/*
 * libherdstat -- herdstat/portage/project_xml.cc
 * $Id: project_xml.cc 220 2005-12-26 12:31:50Z ka0ttic $
 * Copyright (c) 2005 Aaron Walker <ka0ttic@gentoo.org>
 *
 * This file is part of libherdstat.
 *
 * libherdstat is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * libherdstat is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libherdstat; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 325, Boston, MA  02111-1257  USA
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <herdstat/util/string.hh>
#include <herdstat/util/file.hh>
#include <herdstat/portage/project_xml.hh>

#define EXPIRE  169200

namespace herdstat {
namespace portage {
/*** static members *********************************************************/
const char * const ProjectXML::_baseURL = "http://www.gentoo.org/cgi-bin/viewcvs.cgi/*checkout*/xml/htdocs%s?rev=HEAD&root=gentoo&content-type=text/plain";
const char * const ProjectXML::_baseLocal = "%s/gentoo/xml/htdocs/%s";
std::set<std::string> ProjectXML::_parsed;
/****************************************************************************/
ProjectXML::ProjectXML(const std::string& path, const std::string& cvsdir,
                         bool force_fetch)
    throw (FileException, xml::ParserException)
    : _devs(), _cvsdir(cvsdir), _force_fetch(force_fetch),
      in_sub(false), in_dev(false), in_task(false), _cur_role()
{
    if (_cvsdir.empty())
    {
        std::vector<std::string> parts;
        util::split(path, std::back_inserter(parts), "/");
        assert(parts.size() > 1);
        this->set_path(util::sprintf("%s/%s.xml", LOCALSTATEDIR,
            (*(parts.end() - 2)).c_str()));
        this->fetch(path);
    }
    else
    {
        this->set_path(util::sprintf(_baseLocal, _cvsdir.c_str(),
            path.c_str()));
    }

    this->parse();
}
/****************************************************************************/
ProjectXML::~ProjectXML() throw()
{
}
/****************************************************************************/
void
ProjectXML::do_fetch(const std::string& p) const throw (FetchException)
{
    BacktraceContext c("portage::ProjectXML::do_fetch("+p+")");

    if (not _cvsdir.empty())
        return;

    assert(not p.empty());
    const std::string url(util::sprintf(_baseURL, p.c_str()));
    util::Stat mps(this->path());

    try
    {
        if (not mps.exists() or (mps.size() == 0) or
            (mps.exists() and ((std::time(NULL) - mps.mtime()) > EXPIRE)) or
            _force_fetch)
        {
            if (mps.exists())
                util::copy_file(this->path(), this->path()+".bak");

            const Fetcher& fetcher(this->fetcher());
            fetcher(url, this->path());

            if (not mps() or (mps.size() == 0))
                throw FetchException();

            unlink((this->path()+".bak").c_str());
        }
    }
    catch (const FetchException)
    {
        if (util::is_file(this->path()+".bak"))
            util::move_file(this->path()+".bak", this->path());

        if (not mps() or (mps.size() == 0))
        {
            unlink(this->path().c_str());
            return;
        }
    }

    if (not mps())
        std::cerr << "Failed to save '" << url << "' to" << std::endl
            << "'" << this->path() << "'." << std::endl;
}
/****************************************************************************/
void
ProjectXML::do_parse(const std::string& path)
    throw (FileException, xml::ParserException)
{
    if (not path.empty()) this->set_path(path);

    BacktraceContext c("portage::ProjectXML::parse("+this->path()+")");

    if (not util::is_file(this->path()))
        throw FileException(this->path());

    /* if inserting into the set fails, we've already parsed it.
     * this prevents recursively instantiating this class unneededly. */
    if (not _parsed.insert(this->path()).second)
        return;

    this->parse_file(this->path().c_str());
}
/****************************************************************************/
bool
ProjectXML::start_element(const std::string& name, const attrs_type& attrs)
{
    if (meter())
        ++*meter();

    if (name == "task")
        in_task = true;
    else if (name == "subproject")
    {
        /*
         * If inheritmembers == "yes", fetch the file listed in the ref attr,
         * and treat it as another projectxml, recursing into ourselves.
         */

        attrs_type::const_iterator pos = attrs.find("inheritmembers");
        if ((pos != attrs.end()) and (pos->second == "yes"))
        {
            if ((pos = attrs.find("ref")) != attrs.end())
            {
                in_sub = true;

                ProjectXML mp(pos->second, _cvsdir, _force_fetch);
                mp.set_meter(this->meter());
                Herd::const_iterator i;
                for (i = mp.devs().begin() ; i != mp.devs().end() ; ++i)
                {
                    /* if dev doesn't exist, insert it */
                    Herd::iterator d = _devs.find(*i);
                    if (d == _devs.end())
                        _devs.insert(*i);
                    /* otherwise, set it's role if unset */
                    else if (not i->role().empty() and d->role().empty())
                        const_cast<Developer&>(*d).set_role(i->role());
                }
            }
        }
    }
    else if (name == "dev" and not in_task)
    {
        in_dev = true;

        attrs_type::const_iterator pos = attrs.find("description");
        if (pos != attrs.end())
            _cur_role.assign(pos->second);
    }

    return true;
}
/****************************************************************************/
bool
ProjectXML::end_element(const std::string& name)
{
    if (meter())
        ++*meter();

    if (name == "task")             in_task = false;
    else if (name == "subproject")  in_sub = false;
    else if (name == "dev")         in_dev = false;
    return true;
}
/****************************************************************************/
bool
ProjectXML::do_text(const std::string& text)
{
    if (meter())
        ++*meter();

    if (in_dev)
    {
        Developer dev(util::lowercase(text));
        dev.set_role(_cur_role);

        Herd::iterator i = _devs.find(dev);
        if (i == _devs.end())
            _devs.insert(dev);
        else if (not dev.role().empty() and i->role().empty())
            const_cast<Developer&>(*i).set_role(dev.role());
    }

    return true;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
