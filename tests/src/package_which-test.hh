/*
 * libherdstat -- tests/src/package_which-test.hh
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

#ifndef _HAVE__PACKAGE_WHICH_TEST_HH
#define _HAVE__PACKAGE_WHICH_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/portage/config.hh>
#include <herdstat/portage/package_which.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(PackageWhichTest)

void
PackageWhichTest::operator()(const opts_type& null LIBHERDSTAT_UNUSED) const
{
    herdstat::portage::PackageList pkgs;
    const std::string& portdir(herdstat::portage::GlobalConfig().portdir());

    herdstat::portage::PackageWhich which;
    const std::vector<std::string>& results(which("foo", pkgs));
    assert(results.size() == 1);
    const std::string& result(results.front());

    std::cout << result.substr(portdir.length()+1) << std::endl;
}

#endif /* _HAVE__PACKAGE_WHICH_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
