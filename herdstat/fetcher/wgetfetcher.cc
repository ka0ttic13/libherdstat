/*
 * libherdstat -- herdstat/fetcher/wgetfetcher.cc
 * $Id: wgetfetcher.cc 148 2005-11-25 12:03:55Z ka0ttic $
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <cstdlib>
#include <herdstat/util/string.hh>
#include <herdstat/fetcher/exceptions.hh>
#include <herdstat/fetcher/wgetfetcher.hh>

namespace herdstat {
/****************************************************************************/
WgetFetcher::WgetFetcher(const FetcherOptions& opts) throw()
    : FetcherImp(opts)
{
}
/****************************************************************************/
WgetFetcher::~WgetFetcher() throw()
{
}
/****************************************************************************/
bool
WgetFetcher::fetch(const std::string& url, const std::string& path) const
    throw (FileException)
{
    BacktraceContext c("WgetFetcher::fetch("+url+", "+path+")");

    std::string opts("-r -t3 -T15");
    opts += (options().verbose() ? " -v" : " -q");

    return (std::system(util::sprintf("%s %s -O %s '%s'", WGET,
                opts.c_str(), path.c_str(),
                url.c_str()).c_str()) == EXIT_SUCCESS);
}
/****************************************************************************/
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
