/*
 * libherdstat -- herdstat/util/glob.hh
 * $Id: glob.hh 211 2005-12-22 16:11:20Z ka0ttic $
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

#ifndef HAVE_GLOB_HH
#define HAVE_GLOB_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/glob.hh
 * @brief Defines the Glob class.
 */

#include <vector>
#include <string>

namespace herdstat {
namespace util {

    /**
     * @class Glob glob.hh herdstat/util/glob.hh
     * @brief Interface to POSIX glob().
     *
     * @section example Example
     *
     * Below is a simple example of using the Glob class:
     *
@code
const herdstat::util::Glob glob("*foo*");
const std::vector<std::string>& results(glob.results());
std::copy(glob.begin(), glob.end(),
    std::ostream_iterator<std::string>(std::cout, "\n"));
@endcode
     *
     * Another example, using successive operator()() calls:
     *
@code
herdstat::util::Glob glob;
glob("*foo*");
std::copy(glob.results().begin(), glob.results().end(),
    std::ostream_iterator<std::string>(std::cout, "\n"));
glob.clear_results();
glob("*.ebuild");
std::copy(glob.results().begin(), glob.results().end(),
    std::ostream_iterator<std::string>(std::cout, "\n"));
@endcode
     */

    class Glob
    {
        public:
            /// Default constructor.
            Glob() throw();

            /** Constructor.
             * @param pattern glob pattern string.
             * @exception ErrnoException
             */
            Glob(const std::string& pattern) throw (ErrnoException);

            /// Destructor.
            ~Glob() throw();

            /// Clear glob results.
            inline void clear_results();

            /** Get glob results.
             * @returns const reference to results.
             */
            inline const std::vector<std::string>& results() const;

            /** Perform glob search.
             * @param pattern glob pattern string.
             * @exception ErrnoException
             * @returns const reference to results.
             */
            const std::vector<std::string>&
            operator()(const std::string& pattern) throw (ErrnoException);

        private:
            std::vector<std::string> _results;
    };

    inline void
    Glob::clear_results()
    {
        _results.clear();
    }

    inline const std::vector<std::string>&
    Glob::results() const
    {
        return _results;
    }

} // namespace util
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 fdm=marker et : */
