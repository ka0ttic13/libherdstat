/*
 * libherdstat -- tests/src/file-test.hh
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

#ifndef _HAVE_SRC_FILE_TEST_HH
#define _HAVE_SRC_FILE_TEST_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/algorithm.hh>
#include <herdstat/util/functional.hh>
#include <herdstat/util/file.hh>
#include <herdstat/portage/config.hh>
#include "test_handler.hh"

DECLARE_TEST_HANDLER(FileTest)

struct ShowFileContents
{
    void operator()(const std::string& line) const
    {
        std::cout << "    " << line << std::endl;
    }
};

struct ShowFile : std::binary_function<herdstat::util::File, std::string, void>
{
    void operator()(const herdstat::util::File& file, const std::string& base) const
    {
        const std::string path(file.path().substr(base.length()+1));

        if (file.empty())
            std::cout << " File '" << path << "' is empty." << std::endl;
        else
        {
            std::cout << " File contents for '" << path << "'." << std::endl;
            std::for_each(file.begin(), file.end(), ShowFileContents());
        }
    }
};

struct ShowFileName
    : std::binary_function<std::string, std::string, void>
{
    void operator()(const std::string& path, const std::string& base) const
    {
        if (herdstat::util::Regex("\\.svn") == path)
            return;
        std::cout << " " << path.substr(base.length()+1) << std::endl;
    }
};

struct ShowDirectory
{
    void operator()(const herdstat::util::Directory& dir,
                    const std::string& portdir) const
    {
        std::for_each(dir.begin(), dir.end(),
            std::bind2nd(ShowFileName(), portdir));
        std::cout << std::endl;

        std::cout << "Testing util::File for each file in the previous util::Directory:"
            << std::endl;
        std::vector<herdstat::util::File> fv;
        herdstat::util::transform_if(dir.begin(), dir.end(),
            std::back_inserter(fv),
                /* only insert if it's a file and it
                 * doesn't contain '.svn' in the name */
                herdstat::util::compose_f_gx_hx(
                    std::logical_and<bool>(),
                    herdstat::util::IsFile(),
                    std::not1(std::bind1st(herdstat::util::regexMatch(), "\\.svn"))),
            herdstat::util::New<herdstat::util::File>());
        std::for_each(fv.begin(), fv.end(),
            std::bind2nd(ShowFile(), portdir));
    }
};

void
FileTest::operator()(const opts_type& opts) const 
{
    const std::string& portdir(herdstat::portage::GlobalConfig().portdir());

    assert(not opts.empty());
    const std::string& path(opts.front());
    assert(herdstat::util::is_dir(path));

    std::cout << "Testing util::Directory(" << path.substr(portdir.length()+1)
        << "):" << std::endl;
    const herdstat::util::Directory dir(path);
    ShowDirectory show;
    show(dir, portdir);

    std::cout << std::endl
        << "Testing util::Directory copy constructor (and re-running tests on it):"
        << std::endl;
    const herdstat::util::Directory copy(dir);
    assert(copy.size() == dir.size());
    show(copy, portdir);
}

#endif /* _HAVE_SRC_FILE_TEST_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
