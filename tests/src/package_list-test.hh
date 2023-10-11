/*
 * libherdstat -- tests/src/package_list-test.hh
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

#ifndef _HAVE__PACKAGE_LIST_TEST_HH
#define _HAVE__PACKAGE_LIST_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/algorithm.hh>
#include <herdstat/util/functional.hh>
#include <herdstat/portage/functional.hh>
#include <herdstat/portage/config.hh>
#include <herdstat/portage/package_list.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(PackageListTest)

void
PackageListTest::operator()(const opts_type& null LIBHERDSTAT_UNUSED) const
{
    herdstat::portage::PackageList pkgs;

    std::cout << "Package List:" << std::endl;

    herdstat::util::transform_if(pkgs.begin(), pkgs.end(),
        std::ostream_iterator<std::string>(std::cout, "\n"),
        herdstat::util::compose_f_gx(
            herdstat::portage::IsPkgDir(),
            std::mem_fun_ref(&herdstat::portage::Package::path)),
        std::mem_fun_ref(&herdstat::portage::Package::full));
}

#endif /* _HAVE__PACKAGE_LIST_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
