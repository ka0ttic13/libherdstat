/*
 * libherdstat -- herdstat/fetcher/impmap.hh
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

#ifndef _HAVE_FETCHER_IMPMAP_HH
#define _HAVE_FETCHER_IMPMAP_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/fetcher/impmap.hh
 * @brief Defines the FetcherImpMap class.
 */

#include <string>
#include <map>

namespace herdstat {

    class FetcherImp;
    class FetcherOptions;

    /**
     * @class FetcherImpMap impmap.hh herdstat/fetcher/impmap.hh
     * @brief Maps strings (implementation names) to their respective
     * implementations (FetcherImp pointers to concrete instances).  The
     * default supported implementations are inserted upon construction.
     *
     * @section example Example
     *
     * Below is an example of using the FetcherImpMap class in conjunction with
     * the Fetcher class.
     *
     * @include fetcherimp/main.cc
     */

    class FetcherImpMap
    {
        public:
            typedef std::map<std::string, FetcherImp *> container_type;
            typedef container_type::key_type key_type;
            typedef container_type::mapped_type mapped_type;
            typedef container_type::iterator iterator;
            typedef container_type::const_iterator const_iterator;
            typedef container_type::value_type value_type;
            typedef container_type::size_type size_type;

            /** Constructor.
             * All default supported implementations are inserted upon
             * construction.
             * @param opts const reference to a FetcherOptions instance (which
             * is passed to the implementation constructors).
             */
            FetcherImpMap(const FetcherOptions& opts) throw();

            /// Destructor.
            ~FetcherImpMap() throw();

            /** Get implementation mapped to the specified string.
             * @param id implementation name.
             * @returns Pointer to implementation (or NULL if the implementation
             * is not present).
             */
            inline const FetcherImp * const
            operator[](const std::string& id) const;

            /** Insert new implementation pair.
             * @param v const reference to a std::pair<std::string, FetcherImp*>
             * containing the implementation name and implementation pointer.
             * @returns false if insertion failed.
             */
            inline bool insert(const value_type& v);

            /** Insert new implementation.  The implementation pointer type is
             * specified by the template parameter T (which must be explicitly
             * specified).
             * @param id implementation name.
             * @returns false if insertion failed.
             */
            template <typename T>
            inline bool insert(const std::string& id);

            /// Get size.
            inline size_type size() const;

            /// Empty?
            inline bool empty() const;

            inline iterator begin();
            inline const_iterator begin() const;
            inline iterator end();
            inline const_iterator end() const;

        private:
            container_type _map;
            /// Used for passing to FetcherImp constructors when inserting.
            const FetcherOptions& _opts;
    };

    inline const FetcherImp * const
    FetcherImpMap::operator[](const std::string& id) const
    {
        const_iterator i = _map.find(id);
        return (i == _map.end() ? NULL : i->second);
    }

    inline bool
    FetcherImpMap::insert(const value_type& v)
    {
        return _map.insert(v).second;
    }

    template <typename T>
    inline bool
    FetcherImpMap::insert(const std::string& id)
    {
        return _map.insert(std::make_pair(id, new T(_opts))).second;
    }

    inline FetcherImpMap::size_type
    FetcherImpMap::size() const
    {
        return _map.size();
    }

    inline bool
    FetcherImpMap::empty() const
    {
        return _map.empty();
    }

    inline FetcherImpMap::iterator
    FetcherImpMap::begin()
    {
        return _map.begin();
    }

    inline FetcherImpMap::const_iterator
    FetcherImpMap::begin() const
    {
        return _map.begin();
    }

    inline FetcherImpMap::iterator
    FetcherImpMap::end()
    {
        return _map.end();
    }
    
    inline FetcherImpMap::const_iterator
    FetcherImpMap::end() const
    {
        return _map.end();
    }

} // namespace herdstat

#endif /* _HAVE_FETCHER_IMPMAP_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
