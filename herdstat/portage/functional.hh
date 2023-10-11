/*
 * libherdstat -- herdstat/portage/functional.hh
 * $Id: functional.hh 204 2005-12-22 15:57:43Z ka0ttic $
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

#ifndef _HAVE_PORTAGE_FUNCTIONAL_HH
#define _HAVE_PORTAGE_FUNCTIONAL_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/functional.hh
 * @brief portage-related function object definitions.
 */

#include <functional>
#include <herdstat/util/regex.hh>
#include <herdstat/portage/exceptions.hh>
#include <herdstat/portage/util.hh>
#include <herdstat/portage/ebuild.hh>
#include <herdstat/portage/config.hh>
#include <herdstat/portage/package.hh>

namespace herdstat {
namespace portage {

    /**
     * @struct IsCategory functional.hh herdstat/portage/functional.hh
     * @brief Function object that determines whether the given string is a
     * category name.
     */

    struct IsCategory : std::unary_function<std::string, bool>
    {
        bool operator()(const std::string& path) const
        { return is_category(path); }
    };

    /**
     * @struct IsEbuild functional.hh herdstat/portage/functional.hh
     * @brief Function object that determines whether the given path is an
     * ebuild.
     */

    struct IsEbuild : std::unary_function<std::string, bool>
    {
        bool operator()(const std::string& path) const
        { return is_ebuild(path); }
    };

    /**
     * @struct IsPkgDir functional.hh herdstat/portage/functional.hh
     * @brief Function object that determines whether the given path is a valid
     * package directory.
     */

    struct IsPkgDir : std::unary_function<std::string, bool>
    {
        bool operator()(const std::string& path) const
        { return is_pkg_dir(path); }
    };

    /**
     * @struct GetPkgFromPath functional.hh herdstat/portage/functional.hh
     * @brief Function object that returns a "cat/pkg" string given a full
     * path to a package directory.
     */

    struct GetPkgFromPath : std::unary_function<std::string, std::string>
    {
        std::string operator()(const std::string& path) const
        { return get_pkg_from_path(path); }
    };

    /**
     * @struct NewPackage functional.hh herdstat/portage/functional.hh
     * @brief Function object for instantiating a Package class with the given
     * path (to the package directory) and a portdir (may be an overlay).
     */

    struct NewPackage
        : std::binary_function<std::string, std::string, Package>
    {
        Package
        operator()(const std::string& path, const std::string& portdir) const
        { return Package(get_pkg_from_path(path), portdir); }
    };

    /**
     * @struct GetWhichFromPackage functional.hh herdstat/portage/functional.hh
     * @brief Function object for retrieving the path to the newest ebuild for
     * the given Package object.
     */

    struct GetWhichFromPackage : std::unary_function<Package, std::string>
    {
        std::string operator()(const Package& pkg) const
        {
            const KeywordsMap& versions(pkg.keywords());
            if (versions.empty())
                throw NonExistentPkg(pkg);
            return versions.back().first.ebuild();
        }
    };

    /**
     * @struct PackageMatches functional.hh herdstat/portage/functional.hh
     * @brief Function object for comparing a Package object with an object of
     * type T.  Implicit interface assumes there is an operator== for type T.
     */

    template <typename T>
    struct PackageMatches : std::binary_function<Package, T, bool>
    {
        bool operator()(const Package& pkg, const T& criteria) const
        {    
                    /* criteria matches cat/pkg string? */
            return ((pkg.full() == criteria) or
                    /* or matches just the pkg string? */
                    (pkg.name() == criteria));
        }
    };

    /**
     * @struct PackageIsValid functional.hh herdstat/portage/functional.hh
     * @brief Function object for determining whether the given Package object
     * has a valid package directory.
     */

    struct PackageIsValid : std::unary_function<Package, bool>
    {
        bool operator()(const Package& pkg) const
        { return is_pkg_dir(pkg.path()); }
    };

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_PORTAGE_FUNCTIONAL_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
