/*
 * libherdstat -- tests/src/regex-test.hh
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

#ifndef _HAVE__REGEX_TEST_HH
#define _HAVE__REGEX_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/regex.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(RegexTest)

void
RegexTest::operator()(const opts_type& null LIBHERDSTAT_UNUSED) const
{
    std::cout << "Testing util::Regex:" << std::endl;

    const std::string word1("This is a test");
    const std::string word2("test a is This");

    const herdstat::util::Regex regex("test$");

    std::cout << "'" << regex() << "' == '" << word1 << "' ? "
        << (regex == word1) << std::endl;
    std::cout << "'" << regex() << "' == '" << word2 << "' ? "
        << (regex == word2) << std::endl;

    std::cout << std::endl << "Testing util::regexMatch():" << std::endl;

    std::vector<std::string> v;
    v.push_back(word2);
    v.push_back(word1);
    v.push_back("test");

    std::vector<std::string>::iterator i =
        std::find_if(v.begin(), v.end(),
            std::bind1st(herdstat::util::regexMatch(), regex));

    std::cout << "found '" << *i << "'." << std::endl;

    assert(*i == word1);
}

#endif /* _HAVE__REGEX_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
