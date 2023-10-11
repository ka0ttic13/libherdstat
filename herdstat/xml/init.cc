/*
 * libherdstat -- herdstat/xml/init.cc
 * $Id: init.cc 190 2005-12-11 14:15:23Z ka0ttic $
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

#include <herdstat/xml/init.hh>

namespace herdstat {
namespace xml {
/****************************************************************************/
Init::Init(bool validate)
    : _init()
{
    _init.remove_whitespace(true);
    _init.substitute_entities(true);
    _init.load_external_subsets(true);
    _init.validate_xml(validate);
}
/****************************************************************************/
} // namespace xml
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
