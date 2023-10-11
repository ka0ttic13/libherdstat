/*
 * libherdstat -- herdstat/fetcher/impmap.cc
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/fetcher/curlfetcher.hh>
#include <herdstat/fetcher/wgetfetcher.hh>
#include <herdstat/fetcher/impmap.hh>

namespace herdstat {
/****************************************************************************/
FetcherImpMap::FetcherImpMap(const FetcherOptions& opts) throw()
    : _map(), _opts(opts)
{
#define INSERT_IMP(x, y) \
    assert(_map.insert(std::make_pair(#x, y)).second);

#ifdef HAVE_LIBCURL
    INSERT_IMP(curl, new CurlFetcher(_opts));
#endif
    INSERT_IMP(wget, new WgetFetcher(_opts));

#undef INSERT_IMP
}
/****************************************************************************/
FetcherImpMap::~FetcherImpMap() throw()
{
}
/****************************************************************************/
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
