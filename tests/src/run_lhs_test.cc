/*
 * libherdstat -- tests/src/run_lhs_test.cc
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

#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

#include <herdstat/exceptions.hh>
#include <herdstat/util/functional.hh>

#include "binaryio-test.hh"
#include "string-test.hh"
#include "file-test.hh"
#include "vars-test.hh"
#include "container_base-test.hh"
#include "glob-test.hh"
#include "regex-test.hh"
#include "algo-test.hh"
#include "version-test.hh"
#include "keyword-test.hh"
#include "license-test.hh"
#include "ebuild-test.hh"
#include "email-test.hh"
#include "package_list-test.hh"
#include "package_finder-test.hh"
#include "package_which-test.hh"
#include "package_directory-test.hh"
#include "herds.xml-test.hh"
#include "devaway.xml-test.hh"
#include "userinfo.xml-test.hh"
#include "metadata.xml-test.hh"

int
main(int argc, char **argv)
{
    try
    {
        typedef std::map<std::string, TestHandler *> TestsMap;

        if (argc < 2)
            throw herdstat::Exception("usage: run_lhs_test <test> <test opts>");

        std::string test_id(argv[1]);

        opts_type opts;
        if (argc > 2)
            std::copy(argv+2, argv+argc, std::back_inserter(opts));

        TestsMap tests;
        
        tests["binaryio"] = new BinaryIO();
        tests["string"] = new StringTest();
        tests["file"] = new FileTest();
        tests["vars"] = new VarsTest();
        tests["container_base"] = new ContainerBaseTest();
        tests["glob"] = new GlobTest();
        tests["regex"] = new RegexTest();
        tests["algo"] = new AlgoTest();
        tests["version"] = new VersionTest();
        tests["keyword"] = new KeywordTest();
        tests["license"] = new LicenseTest();
        tests["ebuild"] = new EbuildTest();
        tests["email"] = new EmailTest();
        tests["package_list"] = new PackageListTest();
        tests["package_finder"] = new PackageFinderTest();
        tests["package_which"] = new PackageWhichTest();
        tests["package_directory"] = new PackageDirectoryTest();
        tests["herds.xml"] = new HerdsXMLTest();
        tests["devaway.xml"] = new DevawayXMLTest();
        tests["userinfo.xml"] = new UserinfoXMLTest();
        tests["metadata.xml"] = new MetadataXMLTest();

        TestHandler *test = tests[test_id];
        if (not test)
            throw herdstat::Exception("Unknown test '"+test_id+"'.");

        (*test)(opts);

        /* delete the TestHandler pointer for each element in the tests map */
        std::for_each(tests.begin(), tests.end(),
            herdstat::util::compose_f_gx(
                    herdstat::util::DeleteAndNullify<TestHandler>(),
                    herdstat::util::Second<TestsMap::value_type>()
                ));
    }
    catch (const herdstat::BaseException& e)
    {
        std::cerr << e.backtrace(":\n  * ") << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* vim: set tw=80 sw=4 fdm=marker et : */
