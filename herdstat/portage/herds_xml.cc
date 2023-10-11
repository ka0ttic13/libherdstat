/*
 * libherdstat -- herdstat/portage/herds_xml.cc
 * $Id: herds_xml.cc 220 2005-12-26 12:31:50Z ka0ttic $
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

#include <herdstat/exceptions.hh>
#include <herdstat/util/string.hh>
#include <herdstat/util/file.hh>
#include <herdstat/xml/document.hh>
#include <herdstat/portage/project_xml.hh>
#include <herdstat/portage/herds_xml.hh>

#define HERDSXML_EXPIRE     86400

namespace herdstat {
namespace portage {
/*** static members *********************************************************/
const char * const HerdsXML::_local_default = LOCALSTATEDIR"/herds.xml";
/****************************************************************************/
HerdsXML::HerdsXML() throw()
    : DataSource(), _herds(), _cvsdir(), _force_fetch(false), _fetch(),
      in_herd(false), in_herd_name(false),
      in_herd_email(false), in_herd_desc(false), in_maintainer(false),
      in_maintainer_name(false), in_maintainer_email(false),
      in_maintainer_role(false), in_maintaining_prj(false),
      _cur_herd(), _cur_dev()
{
}
/****************************************************************************/
HerdsXML::HerdsXML(const std::string& path)
    throw (FileException, xml::ParserException)
    : DataSource(path), _herds(), _cvsdir(), _force_fetch(false), _fetch(),
      in_herd(false), in_herd_name(false), in_herd_email(false),
      in_herd_desc(false), in_maintainer(false), in_maintainer_name(false),
      in_maintainer_email(false), in_maintainer_role(false), in_maintaining_prj(false),
      _cur_herd(), _cur_dev()
{
    this->parse();
}
/****************************************************************************/
HerdsXML::~HerdsXML() throw()
{
}
/****************************************************************************/
void
HerdsXML::do_parse(const std::string& path)
        throw (FileException, xml::ParserException)
{
    this->timer().start();

    if      (not path.empty())      this->set_path(path);
    else if (this->path().empty())  this->set_path(_local_default);

    BacktraceContext c("portage::HerdsXML::parse("+this->path()+")");

    if (not util::is_file(this->path()))
        throw FileException(this->path());

    this->parse_file(this->path().c_str());

    this->timer().stop();
}
/****************************************************************************/
void
HerdsXML::fill_developer(Developer& dev) const throw (Exception)
{
    BacktraceContext c("portage::HerdsXML::fill_developer()");

    /* at least the dev's username needs to be present for searching */
    if (dev.user().empty())
        throw Exception("HerdsXML::fill_developer() requires you pass a Developer object with at least the user name filled in");

    /* for each herd */
    for (Herds::const_iterator h = _herds.begin() ; h != _herds.end() ; ++h)
    {
        /* is the developer in this herd? */
        Herd::const_iterator d = h->find(dev);
        if (d != h->end())
        {
            if (dev.name().empty() and not d->name().empty())
                dev.set_name(d->name());
            dev.set_email(d->email());
            dev.append_herd(h->name());
        }
    }
}
/****************************************************************************/
bool
HerdsXML::start_element(const std::string& name,
                        const attrs_type& attrs LIBHERDSTAT_UNUSED)
{
    if (meter())
        ++*meter();

    if (name == "herd")
        in_herd = true;
    else if (name == "name" and not in_maintainer)
        in_herd_name = true;
    else if (name == "email" and not in_maintainer)
        in_herd_email = true;
    else if (name == "description" and not in_maintainer)
        in_herd_desc = true;
    else if (name == "maintainer")
        in_maintainer = true;
    else if (name == "email" and in_maintainer)
        in_maintainer_email = true;
    else if (name == "name" and in_maintainer)
        in_maintainer_name = true;
    else if (name == "role")
        in_maintainer_role = true;
    else if (name == "maintainingproject")
        in_maintaining_prj = true;

    return true;
}
/****************************************************************************/
bool
HerdsXML::end_element(const std::string& name)
{
    if (meter())
        ++*meter();

    if (name == "herd")
        in_herd = false;
    else if (name == "name" and not in_maintainer)
        in_herd_name = false;
    else if (name == "email" and not in_maintainer)
        in_herd_email = false;
    else if (name == "description" and not in_maintainer)
        in_herd_desc = false;
    else if (name == "maintainer")
        in_maintainer = false;
    else if (name == "email" and in_maintainer)
        in_maintainer_email = false;
    else if (name == "name" and in_maintainer)
        in_maintainer_name = false;
    else if (name == "role")
        in_maintainer_role = false;
    else if (name == "maintainingproject")
        in_maintaining_prj = false;

    return true;
}
/****************************************************************************/
bool
HerdsXML::do_text(const std::string& text)
{
    if (meter())
        ++*meter();

    if (in_herd_name)
        _cur_herd = _herds.insert(Herd(text)).first;
    else if (in_herd_desc)
        const_cast<Herd&>(*_cur_herd).set_desc(text);
    else if (in_herd_email)
        const_cast<Herd&>(*_cur_herd).set_email(text);        
    else if (in_maintainer_email)
        _cur_dev = const_cast<Herd&>(*_cur_herd).insert(
                Developer(util::lowercase(text))).first;
    else if (in_maintainer_name)
        const_cast<Developer&>(*_cur_dev).set_name(_cur_dev->name() + text);
    else if (in_maintainer_role)
        const_cast<Developer&>(*_cur_dev).set_role(text);

    else if (in_maintaining_prj)
    {
        /* 
         * special case - for <maintainingproject> we must fetch
         * the listed XML, parse it, and then fill the developer
         * container.
         */

        try
        {
            ProjectXML mp(text, _cvsdir, _force_fetch);
            mp.set_meter(this->meter());
            const_cast<Herd&>(*_cur_herd).insert(
                mp.devs().begin(), mp.devs().end());
        }
        catch (const FileException& e)
        {
            std::cerr << e.what() << std::endl;            
        }
    }

    return true;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
