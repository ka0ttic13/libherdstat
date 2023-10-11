/*
 * libherdstat -- herdstat/util/misc.hh
 * $Id: misc.hh 167 2005-12-02 12:41:25Z ka0ttic $
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

#ifndef HAVE_UTIL_MISC_HH
#define HAVE_UTIL_MISC_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/misc.hh
 * @brief Defines miscellaneous classes/functions.
 */

#include <string>
#include <map>

enum ASCIIColor
{
    red,
    green,
    blue,
    yellow,
    orange,
    magenta,
    cyan,
    white,
    black,
    none
};

/* commonly-used utility functions */

namespace herdstat {
namespace util {

    void debug(const char *, ...);

    /// getcwd() wrapper.
    std::string getcwd();

    /**
     * Determine username from email address.
     * @param e E-mail address.
     * @returns A std::string object.
     */
    std::string get_user_from_email(const std::string &e);

    /** Determine current user.
     * Uses ECHANGELOG_USER, if set.  Uses USER otherwise.
     * @returns A std::string object.
     */
    std::string current_user();

    /** Format date std::string.
     * @param t Reference to a time_t object.
     * @param f Format std::string as accepted by strftime(3).
     * @returns A constant std::string object.
     */
    const std::string format_date(const std::time_t &t,
        const char *f = "%a %b %d %T %Z %Y");

    /** Format date std::string.
     * @param t Reference to a std::string object that contains the time.
     * @param f Format std::string as accepted by strftime(3).
     * @returns A constant std::string object.
     */
    const std::string format_date(const std::string &t,
        const char *f = "%a %b %d %T %Z %Y");

    /** Get time_t value from date string.
     * @param str time string.
     * @param fmt format of time string.
     * @returns value as time_t.
     */
    std::time_t str2epoch(const char *str, const char *fmt);

    const std::string get_elapsed_yrs(const std::string& date);

    /**
     * @class ColorMap misc.hh herdstat/util/misc.hh
     * @brief Maps color names to ASCII color sequences.
     */

    class ColorMap
    {
        public:
            /// Constructor.
            ColorMap() throw();

            /** Get color string associated with the given color type.
             * @param c Color type (ASCIIColor).
             * @returns The associated string object.
             */
            inline const std::string& operator[](ASCIIColor c) const
            { return _cm[c]; }

            /** Access color string associated with the given color name.
             * @param s Color name.
             * @returns The associated string object.
             */
            const std::string& operator[](const std::string& s) const;

        private:
            mutable std::map<ASCIIColor, std::string>& _cm;
    };

} // namespace util
} // namespace herdstat

#endif /* HAVE_UTIL_MISC_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
