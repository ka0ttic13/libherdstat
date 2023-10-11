/*
 * libherdstat -- herdstat/cachable.hh
 * $Id: cachable.hh 155 2005-11-27 13:37:27Z ka0ttic $
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

#ifndef _HAVE_CACHABLE_HH
#define _HAVE_CACHABLE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/cachable.hh
 * @brief Defines the Cachable abstract class.
 */

#include <herdstat/noncopyable.hh>

namespace herdstat {

    /**
     * @class Cachable cachable.hh herdstat/cachable.hh
     * @brief Abstract interface for cachable things.
     *
     * @section example Example
     *
     * Below is a simple example of using the Cachable base class.  Upon first
     * invocation, the below application caches the location of every
     * metadata.xml in the specified PORTDIR in a file called metadata_list.txt.
     * Upon subsequent invocations, it will simply load metadata_list.txt.
     *
     * @include cachable/main.cc
     */

    class Cachable : private Noncopyable
    {
        public:
            /// Destructor.
            virtual ~Cachable() { }

            /** Determine if cache is valid.
             * @returns true if cache is valid.
             */
            virtual bool valid() const = 0;

            /// Fill cache.
            virtual void fill() = 0;

            /// Load cache.
            virtual void load() = 0;

            /// Dump cache.
            virtual void dump() = 0;

            /// Get path to cache.
            const std::string& path() const { return _path; }

        protected:
            /** Constructor.
             * @param path Path of cache.
             */
            Cachable(const std::string &path) : _path(path) { }

            /// Initialize cache.  Default cache logic.
            virtual void logic()
            {
                if (this->valid())
                    this->load();
                else
                {
                    this->fill();
                    this->dump();
                }
            }

        private:
            const std::string _path;
    };

} // namespace herdstat

#endif /* _HAVE_CACHABLE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
