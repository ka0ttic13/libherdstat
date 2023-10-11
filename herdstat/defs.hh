/*
 * libherdstat -- herdstat/defs.hh
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

#ifndef _HAVE_HERDSTAT_DEFS_HH
#define _HAVE_HERDSTAT_DEFS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/defs.hh
 * @brief Provides some common #define's.
 */

#define NELEMS(x) (sizeof(x) / sizeof(x[0]))

#ifndef LIBHERDSTAT_DEPRECATED
# if defined(__GNUC__) || defined(DOXYGEN)
#   define LIBHERDSTAT_DEPRECATED __attribute__ ((deprecated))
# else
#   define LIBHERDSTAT_DEPRECATED
# endif
#endif

#ifndef LIBHERDSTAT_UNUSED
# if defined(__GNUC__) || defined(DOXYGEN)
#   define LIBHERDSTAT_UNUSED __attribute__ ((unused))
# else
#   define LIBHERDSTAT_UNUSED
# endif
#endif

#endif /* _HAVE_HERDSTAT_DEFS_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
