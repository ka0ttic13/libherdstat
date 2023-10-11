/*
 * libherdstat -- herdstat/portage/gentoo_email_address.hh
 * $Id: gentoo_email_address.hh 155 2005-11-27 13:37:27Z ka0ttic $
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

#ifndef _HAVE_GENTOO_EMAIL_ADDRESS_HH
#define _HAVE_GENTOO_EMAIL_ADDRESS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/gentoo_email_address.hh
 * @brief Defines the GentooEmailAddress class.
 */

#include <herdstat/email_address.hh>

namespace herdstat {
namespace portage {

    /**
     * @class GentooEmailAddress gentoo_email_address.hh herdstat/portage/gentoo_email_address.hh
     * @brief A gentoo.org EmailAddress.
     */

    class GentooEmailAddress : public EmailAddress
    {
        public:
            /// Default constructor.
            GentooEmailAddress() throw();

            /** Constructor.
             * @param email email address string.
             * @exception MalformedEmail
             */
            GentooEmailAddress(const std::string& email) throw (MalformedEmail);

            /// Destructor.
            virtual ~GentooEmailAddress() throw();

        protected:
            /// Parse email address.
            virtual bool parse(const std::string& email) throw();
    };

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_GENTOO_EMAIL_ADDRESS_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
