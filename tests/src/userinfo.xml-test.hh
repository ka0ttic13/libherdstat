/*
 * libherdstat -- tests/src/userinfo.xml-test.hh
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

#ifndef _HAVE__USERINFO_XML_TEST_HH
#define _HAVE__USERINFO_XML_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/portage/userinfo_xml.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(UserinfoXMLTest)

void
UserinfoXMLTest::operator()(const opts_type& opts) const
{
    assert(opts.size() == 2);

    herdstat::xml::GlobalInit();

    const std::string& path(opts.front());
    const std::string& dev(opts.back());

    herdstat::portage::UserinfoXML userinfo(path);
    const herdstat::portage::Developers& devs = userinfo.devs();

    std::cout << "Size: " << devs.size() << std::endl;

    herdstat::portage::Developers::const_iterator i = devs.find(dev);
    if (i == devs.end())
        throw herdstat::Exception(dev + " doesn't seem to exist.");

    std::cout << "Name:       " << i->name() << "(" << i->user() << ")" << std::endl;
    std::cout << "Email:      " << i->email() << std::endl;
    std::cout << "PGP Key ID: " << i->pgpkey() << std::endl;
    std::cout << "Joined on:  " << i->joined() << std::endl;
    std::cout << "Birthday:   " << i->birthday() << std::endl;
    std::cout << "Status:     " << i->status() << std::endl;
    std::cout << "Roles:      " << i->role() << std::endl;
    std::cout << "Location:   " << i->location() << std::endl;
}

#endif /* _HAVE__USERINFO.XML_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
