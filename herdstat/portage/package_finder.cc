/*
 * libherdstat -- herdstat/portage/package_finder.cc
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

#include <herdstat/portage/package_finder.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
PackageFinder::PackageFinder(const PackageList& pkglist) throw()
    : _pkglist(pkglist), _results(), _timer()
{
}
/****************************************************************************/
PackageFinder::~PackageFinder() throw()
{
}
/****************************************************************************/
const std::vector<Package>&
PackageFinder::operator()(const std::string& criteria,
                          util::ProgressMeter *progress)
    throw (NonExistentPkg)
{
    /* literal searches allow us to use a little optimization hack - we can
     * simply check if the criteria exists in portdir or any of the overlays */

    const std::string pd(_pkglist.portdir()+"/"+criteria);
    if (is_pkg_dir(pd) or is_category(pd))
        _results.push_back(Package(criteria, _pkglist.portdir()));

    std::vector<std::string>::const_iterator i;
    for (i = _pkglist.overlays().begin() ;
            i != _pkglist.overlays().end() ; ++i)
    {
        if (progress)
            ++*progress;

        const std::string od(*i+"/"+criteria);
        if (is_pkg_dir(od) or is_category(od))
            _results.push_back(Package(criteria, *i));
    }

    if (_results.empty())
        return find(criteria, progress);

    return _results;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
