/*
 * libherdstat -- herdstat/portage/package_list.hh
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

#ifndef _HAVE_PORTAGE_PACKAGE_LIST_HH
#define _HAVE_PORTAGE_PACKAGE_LIST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/package_list.hh
 * @brief Provides the PackageList class definition.
 */

#include <herdstat/util/progress/meter.hh>
#include <herdstat/util/container_base.hh>
#include <herdstat/portage/package.hh>
#include <herdstat/portage/functional.hh>

/** 
 * @def PKGLIST_RESERVE
 * @brief Rough estimate of number of packages updated from time to time.  Used
 * for reserve()'ing to prevent a sleu of allocations.
 */

#define PKGLIST_RESERVE            10250

namespace herdstat {
namespace portage {

    /**
     * @class PackageList package_list.hh herdstat/portage/package_list.hh
     * @brief Represents a sorted package list of all directories inside valid
     * categories.  Note that for speed reasons, no validation is done (other
     * than checking that it's a directory and it exists), so you should use
     * the portage::is_pkg_dir() function or the portage::IsPkgDir() function
     * object to validate an element before using it.
     *
     * @section usage Usage
     *
     * Use PackageList as you would any std::vector.
     *
     * @section example Example
     * @see portage::PackageFinder for an example of using portage::PackageList.
     */

    class PackageList : public util::VectorBase<Package>
    {
        public:
            /** Default constructor.
             * @param fill Fill with all packages in the tree? (defaults to
             * true).
             * @param progress progress meter to use (defaults to NULL).
             */
            PackageList(bool fill = true, util::ProgressMeter *progress = NULL);

            /** Constructor.
             * @param portdir PORTDIR to search.
             * @param overlays const reference to a vector of strings denoting
             * overlays (defaults to empty).
             * @param fill Fill with all packages in the tree? (defaults to
             * true).
             * @param progress progress meter to use (defaults to NULL).
             */
            PackageList(const std::string& portdir, const std::vector<std::string>&
                overlays = std::vector<std::string>(), bool fill = true,
                util::ProgressMeter *progress = NULL);

            /// Destructor.
            ~PackageList() throw();

            /** Fill container.
             * @param progress pointer to progress meter to use (defaults to
             * NULL).
             */
            void fill(util::ProgressMeter *progress = NULL);
            /// Has our container been fill()'d?
            bool filled() const { return _filled; }

            ///@{
            /// Is the specified package present in our container?
            inline bool has_package(const std::string& pkg) const;
            inline bool has_package(const Package& pkg) const;
            ///@}

            /// Implicit conversion to const std::vector<Package>&
            operator const container_type&() const { return this->container(); }

            /// Get main portdir used when filling the container.
            const std::string& portdir() const { return _portdir; }
            /// Get overlays used when filling the container.
            const std::vector<std::string>& overlays() const { return _overlays; }

        private:
            const std::string& _portdir;
            const std::vector<std::string>& _overlays;
            bool _filled;
    };

    inline bool
    PackageList::has_package(const std::string& pkg) const
    {
        return std::binary_search(this->begin(), this->end(), pkg);
    }

    inline bool
    PackageList::has_package(const Package& pkg) const
    {
        return has_package(pkg.full());
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_PORTAGE_PACKAGE_LIST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
