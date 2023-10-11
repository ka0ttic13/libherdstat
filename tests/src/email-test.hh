/*
 * libherdstat -- tests/src/email-test.hh
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

#ifndef _HAVE_SRC_EMAIL_TEST_HH
#define _HAVE_SRC_EMAIL_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/exceptions.hh>
#include <herdstat/portage/gentoo_email_address.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(EmailTest)

void
EmailTest::operator()(const opts_type& null LIBHERDSTAT_UNUSED) const
{
    try
    {
        std::cout << "Testing EmailAddress (malformed):" << std::endl;
        herdstat::EmailAddress e1("ka0ttic");
    }
    catch (const herdstat::MalformedEmail& e)
    {
        std::cout << "Caught expected exception 'MalformedEmail' with what() = '"
            << e.what() << "'." << std::endl << std::endl;
    }

    std::cout << "Testing EmailAddress:" << std::endl;
    herdstat::EmailAddress e("ka0ttic@foo.org");
    std::cout << "EmailAddress e(ka0ttic@foo.org)" << std::endl;
    std::cout << "e = " << e.str() << std::endl;
    std::cout << "e.user() == " << e.user() << std::endl;
    std::cout << "e.domain() == " << e.domain() << std::endl;
    e.set_user("bob");
    std::cout << "e.set_user(bob)" << std::endl;
    std::cout << "e = " << e.str() << std::endl;
    std::cout << "e.user() == " << e.user() << std::endl;
    std::cout << "e.domain() == " << e.domain() << std::endl;
    std::cout << "EmailAddress::operator=(foo@bar.com)" << std::endl;
    e = "foo@bar.com";
    std::cout << "e = " << e.str() << std::endl;
    std::cout << "e.user() == " << e.user() << std::endl;
    std::cout << "e.domain() == " << e.domain() << std::endl;

    std::cout << std::endl << "Testing GentooEmailAddress:" << std::endl;
    herdstat::portage::GentooEmailAddress g("ka0ttic");
    std::cout << "GentooEmailAddress g(ka0ttic);" << std::endl;
    std::cout << "g = " << g.str() << std::endl;
    std::cout << "g.user() = " << g.user() << std::endl;
    std::cout << "g.domain() = " << g.domain() << std::endl;

    g.set_domain("foo.org");
    std::cout << "g.set_domain(foo.org)" << std::endl;
    std::cout << "g = " << g.str() << std::endl;
    std::cout << "g.user() = " << g.user() << std::endl;
    std::cout << "g.domain() = " << g.domain() << std::endl;
}

#endif /* _HAVE_SRC_EMAIL_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
