/*
 * libherdstat -- tests/src/glob-test.hh
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

#ifndef _HAVE__GLOB_TEST_HH
#define _HAVE__GLOB_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <algorithm>
#include <iterator>
#include <functional>
#include <herdstat/util/glob.hh>
#include <herdstat/util/functional.hh>
#include <unistd.h>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(GlobTest)

void
GlobTest::operator()(const opts_type& null LIBHERDSTAT_UNUSED) const
{
    /* test Glob */
    char *test_data = std::getenv("TEST_DATA");
    assert(test_data);
    
    if (chdir(test_data) != 0)
        throw herdstat::ErrnoException("chdir");

    herdstat::util::Glob glob("portdir/app-lala/*/*.ebuild");
    glob("portdir/app-misc/foo/*.ebuild");
    glob("portdir/*/*/*.ebuild");
    const std::vector<std::string>& results(glob.results());
    std::copy(results.begin(), results.end(),
        std::ostream_iterator<std::string>(std::cout, "\n"));

    /* test patternMatch functor */
    std::vector<std::string>::size_type n =
        std::count_if(results.begin(), results.end(),
            std::bind2nd(herdstat::util::patternMatch(), "*foo-1.10*"));
    if (n == 0)
        throw herdstat::Exception("*foo-1.10* not found in results vector.");

    std::cout << std::endl
        << "The pattern '*foo-1.10*' appears " << n
        << " times in the output above." << std::endl;
}

#endif /* _HAVE__GLOB_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
