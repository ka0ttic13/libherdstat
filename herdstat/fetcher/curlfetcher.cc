/*
 * libherdstat -- herdstat/fetcher/curlfetcher.cc
 * $Id: curlfetcher.cc 194 2005-12-12 12:57:29Z ka0ttic $
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

#ifdef HAVE_LIBCURL
# include <cstdlib>
# include <cstdio>
# include <cassert>
# include <curl/curl.h>
#endif

#include <herdstat/fetcher/exceptions.hh>
#include <herdstat/fetcher/curlfetcher.hh>

namespace herdstat {
/****************************************************************************/
CurlFetcher::CurlFetcher(const FetcherOptions& opts) throw()
    : FetcherImp(opts)
{
}
/****************************************************************************/
CurlFetcher::~CurlFetcher() throw()
{
}
/****************************************************************************/
bool
CurlFetcher::fetch(const std::string& url, const std::string& path) const
    throw (FileException)
{
    BacktraceContext c("CurlFetcher::fetch("+url+", "+path+")");

#ifdef HAVE_LIBCURL
    FILE *fp = NULL;
    bool result = true;

    CURL *handle = curl_easy_init();
    if (not handle)
        throw Exception("curl_easy_init() returned NULL.");

    try
    {
        fp = std::fopen(path.c_str(), "w");
        if (not fp)
            throw FileException(path);

        /* set curl options */
        curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(handle, CURLOPT_NOPROGRESS, not options().verbose());
        curl_easy_setopt(handle, CURLOPT_FAILONERROR, 1);
        curl_easy_setopt(handle, CURLOPT_VERBOSE, options().debug());
        curl_easy_setopt(handle, CURLOPT_USERAGENT, PACKAGE);

        if (curl_easy_perform(handle) != 0)
            throw FetchException();
    }
    catch (const FileException& e)
    {
        curl_easy_cleanup(handle);
        throw e;
    }
    catch (const FetchException)
    {
        std::fclose(fp); fp = NULL;
        unlink(path.c_str());
        result = false;
    }

    if (fp) std::fclose(fp);
    curl_easy_cleanup(handle);

    return result;
#else
    return false;
#endif
}
/****************************************************************************/
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
