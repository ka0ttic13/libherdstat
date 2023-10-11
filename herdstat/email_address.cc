/*
 * libherdstat -- herdstat/email_address.cc
 * $Id: email_address.cc 155 2005-11-27 13:37:27Z ka0ttic $
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

#include <herdstat/exceptions.hh>
#include <herdstat/email_address.hh>

namespace herdstat {
/****************************************************************************/
EmailAddress::EmailAddress() throw()
    : _email(), _user(), _domain()
{
}
/****************************************************************************/
EmailAddress::EmailAddress(const std::string& email) throw (MalformedEmail)
    : _email(), _user(), _domain()
{
    if (not this->parse(email))
        throw MalformedEmail(email);
}
/****************************************************************************/
EmailAddress::EmailAddress(const std::string& user,
                           const std::string& domain) throw (MalformedEmail)
    : _email(user+"@"+domain), _user(user), _domain(domain)
{
    if (domain.empty())
        throw MalformedEmail(_email);
}
/****************************************************************************/
EmailAddress::~EmailAddress() throw()
{
}
/****************************************************************************/
bool
EmailAddress::parse(const std::string& email) throw()
{
    std::string::size_type pos = email.find('@');
    if (pos == std::string::npos)
    {
        _user.assign(email);
        return false;
    }

    _user.assign(email.substr(0, pos));
    _domain.assign(email.substr(pos+1));
    _email.assign(email);
    
    return true;
}
/****************************************************************************/
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
