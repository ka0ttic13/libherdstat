/*
 * libherdstat -- tests/src/ebuild-test.hh
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

#ifndef _HAVE_SRC_EBUILD_TEST_HH
#define _HAVE_SRC_EBUILD_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/portage/ebuild.hh>
#include "vars-test.hh" /* for ShowVarAndVal */
#include "test_handler.hh"

DECLARE_TEST_HANDLER(EbuildTest)

struct ShowEbuild
    : std::binary_function<herdstat::portage::Ebuild, std::string, void>
{
    void operator()(const herdstat::portage::Ebuild& ebuild,
                    const std::string& portdir) const
    {
        std::cout << "Showing ebuild variables for '"
            << ebuild.path().substr(portdir.length()+1) << "'." << std::endl;
        std::for_each(ebuild.begin(), ebuild.end(), ShowVarAndVal());
    }
};

void
EbuildTest::operator()(const opts_type& opts) const
{
    assert(not opts.empty());
    const herdstat::portage::Ebuild ebuild(opts.front());
    std::for_each(ebuild.begin(), ebuild.end(), ShowVarAndVal());
}

#endif /* _HAVE_SRC_EBUILD_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
