/*
 * libherdstat -- herdstat/portage/package_finder.hh
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

#ifndef _HAVE_PORTAGE_PACKAGE_FINDER_HH
#define _HAVE_PORTAGE_PACKAGE_FINDER_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/package_finder.hh
 * @brief Defines the PackageFinder class.
 */

#include <herdstat/util/timer.hh>
#include <herdstat/util/algorithm.hh>
#include <herdstat/portage/util.hh>
#include <herdstat/portage/package_list.hh>

namespace herdstat {
namespace portage {

    /**
     * @class PackageFinder package_finder.hh herdstat/portage/package_finder.hh
     * @brief Interface for portage package searching.
     *
     * @section example Example
     *
     * Below is a simple example of using the PackageFinder class:
     *
     * @include package_finder/main.cc
     */

    class PackageFinder
    {
        public:
            /** Constructor.
             * @param pkglist const reference to a PackageList object.
             */
            PackageFinder(const PackageList& pkglist) throw();

            /// Destructor.
            ~PackageFinder() throw();

            /// Clear search results.
            void clear_results() { _results.clear(); }
            /// Get search results.
            const std::vector<Package>& results() const { return _results; }
            /// Get elapsed search time.
            const util::Timer::size_type& elapsed() const
            { return _timer.elapsed(); }

            /** Perform search on the given criteria.
             * @param v const reference to either a std::string or a
             * util::Regex.
             * @param progress Progress meter to use (defaults to NULL).
             * @returns const reference to search results.
             * @exception NonExistentPkg
             */
            template <typename T>
            const std::vector<Package>&
            find(const T& v, util::ProgressMeter *progress = NULL)
                throw (NonExistentPkg);

            /** Perform search for literal string.  Does some possible
             * optimizations, otherwise just calls find().
             * @param v literal string.
             * @param progress Progress meter to use (defaults to NULL).
             * @returns const reference to search results.
             * @exception NonExistentPkg
             */
            const std::vector<Package>&
            operator()(const std::string& v,
                       util::ProgressMeter *progress = NULL) throw (NonExistentPkg);

            /** char * overload that calls the std::string version of
             * operator().
             */
            inline const std::vector<Package>&
            operator()(const char * const v, util::ProgressMeter *progress = NULL)
                throw (NonExistentPkg)
            { return operator()(std::string(v), progress); }

            /// util::Regex overload that simply calls find().
            inline const std::vector<Package>&
            operator()(const util::Regex& v, util::ProgressMeter *progress = NULL)
                throw (NonExistentPkg)
            { return find(v, progress); }

        private:
            struct IsValid
                : std::binary_function<Package, util::ProgressMeter *, bool>
            {
                inline bool operator()(const Package& pkg,
                                       util::ProgressMeter *progress) const;
            };

            const PackageList& _pkglist;
            std::vector<Package> _results;
            util::Timer _timer;
    };

    inline bool
    PackageFinder::IsValid::operator()(const Package& pkg,
                                       util::ProgressMeter *progress) const
    {
        if (progress)
            ++*progress;

        return (is_pkg_dir(pkg.path()) or is_category(pkg.path()));
    }

    template <typename T>
    const std::vector<Package>&
    PackageFinder::find(const T& v, util::ProgressMeter *progress)
        throw (NonExistentPkg)
    {
        _timer.start();

        util::copy_if(_pkglist.begin(), _pkglist.end(),
            std::back_inserter(_results),
            util::compose_f_gx_hx(std::logical_and<bool>(),
                std::bind2nd(PackageMatches<T>(), v),
                std::bind2nd(IsValid(), progress)));

        _timer.stop();

        if (_results.empty())
            throw NonExistentPkg(v);

        return _results;
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_PORTAGE_PACKAGE_FINDER_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
