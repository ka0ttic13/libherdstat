/*
 * libherdstat -- tests/src/binaryio-test.hh
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

#ifndef _HAVE_SRC_BINARYIO_TEST_HH
#define _HAVE_SRC_BINARYIO_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <vector>
#include <unistd.h>
#include <herdstat/io/binary_stream_iterator.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(BinaryIO)

void
BinaryIO::operator()(const opts_type& null LIBHERDSTAT_UNUSED) const
{
    std::cout << "Testing BinaryOStream... " << std::endl;

    {
        herdstat::io::BinaryOStream stream("foo");
        if (not stream)
            throw herdstat::FileException("foo");

        size_t i = 10;
        stream << i;
        std::cout << "wrote '" << i << "'." << std::endl;

        stream << "This is a test.";
        std::cout << "wrote 'This is a test.'." << std::endl;
    
        std::string foo("foo");
        stream << foo;
        std::cout << "wrote 'foo'." << std::endl;
    }

    assert(herdstat::util::is_file("foo"));

    {
        std::cout << std::endl
            << "Testing BinaryIStream on the binary stream we just wrote..."
            << std::endl;

        herdstat::io::BinaryIStream stream("foo");
        if (not stream)
            throw herdstat::FileException("foo");

        size_t ival = 5;
        stream >> ival;
        std::cout << "read value '" << ival << "'." << std::endl;
        assert(ival == 10);

        std::string test;
        stream >> test;
        std::cout << "read value '" << test << "'." << std::endl;
        assert(test == "This is a test.");

        std::string foo;
        stream >> foo;
        std::cout << "read value '" << foo << "'." << std::endl;
        assert(foo == "foo");
    }

    unlink("foo");

    std::vector<std::string> s;
    s.push_back("foo");
    s.push_back("bar");
    s.push_back("baz");
    
    {
        std::cout << "Testing BinaryOStreamIterator..." << std::endl;

        herdstat::io::BinaryOStream stream("bar");
        if (not stream)
            throw herdstat::FileException("bar");

        std::cout << "s = '";
        std::copy(s.begin(), s.end(),
            std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << "'." << std::endl;

        std::copy(s.begin(), s.end(),
            herdstat::io::BinaryOStreamIterator<std::string>(stream));
    }

    assert(herdstat::util::is_file("bar"));

    {
        std::cout << "Testing BinaryIStreamIterator..." << std::endl;

        herdstat::io::BinaryIStream stream("bar");
        if (not stream)
            throw herdstat::FileException("bar");

        herdstat::io::BinaryIStreamIterator<std::string> strEOF;

        std::vector<std::string> s2(
                herdstat::io::BinaryIStreamIterator<std::string>(stream), strEOF);

        std::cout << "s2 = '";
        std::copy(s2.begin(), s2.end(),
            std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << "'." << std::endl;

        assert(s == s2);
    }

    unlink("bar");
}

#endif /* _HAVE_SRC_BINARYIO_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
