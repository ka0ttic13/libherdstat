/*
 * libherdstat -- tests/src/herds.xml-test.hh
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

#ifndef _HAVE__HERDS_XML_TEST_HH
#define _HAVE__HERDS_XML_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/xml/init.hh>
#include <herdstat/portage/herds_xml.hh>

#include "test_handler.hh"

DECLARE_TEST_HANDLER(HerdsXMLTest)

struct DisplayDev
{
    void operator()(const herdstat::portage::Developer& dev) const
    {
        std::cout << "  " << dev.user() << std::endl;
    }
};

void
HerdsXMLTest::operator()(const opts_type& opts) const
{
    assert(not opts.empty());
    assert(herdstat::util::is_file(opts.front()));

    herdstat::xml::GlobalInit();

    herdstat::portage::HerdsXML herds_xml;
    herds_xml.parse(opts.front());
    const herdstat::portage::Herds& herds(herds_xml.herds());
    assert(not herds.empty());

    std::cout << "Size: " << herds.size() << std::endl;

    herdstat::portage::Herds::const_iterator i = herds.find("shell-tools");
    assert(i != herds.end());

    std::cout << i->name() << "(" << i->size() << ")" << std::endl;
    std::for_each(i->begin(), i->end(), DisplayDev());
}

#endif /* _HAVE__HERDS.XML_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
