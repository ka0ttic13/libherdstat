/*
 * libherdstat -- tests/src/keyword-test.hh
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

#ifndef _HAVE__KEYWORD_TEST_HH
#define _HAVE__KEYWORD_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/portage/keywords.hh>

#include "test_handler.hh"

DECLARE_TEST_HANDLER(KeywordTest)

inline void
display_keywords(const herdstat::portage::Keywords& keywords)
{
    std::transform(keywords.begin(), keywords.end(),
        std::ostream_iterator<std::string>(std::cout, "\n"),
        std::mem_fun_ref(&herdstat::portage::Keyword::str));
}

void
KeywordTest::operator()(const opts_type& opts) const
{
    assert(not opts.empty());

    std::cout << "Testing keyword sorting:" << std::endl;
    herdstat::portage::Keywords keywords(opts.front());
    std::cout << "'"
        << herdstat::util::strip_colors(keywords.str()) << "'" << std::endl;
    std::cout << std::endl
        << "Testing keyword iterator:" << std::endl;
    display_keywords(keywords);
    std::cout << "All testing? " << std::boolalpha
        << keywords.all_testing() << std::endl;

    std::cout << std::endl
        << "Testing all_testing():" << std::endl;
    std::vector<std::string> v;
    v.push_back("~x86"); v.push_back("~alpha"); v.push_back("~mips");
    keywords.clear();
    keywords.insert(v.begin(), v.end());
    display_keywords(keywords);
    std::cout << "All testing? " << keywords.all_testing() << std::endl;
    std::cout << "All stable? " << keywords.all_stable() << std::endl;

    v.clear();
    v.push_back("x86"); v.push_back("alpha");
    keywords.clear();
    keywords.insert(v.begin(), v.end());
    std::cout << std::endl << "Testing all_stable():" << std::endl;

    display_keywords(keywords);
    std::cout << "All stable? " << keywords.all_stable() << std::endl;
}

#endif /* _HAVE__KEYWORD_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
