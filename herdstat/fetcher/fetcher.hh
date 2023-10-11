/*
 * libherdstat -- herdstat/fetcher/fetcher.hh
 * $Id: fetcher.hh 155 2005-11-27 13:37:27Z ka0ttic $
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

#ifndef _HAVE_FETCHER_HH
#define _HAVE_FETCHER_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/fetcher/fetcher.hh
 * @brief Defines the Fetcher interface.
 */

#include <herdstat/noncopyable.hh>
#include <herdstat/fetcher/exceptions.hh>
#include <herdstat/fetcher/options.hh>
#include <herdstat/fetcher/impmap.hh>

namespace herdstat {

    /**
     * @class Fetcher fetcher.hh herdstat/fetcher/fetcher.hh
     * @brief File fetcher.
     *
     * @section example Example
     *
     * Below is an example showing the most simple usage of the Fetcher class.
     * It uses the default options and default fetcher implementation.
     *
     * @include fetcher/main.cc
     *
     * Below is another example that shows how to use the FetcherOptions class
     * in conjunction with the Fetcher class.  This example allows the choosing
     * of the fetcher implementation at run-time.
     *
     * @include fetcher_options/main.cc
     *
     * Below is another example of using the Fetcher class.  It uses the
     * FetcherImpMap class to provide a user-defined fetcher implementation.
     *
     * @include fetcherimp/main.cc
     */

    class Fetcher : private Noncopyable
    {
        public:
            /// Default constructor.
            Fetcher() throw();

            /** Constructor.
             * @param opts const reference to a FetcherOptions object.
             */
            Fetcher(const FetcherOptions& opts) throw();

            /** Constructor.
             * @param impmap const reference to a user provided implementation
             * map (note that caller is responsible for free'ing all of the
             * map's members).
             * @param opts const reference to a FetcherOptions object.
             */
            Fetcher(const FetcherImpMap& impmap,
                    const FetcherOptions& opts = FetcherOptions()) throw();

            /** Constructor.  Fetch url and save to path.
             * @param url URL string.
             * @param path Path to save to.
             * @param opts const reference to a FetcherOptions objects.
             * @exception FileException, FetchException, UnimplementedFetchMethod
             */
            Fetcher(const std::string& url, const std::string& path,
                    const FetcherOptions& opts = FetcherOptions())
                throw (FileException, FetchException, UnimplementedFetchMethod);

            /// Destructor.
            ~Fetcher() throw();

            /// Get const reference to options object.
            const FetcherOptions& options() const { return _opts; }
            /// Set options object.
            void set_options(const FetcherOptions& opts) { _opts = opts; }

            /** Fetch url and save to path.
             * @param url URL string.
             * @param path Path to save to.
             * @exception FileException, FetchException, UnimplementedFetchMethod
             */
            void operator()(const std::string& url,
                            const std::string& path) const
                throw (FileException, FetchException, UnimplementedFetchMethod);

        private:
            FetcherOptions _opts;
            FetcherImpMap _impmap;
            const bool _copied_impmap;
    };

} // namespace herdstat

#endif /* _HAVE_FETCHER_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
