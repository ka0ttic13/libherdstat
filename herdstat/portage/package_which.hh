/*
 * libherdstat -- herdstat/portage/package_which.hh
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

#ifndef _HAVE_PORTAGE_PACKAGE_WHICH_HH
#define _HAVE_PORTAGE_PACKAGE_WHICH_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/package_which.hh
 * @brief Defines the PackageWhich class.
 */

#include <vector>
#include <herdstat/util/progress/meter.hh>
#include <herdstat/portage/package_finder.hh>

namespace herdstat {
namespace portage {

    /**
     * @class PackageWhich package_which.hh herdstat/portage/package_which.hh
     * @brief Interface for finding the newest ebuild of a package.
     */

    class PackageWhich
    {
        public:
            /// Default constructor.
            PackageWhich() throw();

            /// Destructor.
            ~PackageWhich() throw();

            /// Clear search results.
            void clear_results() { _results.clear(); }
            /// Get search results.
            const std::vector<std::string>& results() const { return _results; }

            /** Get the latest ebuild for each package in the given vector. Any
             * vector<Package> will do, but this is mainly offered for use with
             * PackageFinder results.
             * @param results const reference to a std::vector<Package>.
             * @param progress progress meter to use (defaults to NULL).
             * @returns vector of ebuild paths.
             */
            const std::vector<std::string>&
            operator()(const std::vector<Package>& results,
                       util::ProgressMeter *progress = NULL) throw (NonExistentPkg);

            /** Get the latest ebuild(s) for the given package string/portdir.
             * @param pkg Full category/package string.
             * @param portdir PORTDIR the package is located in.
             * @param progress progress meter to use (defaults to NULL).
             * @returns vector of ebuild paths.
             */
            inline const std::vector<std::string>&
            operator()(const std::string& pkg, const std::string& portdir,
                       util::ProgressMeter *progress = NULL)
                throw (NonExistentPkg);

            /** Get the latest ebuild(s) for those packages matching the given
             * type T using the given PackageList.  Uses PackageFinder to get
             * the list of matching packages.
             * @param v search criteria of type T.
             * @param pkglist const reference to a PackageList.
             * @param progress progress meter to use (defaults to NULL).
             * @returns vector of ebuild paths.
             */
            template <typename T>
            inline const std::vector<std::string>&
            operator()(const T& v, const PackageList& pkglist,
                       util::ProgressMeter *progress = NULL) throw (NonExistentPkg);

        private:
            std::vector<std::string> _results;
    };

    inline const std::vector<std::string>&
    PackageWhich::operator()(const std::string& pkg,
                             const std::string& portdir,
                             util::ProgressMeter *progress)
        throw (NonExistentPkg)
    {
        BacktraceContext c("herdstat::portage::PackageWhich::operator()("+pkg+", "+portdir+")");

        if (progress)
            ++*progress;

        if (not util::is_dir(portdir+"/"+pkg))
            throw NonExistentPkg(pkg);

        Package p(pkg, portdir);
        const KeywordsMap& v(p.keywords());
        _results.push_back(v.back().first.ebuild());
        return _results;
    }

    template <typename T>
    inline const std::vector<std::string>&
    PackageWhich::operator()(const T& v,
                             const PackageList& pkglist,
                             util::ProgressMeter *progress) throw (NonExistentPkg)
    {
        PackageFinder find(pkglist);
        return operator()(find(v, progress));
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_PORTAGE_PACKAGE_WHICH_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
