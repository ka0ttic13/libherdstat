/*
 * libherdstat -- herdstat/portage/archs.cc
 * $Id: archs.cc 142 2005-11-23 02:14:51Z ka0ttic $
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

#include <iterator>
#include <herdstat/portage/archs.hh>

#define ARCH_LIST   "/profiles/arch.list"

namespace herdstat {
namespace portage {
/****************************************************************************/
Archs::Archs(const std::string& portdir) throw (FileException)
    : util::BaseFile(portdir+ARCH_LIST)
{
    this->read();
}
/****************************************************************************/
Archs::~Archs() throw()
{
}
/****************************************************************************/
void
Archs::do_read()
{
    this->insert(std::istream_iterator<std::string>(this->stream()),
                 std::istream_iterator<std::string>());

    /* so keywords like '-*' are recognized. */
    this->insert("*");
}
/****************************************************************************/
} // namespace portdir
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
