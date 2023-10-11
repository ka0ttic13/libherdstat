/*
 * libherdstat -- herdstat/doxygen.hh
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

#ifndef _HAVE_HERDSTAT_DOXYGEN_HH
#define _HAVE_HERDSTAT_DOXYGEN_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/doxygen.hh
 * @brief Main page documentation for Doxygen.
 */

/**
 * @mainpage libherdstat API Documentation
 *
 * @section overview Overview
 *
 * libherdstat is a C++ library that provides interfaces for things such as:
 * - Gentoo-specific XML files such as herds.xml (herdstat::portage::HerdsXML),
 *   userinfo.xml (herdstat::portage::UserinfoXML),
 *   devaway.xml (herdstat::portage::DevawayXML), and metadata.xml
 *   (herdstat::portage::MetadataXML).
 * - Portage configuration (herdstat::portage::Config).
 * - Portage package searching (herdstat::portage::PackageFinder).
 * - Developer/Herd containers (herdstat::portage::Developer,
 *   herdstat::portage::Developers, herdstat::portage::Herd,
 *   herdstat::portage::Herds).
 * - Version strings (herdstat::portage::VersionString,
 *   herdstat::portage::Versions, herdstat::portage::VersionsMap).
 * - Keyword strings (herdstat::portage::Keyword,
 *   herdstat::portage::Keywords, herdstat::portage::KeywordsMap).
 * - Ebuild LICENSE parsing (herdstat::portage::License).
 * - Portage-related functional objects for use with standard algorithms
 *   (herdstat/portage/functional.hh).
 * - File fetching (herdstat::Fetcher).
 * - POSIX regular expressions (herdstat::util::Regex).
 * - POSIX pattern matching (herdstat::util::Glob).
 * - Directory iterators (herdstat::util::Directory).
 * - Extensible progress meter interface (herdstat::util::ProgressMeter) with
 *   several different implementations (herdstat::util::PercentMeter,
 *   herdstat::util::EllipseMeter, herdstat::util::Spinner).
 * - String manipulation utilities (herdstat/util/string.hh).
 * - General purpose algorithms (herdstat/util/algorithms.hh) and functional
 *   objects (herdstat/util/functional.hh).
 * - Interfaces for readline's libreadline and libhistory
 *   (herdstat::readline::ReadLine and herdstat::readline::History
 *   respectively).
 * - Even more.
 *
 *
 * @section usage Usage
 *
 * To link your application with libherdstat, use the provided pkg-config file
 * via the pkg-config application:
 *
 * @verbatim
$ g++ myapp.cc -o myapp `pkg-config --libs --cflags libherdstat-MAJOR_VERSION.MINOR_VERSION`
@endverbatim
 *
 * Where MAJOR_VERSION and MINOR_VERSION are libherdstat's major and minor
 * version number, respectively.  For example, with libherdstat-0.2.0, you'd use
 * 'libherdstat-0.2'.
 *
 * If your application uses GNU autoconf, you can use the PKG_CHECK_MODULES
 * macro provided by the pkg-config application in your application's
 * configure.ac:
 *
 * @verbatim
PKG_CHECK_MODULES(libherdstat, libherdstat-0.2 >= 0.2.5)
@endverbatim
 * 
 * See the pkg-config(1) manual page for more detailed usage information.
 *
 * @section examples Examples
 *
 * Since libherdstat provides a multitude of interfaces for various things, it's
 * not feasable to provide a single example (for that, see the <a
 * href="http://developer.berlios.de/projects/herdstat/">herdstat</a>
 * application).
 *
 * Instead, we provide individual examples for each major
 * interface.  See the documentation for the particular interface for example
 * code or the examples/ directory provided in the distribution tarball.
 * The smaller classes/functions only include small code snippets.
 */

/**
 * @page Authors Authors
 * @section Authors Authors
 * 
 * libherdstat was written by Aaron Walker <ka0ttic@gentoo.org>.
 */

/**
 * @page ChangeLog ChangeLog
 * @section ChangeLog ChangeLog
 * @verbinclude ChangeLog
 */

/**
 * @page License License
 * @section License License
 * @verbinclude COPYING
 */

/**
 * @namespace herdstat
 * @brief Main namespace all of libherdstat resides in.
 */

/**
 * @namespace herdstat::xml
 * @brief XML-related classes.
 */

/**
 * @namespace herdstat::util
 * @brief General-purpose utility classes/functions.
 */

/**
 * @namespace herdstat::io
 * @brief General-purpose input/output classes/functions.
 */

/**
 * @namespace herdstat::portage
 * @brief portage-related classes/functions.
 */

#endif /* _HAVE_HERDSTAT_DOXYGEN_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
