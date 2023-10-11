/*
 * libherdstat -- herdstat/portage/package_directory.hh
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

#ifndef _HAVE_PORTAGE_PACKAGE_DIRECTORY_HH
#define _HAVE_PORTAGE_PACKAGE_DIRECTORY_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/package_directory.hh
 * @brief Defines the PackageDirectory class.
 */

#include <herdstat/util/file.hh>
#include <herdstat/util/algorithm.hh>
#include <herdstat/util/functional.hh>
#include <herdstat/portage/functional.hh>

namespace herdstat {
namespace portage {

    /**
     * @class PackageDirectory package_directory.hh herdstat/portage/package_directory.hh
     * @brief Package directory contents container.
     */

    class PackageDirectory : public util::Directory
    {
        public:
            /// Default constructor.
            PackageDirectory() throw();

            /** Constructor.
             * @param path Path to package directory.
             * @exception FileException
             */
            PackageDirectory(const std::string& path) throw (FileException);

            /// Copy constructor
            PackageDirectory(const PackageDirectory& that);

            /// Destructor.
            virtual ~PackageDirectory() throw();

            /// Copy assignment operator.
            PackageDirectory& operator= (const PackageDirectory& that);

            /// Get number of ebuilds in this package directory.
            inline difference_type ebuild_count() const;

            /** Get number of patches (files ending in 'patch' or 'diff') in this
             * package directory.
             */
            inline difference_type patches_count() const;

            /// Is a metadata.xml present?
            inline bool has_metadata() const;

            /// Get a vector of portage::Ebuild's representing each ebuild.
            inline const std::vector<Ebuild>& ebuilds() const;

        private:
            mutable std::vector<Ebuild> * _ebuilds;
    };

    inline PackageDirectory::difference_type
    PackageDirectory::ebuild_count() const
    {
        return std::count_if(this->begin(), this->end(), IsEbuild());
    }

    inline PackageDirectory::difference_type
    PackageDirectory::patches_count() const
    {
        const util::Regex re("\\.(patch|diff)$", util::Regex::extended);
        return std::count_if(this->begin(), this->end(),
                std::bind1st(util::regexMatch(), re));
    }

    inline bool
    PackageDirectory::has_metadata() const
    {
        return (this->find("metadata.xml") != this->end());
    }

    inline const std::vector<Ebuild>&
    PackageDirectory::ebuilds() const
    {
        if (not _ebuilds)
        {
            _ebuilds = new std::vector<Ebuild>();
            util::transform_if(this->begin(), this->end(),
                std::back_inserter(*_ebuilds), IsEbuild(),
                util::New<Ebuild>());
        }

        return *_ebuilds;
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_PORTAGE_PACKAGE_DIRECTORY_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
