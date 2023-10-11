/*
 * libherdstat -- herdstat/portage/gentoo_email_address.cc
 * $Id: gentoo_email_address.cc 155 2005-11-27 13:37:27Z ka0ttic $
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
#include <herdstat/portage/gentoo_email_address.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
GentooEmailAddress::GentooEmailAddress() throw()
    : EmailAddress()
{
}
/****************************************************************************/
GentooEmailAddress::GentooEmailAddress(const std::string& email)
    throw(MalformedEmail)
    : EmailAddress()
{
    this->assign(email);
}
/****************************************************************************/
GentooEmailAddress::~GentooEmailAddress() throw()
{
}
/****************************************************************************/
bool
GentooEmailAddress::parse(const std::string& email) throw()
{
    if (not EmailAddress::parse(email))
        this->set_domain("gentoo.org");
    return true;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
