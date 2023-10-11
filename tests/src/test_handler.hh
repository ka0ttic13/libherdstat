/*
 * libherdstat -- tests/src/test_handler.hh
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

#ifndef _HAVE_SRC_TEST_HANDLER_HH
#define _HAVE_SRC_TEST_HANDLER_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @class TestHandler
 * @brief Abstract base class for tests.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <cstdlib>

#include <herdstat/defs.hh>

typedef std::vector<std::string> opts_type;

class TestHandler
{
    public:
        virtual ~TestHandler() { }
        virtual void operator()(const opts_type&) const = 0;
};

#define DECLARE_TEST_HANDLER(x) \
    class x : public TestHandler \
    { \
        public: \
                virtual ~x() { } \
                virtual void operator()(const opts_type&) const; \
    };

#endif /* _HAVE_SRC_TEST_HANDLER_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
