/*
 * libherdstat -- tests/src/string-test.hh
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

#ifndef _HAVE__STRING_TEST_HH
#define _HAVE__STRING_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/string.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(StringTest)

void
StringTest::operator()(const opts_type& null LIBHERDSTAT_UNUSED) const
{
    std::string s("Mary had a little lamb!");
    std::cout << s << std::endl;
    
    /* test util::split() */
    std::vector<std::string> v;
    herdstat::util::split(s, std::back_inserter(v));
    assert(v.size() == 5);
    std::vector<std::string>::iterator i;
    std::cout << "[ ";
    for (i = v.begin() ; i != v.end() ; ++i)
    {
        std::cout << "'" << *i << "'";
        if ((i+1) != v.end())
            std::cout << ", ";
    }
    std::cout << " ]" << std::endl;

    /* util::lowercase/util::join */
    std::cout << herdstat::util::lowercase(
                    herdstat::util::join(v.begin(), v.end())) << std::endl;

    /* util::destringify */
    std::cout
        << herdstat::util::destringify<int>("10") << std::endl
        << herdstat::util::destringify<long>("01") << std::endl
        << herdstat::util::destringify<unsigned long>("385233535") << std::endl
        << herdstat::util::destringify<float>("4.29") << std::endl
        << herdstat::util::destringify<bool>("false") << std::endl;

    /* util::strip_colors */
    const std::string c("This is a \033[0;31mtest\033[00m");
    std::cout << c << std::endl;
    std::cout << herdstat::util::strip_colors(c) << std::endl;
}

#endif /* _HAVE__STRING_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
