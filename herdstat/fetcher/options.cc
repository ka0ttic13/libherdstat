/*
 * libherdstat -- herdstat/fetcher/options.cc
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

#include <cstdlib>
#include <herdstat/fetcher/options.hh>

namespace herdstat {
/****************************************************************************/
FetcherOptions::FetcherOptions() throw()
    : _verbose(false), _debug(false), _imp(DEFAULT_FETCH_METHOD)
{
    const char * const result = std::getenv("HERDSTAT_FETCH_METHOD");
    if (result)
        _imp.assign(result);
}
/****************************************************************************/
FetcherOptions::FetcherOptions(const std::string& imp) throw()
    : _verbose(false), _debug(false), _imp(imp)
{
}
/****************************************************************************/
FetcherOptions::~FetcherOptions() throw()
{
}
/****************************************************************************/
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
