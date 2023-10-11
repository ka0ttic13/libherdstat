/*
 * libherdstat -- herdstat/portage/package.cc
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

#include <herdstat/exceptions.hh>
#include <herdstat/portage/package_directory.hh>
#include <herdstat/portage/package.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
Package::Package()
    : _name(), _cat(), _dir(GlobalConfig().portdir()), _full(), _path(),
      _kwmap(NULL), _pkgdir(NULL)
{
}
/****************************************************************************/
Package::Package(const Package& that)
    : _name(), _cat(), _dir(GlobalConfig().portdir()), _full(), _path(),
      _kwmap(NULL), _pkgdir(NULL)
{
    *this = that;
}
/****************************************************************************/
Package::Package(const std::string& name, const std::string& portdir)
    : _name(), _cat(), _dir(portdir), _full(),  _path(), _kwmap(NULL),
      _pkgdir(NULL)
{
    set_name(name);
}
/****************************************************************************/
Package::~Package()
{
    if (_kwmap)  delete _kwmap;
    if (_pkgdir) delete _pkgdir;
}
/****************************************************************************/
Package&
Package::operator=(const Package& that)
{
    _name.assign(that._name);
    _cat.assign(that._cat);
    _dir.assign(that._dir);
    _full.assign(that._full);
    _path.assign(that._path);

    if (that._kwmap)
        _kwmap = new KeywordsMap(*that._kwmap);
    if (that._pkgdir)
        _pkgdir = new PackageDirectory(*that._pkgdir);

    return *this;
}
/****************************************************************************/
void
Package::set_name(const std::string& name)
{
    if (name.find('/') != std::string::npos)
        set_full(name);
    else
    {
        _name.assign(name);
        _full.assign(_name);
        set_category(_name);
        set_path(_dir+"/"+_name);
    }
}
/****************************************************************************/
void
Package::set_full(const std::string& full)
{
    std::string::size_type pos = full.find('/');
    if (pos == std::string::npos)
        throw Exception("Invalid full category/package specification '"+full+"'.");

    set_category(full.substr(0, pos));
    set_name(full.substr(++pos));
    _full.assign(full);
    set_path(_dir+"/"+_full);
}
/****************************************************************************/
const PackageDirectory&
Package::pkgdir() const
{
    if (not _pkgdir)
        _pkgdir = new PackageDirectory(_path);
    return *_pkgdir;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
