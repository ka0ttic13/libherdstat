/*
 * libherdstat -- herdstat/util/glob.cc
 * $Id: glob.cc 211 2005-12-22 16:11:20Z ka0ttic $
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

#include <iostream>
#include <glob.h>
#include <herdstat/exceptions.hh>
#include <herdstat/util/glob.hh>

namespace herdstat {
namespace util {
/****************************************************************************/
Glob::Glob() throw()
    : _results()
{

}
/****************************************************************************/
Glob::Glob(const std::string& pattern) throw (ErrnoException)
    : _results()
{
    this->operator()(pattern);
}
/****************************************************************************/
Glob::~Glob() throw()
{
}
/****************************************************************************/
const std::vector<std::string>&
Glob::operator()(const std::string& pattern) throw (ErrnoException)
{
    BacktraceContext c("herdstat::util::Glob::operator()("+pattern+")");

    glob_t globbuf;

    int ret = glob(pattern.c_str(), GLOB_ERR, NULL, &globbuf);
    if (ret != 0 and ret != GLOB_NOMATCH)
        throw ErrnoException("glob");

    /* fill _results */
    if (ret != GLOB_NOMATCH)
        _results.insert(_results.end(),
                        globbuf.gl_pathv, globbuf.gl_pathv + globbuf.gl_pathc);

    globfree(&globbuf);

    /* there may be duplicates due to previous calls to operator(). */
    if ((ret != GLOB_NOMATCH) and (_results.size() > 1))
    {
        std::sort(_results.begin(), _results.end());
        _results.erase(std::unique(_results.begin(), _results.end()),
            _results.end());
    }

    return _results;
}
/****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
