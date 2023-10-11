/*
 * libherdstat -- herdstat/fetcher/exceptions.cc
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

#include <herdstat/fetcher/exceptions.hh>

namespace herdstat {
/****************************************************************************/
FetchException::FetchException() throw()
    : Exception()
{
}
/****************************************************************************/
FetchException::FetchException(const std::string& msg) throw()
    : Exception(msg)
{
}
/****************************************************************************/
FetchException::~FetchException() throw()
{
}
/****************************************************************************/
UnimplementedFetchMethod::UnimplementedFetchMethod
    (const std::string& imp) throw()
    : Exception(imp)
{
}
/****************************************************************************/
UnimplementedFetchMethod::~UnimplementedFetchMethod() throw()
{
}
/****************************************************************************/
const char *
UnimplementedFetchMethod::what() const throw()
{
    std::string msg("Unimplemented fetch method '");
    msg += std::string(this->message()) +
        "'.\nWas support for this method compiled in?";
    return msg.c_str();
}
/****************************************************************************/
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
