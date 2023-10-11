/*
 * libherdstat -- herdstat/portage/devaway_xml.cc
 * $Id: devaway_xml.cc 220 2005-12-26 12:31:50Z ka0ttic $
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
#include <herdstat/portage/devaway_xml.hh>

namespace herdstat {
namespace portage {
/*** static members *********************************************************/
const char * const DevawayXML::_local_default = LOCALSTATEDIR"/devaway.xml";
/****************************************************************************/
DevawayXML::DevawayXML() throw()
    : DataSource(), _devs(), in_devaway(false),
      in_dev(false), in_reason(false), _cur_dev()
{
}
/****************************************************************************/
DevawayXML::DevawayXML(const std::string &path)
    throw (FileException, xml::ParserException)
    : DataSource(path), _devs(), in_devaway(false),
      in_dev(false), in_reason(false), _cur_dev()
{
    this->parse();
}
/****************************************************************************/
DevawayXML::~DevawayXML() throw()
{
}
/****************************************************************************/
void
DevawayXML::do_parse(const std::string& path)
    throw (FileException, xml::ParserException)
{
    this->timer().start();

    if (not path.empty())
        this->set_path(path);
    else if (this->path().empty())
        this->set_path(_local_default);

    BacktraceContext c("portage::DevawayXML::parse("+this->path()+")");

    if (not util::is_file(this->path()))
        throw FileException(this->path());

    this->parse_file(this->path().c_str());

    this->timer().stop();
}
/****************************************************************************/
void
DevawayXML::fill_developer(Developer& dev) const throw (Exception)
{
    BacktraceContext c("portage::DevawayXML::fill_developer()");

    if (dev.user().empty())
        throw Exception("DevawayXML::fill_developer() requires you pass a Developer object with at least the user name filled in");

    Developers::const_iterator d = _devs.find(dev);
    if (d != _devs.end())
    {
        dev.set_away(true);
        dev.set_awaymsg(d->awaymsg());
    }
}
/****************************************************************************/
const std::vector<std::string>
DevawayXML::keys() const
{
    std::vector<std::string> v;
    for (Developers::const_iterator i = _devs.begin() ; i != _devs.end() ; ++i)
    {
        v.push_back(i->user());
        v.push_back(i->email());
    }
    return v;
}
/****************************************************************************/
bool
DevawayXML::start_element(const std::string& name, const attrs_type& attrs)
{
    if (meter())
        ++*meter();

    if (name == "devaway")
        in_devaway = true;
    else if (name == "dev" and in_devaway)
    {
        attrs_type::const_iterator pos = attrs.find("nick");
        if (pos == attrs.end())
        {
            std::cerr << "<dev> tag with no nick attribute!" << std::endl;
            return false;
        }

        _cur_dev = _devs.insert(pos->second).first;
        in_dev = true;
    }
    else if (name == "reason" and in_dev)
        in_reason = true;

    return true;
}
/****************************************************************************/
bool
DevawayXML::end_element(const std::string& name)
{
    if (meter())
        ++*meter();

    if (name == "devaway")      in_devaway = false;
    else if (name == "dev")     in_dev = false;
    else if (name == "reason")  in_reason = false;

    return true;
}
/****************************************************************************/
bool
DevawayXML::do_text(const std::string& text)
{
    if (meter())
        ++*meter();

    if (in_reason)
        const_cast<Developer&>(*_cur_dev).set_awaymsg(_cur_dev->awaymsg()+text);

    return true;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
