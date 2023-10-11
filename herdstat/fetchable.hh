/*
 * libherdstat -- herdstat/fetchable.hh
 * $Id: fetchable.hh 154 2005-11-26 13:37:02Z ka0ttic $
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

#ifndef _HAVE_FETCHABLE_HH
#define _HAVE_FETCHABLE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/fetchable.hh
 * @brief Defines the abstract Fetchable interface.
 */

#include <herdstat/fetcher/fetcher.hh>

namespace herdstat {

    /**
     * @class Fetchable fetchable.hh herdstat/fetchable.hh
     * @brief Abstract base for fetchable things.
     *
     * The Fetchable base class is used to describe objects as being
     * "fetchable".  Derivatives define their own do_fetch virtual function that
     * uses the _fetch object (obtained via the fetcher() member function) to
     * fetch the needed file(s).
     *
     * @section example Example
     *
     * Below is an example application that uses the Fetchable base class to
     * describe an RSS feed as being fetchable.  The RSSFeed class defines the
     * do_fetch virtual to fetch the RSS feed.
     *
     * @include fetchable/rss_feed.hh
     *
     * Defines the RSSFeed and RSSFeedEntry interfaces.
     *
     * @include fetchable/rss_feed.cc
     *
     * Defines the RSSFeed and RSSFeedEntry implementations.
     *
     * @include fetchable/main.cc
     *
     * Defines main().
     */

    class Fetchable
    {
        public:
            /// Destructor.
            virtual ~Fetchable() { }

            /** Fetch our file and save it to the specified path.
             * @param path Path to file.
             * @exception FetchException
             */
            inline void fetch(const std::string& path = "") const
                throw (FetchException);

            /// Have we already fetch()'d?
            bool fetched() const { return _fetched; }

        protected:
            /// Default constructor.
            Fetchable() throw() : _fetch(), _fetched(false) { }

            /// Return fetcher.
            const Fetcher& fetcher() const { return _fetch; }

            /** Does the actual fetching.
             * @param path local path to save.
             * @exception FetchException
             */
            virtual void do_fetch(const std::string& path = "") const
                throw (FetchException) = 0;

        private:
            mutable Fetcher _fetch;
            mutable bool _fetched;
    };

    inline void
    Fetchable::fetch(const std::string& path) const throw (FetchException)
    {
        if (_fetched)
            return;
        do_fetch(path);
        _fetched = true;
    }

} // namespace herdstat

#endif /* _HAVE_FETCHABLE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
