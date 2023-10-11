/*
 * libherdstat -- tests/src/metadata.xml-test.hh
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

#ifndef _HAVE__METADATA_XML_TEST_HH
#define _HAVE__METADATA_XML_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/functional.hh>
#include <herdstat/portage/metadata_xml.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(MetadataXMLTest)

void
MetadataXMLTest::operator()(const opts_type& opts) const
{
    assert(not opts.empty());

    herdstat::xml::GlobalInit();

    herdstat::portage::MetadataXML meta(opts.front());
    const herdstat::portage::Herds& herds(meta.herds());
    const herdstat::portage::Developers& devs(meta.devs());

    std::cout << "herds: ";
    std::transform(herds.begin(), herds.end(),
        std::ostream_iterator<std::string>(std::cout, "\n"),
        herdstat::util::compose_f_gx(
            std::bind2nd(std::plus<std::string>(), " "),
            std::mem_fun_ref(&herdstat::portage::Herd::name)
        ));

    std::cout << "devs: ";
    std::transform(devs.begin(), devs.end(),
        std::ostream_iterator<std::string>(std::cout, "\n"),
        herdstat::util::compose_f_gx(
            std::bind2nd(std::plus<std::string>(), " "),
            std::mem_fun_ref(&herdstat::portage::Developer::user)
        ));

    if (not meta.longdesc().empty())
    {
        std::cout << "longdesc: " << meta.longdesc() << std::endl;
        std::cout << "tidy longdesc: "
            << herdstat::util::tidy_whitespace(meta.longdesc()) << std::endl;
    }
}

#endif /* _HAVE__METADATA.XML_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
