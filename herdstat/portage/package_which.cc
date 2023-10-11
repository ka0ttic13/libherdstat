/*
 * libherdstat -- herdstat/portage/package_which.cc
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

#include <herdstat/portage/package_which.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
PackageWhich::PackageWhich() throw()
    : _results()
{
}
/****************************************************************************/
PackageWhich::~PackageWhich() throw()
{
}
/****************************************************************************/
const std::vector<std::string>&
PackageWhich::operator()(const std::vector<Package>& finder_results,
                         util::ProgressMeter *progress)
    throw (NonExistentPkg)
{
    BacktraceContext c("herdstat::portage::PackageWhich::operator()(std::vector<Package>)");

    /* Loop through the results only keeping the newest of packages */
    std::vector<Package> pkgs;
    std::vector<Package>::const_iterator i;
    for (i = finder_results.begin() ; i != finder_results.end() ; ++i)
    {
        if (progress)
            ++*progress;

        if (is_category(i->path()))
            continue;

        /* see if we've inserted it already */
        std::vector<Package>::iterator p =
            std::find_if(pkgs.begin(), pkgs.end(),
                util::compose_f_gx(
                    std::bind2nd(std::equal_to<std::string>(), *i),
                    std::mem_fun_ref(&Package::full)));

        /* package doesn't exist, so add it */
        if (p == pkgs.end())
            pkgs.push_back(*i);
        /* package of the same name exists */
        else
        {
            const Package& p1(*i);
            Package& p2(*p);

            const VersionString& v1(p1.keywords().back().first);
            const VersionString& v2(p2.keywords().back().first);

            /* if the pkg that already exists is older than the current one, or
             * they're equal and the one not already in 'pkgs' is in an overlay,
             * replace it */
            if (((v2 < v1) or (v2 == v1)) and p1.in_overlay())
                p2 = p1;
        }
    }

    std::transform(pkgs.begin(), pkgs.end(),
        std::back_inserter(_results), GetWhichFromPackage());

    return _results;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
