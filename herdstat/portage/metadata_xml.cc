/*
 * libherdstat -- herdstat/portage/metadata_xml.cc
 * $Id: metadata_xml.cc 220 2005-12-26 12:31:50Z ka0ttic $
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

#include <locale>

#include <herdstat/exceptions.hh>
#include <herdstat/util/string.hh>
#include <herdstat/util/file.hh>
#include <herdstat/portage/metadata_xml.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
MetadataXML::MetadataXML() throw()
    : Parsable(), _data(), in_herd(false), in_maintainer(false),
      in_email(false), in_name(false), in_desc(false), in_longdesc(false),
      in_en_longdesc(false), _cur_dev(), _longdesc()
{
}
/****************************************************************************/
MetadataXML::MetadataXML(const std::string& path, const std::string& pkg)
    throw (FileException, xml::ParserException)
    : Parsable(path), _data(pkg), in_herd(false), in_maintainer(false),
      in_email(false), in_name(false), in_desc(false), in_longdesc(false),
      in_en_longdesc(false), _cur_dev(), _longdesc()
{
    this->parse();
}
/****************************************************************************/
MetadataXML::~MetadataXML() throw()
{
}
/****************************************************************************/
void
MetadataXML::do_parse(const std::string& path)
    throw (FileException, xml::ParserException)
{
    if (not path.empty()) this->set_path(path);

    BacktraceContext c("portage::MetadataXML::parse("+this->path()+")");

    if (not util::file_exists(this->path())) throw FileException(this->path());
    this->parse_file(this->path().c_str());

    if (_data.longdesc().empty() and not _longdesc.empty())
        _data.set_longdesc(_longdesc);
}
/****************************************************************************/
bool
MetadataXML::start_element(const std::string& name, const attrs_type& attrs)
{
    if (meter())
        ++*meter();

    if (name == "catmetadata")
        _data.set_category(true);
    else if (name == "herd")
        in_herd = true;
    else if (name == "maintainer")
        in_maintainer = true;
    else if (name == "email" and in_maintainer)
        in_email = true;
    else if (name == "name" and in_maintainer)
        in_name = true;
    else if (name == "description")
        in_desc = true;
    else if (name == "longdescription")
    {
        attrs_type::const_iterator i = attrs.find("lang");
        if (i != attrs.end())
        {
            if (i->second.empty() or (i->second == "en"))
            {
                in_en_longdesc = true;
                return true;
            }
        
            if (i->second == std::locale("").name().substr(0, 2))
                in_longdesc = true;
        }
        else
            in_en_longdesc = true;
    }

    return true;
}
/****************************************************************************/
bool
MetadataXML::end_element(const std::string& name)
{
    if (meter())
        ++*meter();

    if (name == "herd")
        in_herd = false;
    else if (name == "maintainer")
        in_maintainer = false;
    else if (name == "email" and in_maintainer)
        in_email = false;
    else if (name == "name" and in_maintainer)
        in_name = false;
    else if (name == "description")
        in_desc = false;
    else if (name == "longdescription" and in_en_longdesc)
        in_en_longdesc = false;
    else if (name == "longdescription")
        in_longdesc = false;

    return true;
}
/****************************************************************************/
bool
MetadataXML::do_text(const std::string& text)
{
    if (meter())
        ++*meter();

    if (in_herd)
        _data.herds().insert(Herd(text));
    else if (in_email)
    {
        /* only insert it if it's not a herd */
        if (_data.herds().find(text.substr(0, text.find('@'))) ==
                _data.herds().end())
            _cur_dev = _data.devs().insert(Developer(util::lowercase(text))).first;
        else
            _cur_dev = _data.devs().end();
    }
    else if (in_name)
    {
        if (_cur_dev != _data.devs().end())
            const_cast<Developer&>(*_cur_dev).set_name(_cur_dev->name() + text);
    }
    else if (in_desc)
    {
        if (_cur_dev != _data.devs().end())
            const_cast<Developer&>(*_cur_dev).set_role(text);
    }
    else if (in_en_longdesc)
        _longdesc += text;
    else if (in_longdesc)
        _data.set_longdesc(_data.longdesc() + text);

    return true;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
