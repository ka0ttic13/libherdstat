/*
 * libherdstat -- tests/src/version-test.hh
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

#ifndef _HAVE__VERSION_TEST_HH
#define _HAVE__VERSION_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/file.hh>
#include <herdstat/portage/util.hh>
#include <herdstat/portage/version.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(VersionTest)

void
VersionTest::operator()(const opts_type& opts) const
{
    assert(not opts.empty());

    std::cout << "Testing VersionString:" << std::endl;

    {
        const herdstat::util::Directory dir(opts.front());
        herdstat::util::Directory::const_iterator d;
        for (d = dir.begin() ; d != dir.end() ; ++d)
        {
            if (herdstat::portage::is_ebuild(*d))
            {
                herdstat::portage::VersionString ver(*d);
                std::cout << "  found version '" << ver.str() << "'." << std::endl;
            }
        }
    }

    std::cout << std::endl
        << "Testing sorted VersionString container:" << std::endl;

    std::string ebuild;

    const herdstat::portage::Versions versions(opts.front());
    herdstat::portage::Versions::const_iterator i;
    for (i = versions.begin() ; i != versions.end() ; ++i)
    {
        std::cout << "  " << i->str() << std::endl;    
        ebuild.assign(i->ebuild());
    }

    std::cout << std::endl
        << "Testing VersionComponents:" << std::endl;
    
    const herdstat::portage::VersionComponents vmap(ebuild);
    herdstat::portage::VersionComponents::const_iterator v;
    for (v = vmap.begin() ; v != vmap.end() ; ++v)
        std::cout << "  " << v->first << " = " << v->second << std::endl;
}

#endif /* _HAVE__VERSION_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
