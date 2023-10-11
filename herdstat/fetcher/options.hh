/*
 * libherdstat -- herdstat/fetcher/options.hh
 * $Id: options.hh 158 2005-11-29 13:19:55Z ka0ttic $
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

#ifndef _HAVE_FETCHER_OPTIONS_HH
#define _HAVE_FETCHER_OPTIONS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/fetcher/options.hh
 * @brief Defines the FetcherOptions class.
 */

#include <string>

/**
 * @def DEFAULT_FETCH_METHOD
 * @brief Default fetcher implementation to use.
 */
#define DEFAULT_FETCH_METHOD    "wget"

namespace herdstat {

    /**
     * @class FetcherOptions options.hh herdstat/fetcher/options.hh
     * @brief Options that determine Fetcher's behavior.
     *
     * @section example Example
     *
     * Below is an example of using the FetcherOptions class in conjunction with
     * the Fetcher class.
     *
     * @include fetcher_options/main.cc
     */

    class FetcherOptions
    {
        public:
            /** Default constructor.
             * Fetcher implementation is set to the value of the environment
             * variable HERDSTAT_FETCH_METHOD (if set).  Otherwise the value of
             * the DEFAULT_FETCH_METHOD define is used.
             */
            FetcherOptions() throw();

            /** Constructor.
             * @param imp Fetcher implementation to use.
             */
            FetcherOptions(const std::string& imp) throw();

            /// Destructor.
            ~FetcherOptions() throw();

            /// Get fetcher implementation name.
            inline const std::string& implementation() const;
            /// verbose?
            inline bool verbose() const;
            /// debug?
            inline bool debug() const;

            /// Set fetcher implementation name.
            inline void set_implementation(const std::string& imp);
            /// set verbose
            inline void set_verbose(bool v);
            /// set debug
            inline void set_debug(bool v);

        private:
            bool _verbose;
            bool _debug;
            std::string _imp;
    };

    inline const std::string& FetcherOptions::implementation() const
    { return _imp; }
    inline bool FetcherOptions::verbose() const { return _verbose; }
    inline bool FetcherOptions::debug() const { return _debug; }
    inline void FetcherOptions::set_implementation(const std::string& imp)
    { _imp = imp; }
    inline void FetcherOptions::set_verbose(bool v) { _verbose = v; }
    inline void FetcherOptions::set_debug(bool v) { _debug = v; }

} // namespace herdstat

#endif /* _HAVE_FETCHER_OPTIONS_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
