/*
 * libherdstat -- herdstat/portage/util.cc
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

#include <herdstat/util/string.hh>
#include <herdstat/portage/util.hh>

namespace herdstat {
namespace portage {

std::string
get_pkg_from_verstr(const std::string& ver)
{
    std::string cat, pkg;
    std::string::size_type pos = ver.find('/');
    if (pos != std::string::npos)
        cat.assign(0, pos++);

    std::vector<std::string> parts;
    util::split(ver.substr(pos), std::back_inserter(parts), "-");

    /* if parts > 3, $PN contains a '-' */
    if (parts.size() > 3)
    {
        while (parts.size() > 2)
        {
            pkg += "-" + parts.front();
            parts.erase(parts.begin());
        }
    }

    return (cat+"/"+pkg);
}

} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
