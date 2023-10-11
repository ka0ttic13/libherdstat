/*
 * libherdstat -- tests/src/vars-test.hh
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

#ifndef _HAVE_SRC_VARS_TEST_HH
#define _HAVE_SRC_VARS_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/vars.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(VarsTest)

struct ShowVarAndVal
{
    void operator()(const std::pair<const std::string, std::string>& v) const
    {
        if (v.first != "HOME")
            std::cout << "  Variable '" << v.first << "' has a value of '"
                << v.second << "'." << std::endl;
    }
};

void
VarsTest::operator()(const opts_type& opts) const
{
    assert(not opts.empty());
    const std::string& path(opts.front());
    assert(herdstat::util::is_file(path));

    const std::string& portdir(herdstat::portage::GlobalConfig().portdir());

    std::cout << "Testing util::Vars(" << path.substr(portdir.length()+1)
        << "):" << std::endl;
    herdstat::util::Vars vars(path);
    std::for_each(vars.begin(), vars.end(), ShowVarAndVal());
}

#endif /* _HAVE_SRC_VARS_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
