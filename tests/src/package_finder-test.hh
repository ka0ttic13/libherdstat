/*
 * libherdstat -- tests/src/package_finder-test.hh
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

#ifndef _HAVE__PACKAGE_FINDER_TEST_HH
#define _HAVE__PACKAGE_FINDER_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/regex.hh>
#include <herdstat/portage/package_finder.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(PackageFinderTest)

void
PackageFinderTest::operator()(const opts_type& null LIBHERDSTAT_UNUSED) const
{
    herdstat::portage::PackageList pkgs;
    herdstat::portage::PackageFinder find(pkgs);
    const std::vector<herdstat::portage::Package>& results(find.results());

    try
    {
        std::cout << std::endl
            << "Testing PackageFinder with ambiguous package name" << std::endl;
        find.clear_results();
        find("libfoo");
        assert(results.size() > 1);
        throw herdstat::portage::AmbiguousPkg(results.begin(), results.end());
    }
    catch (const herdstat::portage::AmbiguousPkg& e)
    {
        std::cerr << "  libfoo is ambiguous, matches are:" << std::endl;
        std::vector<std::string>::const_iterator i;
        for (i = e.packages().begin() ; i != e.packages().end() ; ++i)
            std::cerr << "    " << *i << std::endl;
    }

    {
        std::cout << std::endl
            << "Testing PackageFinder" << std::endl;
        find.clear_results();
        find("pfft");
        assert(results.size() == 1);
        const herdstat::portage::Package& result(results.front());
        std::cout << "  " << result.full() << std::endl;
    }

    {
        std::cout << std::endl << "Testing PackageFinder w/regex:" << std::endl;
        find.clear_results();
        find(herdstat::util::Regex("^foo"));
        assert(results.size() > 1);
        std::vector<herdstat::portage::Package>::const_iterator i;
        for (i = results.begin() ; i != results.end() ; ++i)
            std::cout << "  Found " << i->full() << std::endl;
    }
}

#endif /* _HAVE__PACKAGE_FINDER_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
