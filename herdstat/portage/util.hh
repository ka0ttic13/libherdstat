/*
 * libherdstat -- herdstat/portage/util.hh
 * $Id: util.hh 204 2005-12-22 15:57:43Z ka0ttic $
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

#ifndef HAVE_PORTAGE_UTIL_HH
#define HAVE_PORTAGE_UTIL_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/util.hh
 * @brief portage-related miscellaneous functions.
 */

#include <fnmatch.h>
#include <herdstat/util/string.hh>
#include <herdstat/util/misc.hh>
#include <herdstat/util/regex.hh>
#include <herdstat/util/file.hh>
#include <herdstat/portage/config.hh>

namespace herdstat {
namespace portage {

    /**
     * Is the specified path an ebuild?
     * @param path Path.
     * @returns A boolean value.
     */

    inline bool
    is_ebuild(const std::string& path)
    {
        return (fnmatch("*.ebuild", path.c_str(), 0) == 0);
    }

    /**
     * Is the specified path a category?
     * @param path path to category.
     * @returns A boolean value.
     */

    inline bool
    is_category(const std::string& path)
    {
        return (util::is_dir(path) and
                GlobalConfig().categories().count(util::basename(path)));
    }

    /**
     * Is the specified path a valid package directory?
     * @param path Path.
     * @returns A boolean value.
     */

    inline bool
    is_pkg_dir(const std::string& path)
    {
        if (not util::is_dir(path))
            return false;

        /* consider it a package directory if an ebuild exists */
        const util::Directory pkgdir(path);
        return (std::find_if(pkgdir.begin(),
                    pkgdir.end(), is_ebuild) != pkgdir.end());
    }

    /**
     * Are we inside a package directory?
     * @returns A boolean value.
     */

    inline bool
    in_pkg_dir()
    {
        return is_pkg_dir(util::getcwd());
    }

    /**
     * Get category/package from absolute path.
     * @param path Path to package directory.
     * @returns A string in "cat/pkg" form.
     */

    inline std::string
    get_pkg_from_path(const std::string& path)
    {
        std::string::size_type pos = path.rfind('/');
        pos = path.rfind('/', --pos);
        return path.substr(++pos);
    }

    std::string get_pkg_from_verstr(const std::string& ver);

} // namespace portage
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 fdm=marker et : */
