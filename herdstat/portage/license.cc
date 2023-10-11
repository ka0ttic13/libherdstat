/*
 * libherdstat -- herdstat/portage/license.cc
 * $Id$
 * Copyright (c) 2005 Aaron Walker <ka0ttic@gentoo.org>
 *
 * This file is part of libherdstat.
 *
 * libherdstat is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * libherdstat is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libherdstat; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 325, Boston, MA  02111-1257  USA
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <algorithm>
#include <herdstat/util/string.hh>
#include <herdstat/util/file.hh>
#include <herdstat/portage/exceptions.hh>
#include <herdstat/portage/config.hh>
#include <herdstat/portage/license.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
License::License(bool validate) throw()
    : _validate(validate), _license()
{
}
/****************************************************************************/
License::License(const std::string& str, bool validate)
    throw (QAException)
    : _validate(validate), _license(str)
{
    this->parse();
}
/****************************************************************************/
License::~License() throw()
{
}
/****************************************************************************/
void
License::parse() throw (QAException)
{
    BacktraceContext c("portage::License::parse("+_license+")");

    _license.erase(std::remove(_license.begin(),
                _license.end(), '|'), _license.end());
    _license.erase(std::remove(_license.begin(),
                _license.end(), '('), _license.end());
    _license.erase(std::remove(_license.begin(),
                _license.end(), ')'), _license.end());

    /* extract FOO from lines like "foo? ( FOO )" */
    std::string::size_type pos;
    while ((pos = _license.find('?')) != std::string::npos)
    {
        std::string::size_type lpos = pos;
        while (_license.at(lpos) != ' ')
        {
            _license.erase(lpos, 1);
            if (lpos-- == 0)
                break;
        }
    }

    _license.assign(util::tidy_whitespace(_license));

    if (_validate)
    {
        std::vector<std::string> parts;
        std::vector<std::string>::iterator i;
        util::split(_license, std::back_inserter(parts));
        for (i = parts.begin() ; i != parts.end() ; ++i)
        {
            if (not util::file_exists(GlobalConfig().portdir()+
                    "/licenses/"+(*i)))
                throw QAException(*i);
        }
    }
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
