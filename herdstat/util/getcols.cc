/*
 * libherdstat -- herdstat/util/getcols.cc
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <curses.h>
#include <term.h>

#include <herdstat/exceptions.hh>
#include <herdstat/util/getcols.hh>

namespace herdstat {
namespace util {

std::size_t
getcols()
{
    static bool term_init = false;
    static char term_info[2048];

    if (not term_init)
    {
        const char * const type = std::getenv("TERM");
        if (not type)
        {
            if (setenv("TERM", "vt100", 0) != 0)
                throw Exception("Failed to setenv(TERM, \"vt100\")");
        }

        int result = tgetent(term_info, std::getenv("TERM"));
        if (result < 0)
            throw Exception("Failed to access termcap database.");
        else if (result == 0)
            throw Exception("Unknown terminal type '%s'", type);

        term_init = true;
    }

    int cols = tgetnum("co");
    return (cols > 0 ? cols : 78);
}

} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
