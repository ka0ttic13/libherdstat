/*
 * libherdstat -- herdstat/portage/metadata.cc
 * $Id: metadata.cc 141 2005-11-21 14:19:35Z ka0ttic $
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

#include <herdstat/portage/metadata.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
Metadata::Metadata()
    : _pkg(), _longdesc(), _cat(false), _herds(NULL), _devs(NULL)
{
}
/****************************************************************************/
Metadata::Metadata(const std::string &pkg)
    : _pkg(pkg), _longdesc(), _cat(false), _herds(NULL), _devs(NULL)
{
}
/****************************************************************************/
Metadata::Metadata(const Metadata& that)
    : _pkg(), _longdesc(), _cat(false), _herds(NULL), _devs(NULL)
{
    *this = that;
}
/****************************************************************************/
Metadata&
Metadata::operator=(const Metadata& that)
{
    _pkg = that._pkg;
    _longdesc = that._longdesc;
    _cat = that._cat;

    if (that._herds)
        _herds = new Herds(*that._herds);
    if (that._devs)
        _devs = new Developers(*that._devs);

    return *this;
}
/****************************************************************************/
Metadata::~Metadata()
{
    if (_herds) delete _herds;
    if (_devs) delete _devs;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
