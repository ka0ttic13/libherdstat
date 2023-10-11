/*
 * libherdstat -- herdstat/portage/package_directory.cc
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

#include <herdstat/portage/package_directory.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
PackageDirectory::PackageDirectory() throw()
    : util::Directory(true), _ebuilds(NULL)
{
}
/****************************************************************************/
PackageDirectory::PackageDirectory(const std::string& path)
    throw (FileException)
    : util::Directory(path, true), _ebuilds(NULL)
{
}
/****************************************************************************/
PackageDirectory::PackageDirectory(const PackageDirectory& that)
    : util::Directory(true), _ebuilds(NULL)
{
    *this = that;
}
/****************************************************************************/
PackageDirectory&
PackageDirectory::operator=(const PackageDirectory& that)
{
    util::Directory::operator=(that);

    if (that._ebuilds)
        _ebuilds = new std::vector<Ebuild>(*that._ebuilds);

    return *this;
}
/****************************************************************************/
PackageDirectory::~PackageDirectory() throw()
{
    if (_ebuilds) delete _ebuilds;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
