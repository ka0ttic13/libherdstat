/*
 * libherdstat -- herdstat/libherdstat_version.hh
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

#ifndef _HAVE_HERDSTAT_LIBHERDSTAT_VERSION_HH
#define _HAVE_HERDSTAT_LIBHERDSTAT_VERSION_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/libherdstat_version.hh
 * @brief Provides libherdstat version constants.
 */

/**
 * @def LIBHERDSTAT_VERSION_MAJOR
 * @brief Major version (eg 0.4.1 -> 0).
 */

#define LIBHERDSTAT_VERSION_MAJOR 0

/**
 * @def LIBHERDSTAT_VERSION_MINOR
 * @brief Minor version (eg 0.4.1 -> 4).
 */

#define LIBHERDSTAT_VERSION_MINOR 2

/**
 * @def LIBHERDSTAT_VERSION_MICRO
 * @brief Micro version (eg 0.4.1 -> 1).
 */

#define LIBHERDSTAT_VERSION_MICRO 0

/**
 * @def LIBHERDSTAT_VERSION_STRING
 * @brief Full version string with delimiters.
 */

#define LIBHERDSTAT_VERSION_STRING \
            LIBHERDSTAT_VERSION_MAJOR"."LIBHERDSTAT_VERSION_MINOR"."LIBHERDSTAT_VERSION_MICRO

/**
 * @def LIBHERDSTAT_VERSION
 * @brief Version, two digits per part (eg 0.4.1 -> 00401)
 */

#define LIBHERDSTAT_VERSION ((100 * 100 * LIBHERDSTAT_VERSION_MAJOR) \
	    + (100 * LIBHERDSTAT_VERSION_MINOR) + LIBHERDSTAT_VERSION_MICRO)

/**
 * @def LIBHERDSTAT_BUILD_CXX
 * @brief C++ compiler used at build time.
 */

#define LIBHERDSTAT_BUILD_CXX i686-pc-linux-gnu-g++

/**
 * @def LIBHERDSTAT_BUILD_CXXFLAGS
 * @brief CXXFLAGS used at build time.
 */

#define LIBHERDSTAT_BUILD_CXXFLAGS -g -O2 -pedantic -ansi -W -Wextra -Wall -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -ggdb3

/**
 * @def LIBHERDSTAT_BUILD_LDFLAGS
 * @brief LDFLAGS used at build time.
 */

#define LIBHERDSTAT_BUILD_LDFLAGS 

#endif /* _HAVE_HERDSTAT_LIBHERDSTAT_VERSION_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
