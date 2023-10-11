/*
 * libherdstat -- tests/src/package_directory-test.hh
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

#ifndef _HAVE_SRC_PACKAGE_DIRECTORY_TEST_HH
#define _HAVE_SRC_PACKAGE_DIRECTORY_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/portage/package_directory.hh>
#include "file-test.hh" /* for ShowFileName */
#include "vars-test.hh" /* for ShowVarAndVal */
#include "ebuild-test.hh" /* for ShowEbuild */
#include "test_handler.hh"

DECLARE_TEST_HANDLER(PackageDirectoryTest)

void
PackageDirectoryTest::operator()(const opts_type& opts) const
{
    const std::string& portdir(herdstat::portage::GlobalConfig().portdir());

    assert(not opts.empty());
    const std::string& path(opts.front());
    assert(herdstat::util::is_dir(path));

    std::cout << "Testing portage::PackageDirectory("
        << path.substr(portdir.length()+1) << "):" << std::endl;
    herdstat::portage::PackageDirectory pkgdir(path);    
    std::for_each(pkgdir.begin(), pkgdir.end(),
        std::bind2nd(ShowFileName(), portdir));
    
    std::cout << std::endl
        << "Testing portage::PackageDirectory::ebuild_count():" << std::endl;
    std::cout << " Number of ebuilds present in "
        << path.substr(portdir.length()+1) << ": "
        << pkgdir.ebuild_count() << std::endl;

    std::cout << std::endl
        << "Testing portage::PackageDirectory::patches_count():" << std::endl;
    std::cout << " Number of patches present in "
        << path.substr(portdir.length()+1) << ": "
        << pkgdir.patches_count() << std::endl;

    std::cout << std::endl
        << "Testing portage::PackageDirectory::has_metadata():" << std::endl;
    std::cout << " Package directory " << path.substr(portdir.length()+1)
        << " has a metadata.xml? " << std::boolalpha << pkgdir.has_metadata()
        << std::endl;
    std::cout
        << "Removing metadata.xml from directory vector and re-testing has_metadata()."
        << std::endl;
    pkgdir.erase(pkgdir.find("metadata.xml"));
    std::cout << " Package directory " << path.substr(portdir.length()+1)
        << " has a metadata.xml? " << std::boolalpha << pkgdir.has_metadata()
        << std::endl;

    std::cout << std::endl
        << "Testing portage::PackageDirectory::ebuilds():" << std::endl;
    const std::vector<herdstat::portage::Ebuild>& ebuilds(pkgdir.ebuilds());
    std::for_each(ebuilds.begin(), ebuilds.end(),
            std::bind2nd(ShowEbuild(), portdir));
}

#endif /* _HAVE_SRC_PACKAGE_DIRECTORY_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
