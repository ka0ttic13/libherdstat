/*
 * libherdstat -- portage/ebuild.cc
 * $Id: ebuild.cc 204 2005-12-22 15:57:43Z ka0ttic $
 * Copyright (c) 2005 Aaron Walker <ka0ttic@gentoo.org>
 *
 * This file is part of libherdstat.
 *
 * libherdstat is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * libherdstat is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libherdstat; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 325, Boston, MA  02111-1257  USA
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <cassert>
#include <herdstat/util/string.hh>
#include <herdstat/portage/util.hh>
#include <herdstat/portage/ebuild.hh>

namespace herdstat {
namespace portage {
/*** static members *********************************************************/
//ebuild::eclass_map ebuild::_eclasses;
/****************************************************************************/
Ebuild::Ebuild() throw()
    : util::Vars(), _vmap()
{
}
/****************************************************************************/
Ebuild::Ebuild(const std::string &path) throw (FileException)
    : util::Vars(), _vmap()
{
    this->read(path);
}
/****************************************************************************/
Ebuild::~Ebuild() throw()
{
}
/****************************************************************************/
void
Ebuild::assign(const std::string& path)
{
    if (this->is_open())
        this->close();

    this->clear();
    this->read(path);
}
/****************************************************************************/
void
Ebuild::do_set_defaults()
{
    /* in case path() is an eclass */
    if (is_ebuild(this->path()))
    {
        _vmap.assign(this->path());
        /* insert this ebuild's variable components
         * (${P}, ${PN}, ${PV}, etc) into our map */
        this->insert(_vmap.begin(), _vmap.end());
    }
}
/****************************************************************************/
//void
//Ebuild::do_perform_action_on(const std::string& str)
//{
//    /* perform any inherits */
//    if (str.find("inherit") != std::string::npos)
//    {
//        std::string line(str);
//        this->strip_ws(line);

//        std::vector<std::string> parts(util::split(line));
//        if (parts[0] == "inherit")
//        {
//            std::vector<std::string>::iterator i;
//            for (i = parts.begin() + 1 ; i != parts.end() ; ++i)
//            {
//                const std::string eclass =
//                    util::sprintf(GlobalConfig().portdir()+"/eclass/%s.eclass",
//                        i->c_str());

//                /* only recurse if we havent parsed this eclass already */
//                eclass_map::iterator x = _eclasses.find(eclass);
//                if (x == _eclasses.end())
//                {
//                    if (util::file_exists(eclass))
//                    {
//                        std::cout << "parsing eclass '" << eclass << "'" << std::endl;
//                        x = _eclasses.insert(std::make_pair(eclass,
//                                         new ebuild())).first;
//                        x->second->insert(_vmap.begin(), _vmap.end());
//                        x->second->read(eclass);
//                    }
//                    else
//                    {
//                        std::cerr << this->path() << ": non-existent eclass "
//                            << eclass << std::endl;
//                        continue;
//                    }
//                }
//                else
//                    x->second->insert(_vmap.begin(), _vmap.end());

//                assert(x->second);
//                for (iterator e = x->second->begin() ;
//                        e != x->second->end() ; ++e)
//                {
//                    /* eclass overrides any variables set at this point */
//                    this->operator[](e->first) = e->second;
//                }
//            }
//        }
//    }
//}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
