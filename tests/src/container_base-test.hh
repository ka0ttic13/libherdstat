/*
 * libherdstat -- tests/src/container_base-test.hh
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

#ifndef _HAVE__CONTAINER_BASE_TEST_HH
#define _HAVE__CONTAINER_BASE_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/container_base.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(ContainerBaseTest)

class MySet : public herdstat::util::SetBase<std::string>
{
    public:
        void display()
        {
            for (iterator i = this->begin() ; i != this->end() ; ++i)
                std::cout << *i << std::endl;
        }
};

#define TRY_INSERT(x) \
    if (not m.insert(#x).second) \
        std::cout << "Failed to insert " << #x << std::endl;

void
ContainerBaseTest::operator()(const opts_type& null LIBHERDSTAT_UNUSED) const
{
    MySet m;
    TRY_INSERT(foo);
    TRY_INSERT(bar);
    TRY_INSERT(baz);
    TRY_INSERT(foo);
    TRY_INSERT(foobarbaz);

    m.display();
}

#undef TRY_INSERT

#endif /* _HAVE__CONTAINER_BASE-TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
