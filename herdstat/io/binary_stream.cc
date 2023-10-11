/*
 * libherdstat -- herdstat/io/binary_stream.cc
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

#include <herdstat/io/binary_stream.hh>

namespace herdstat {
namespace io {
/****************************************************************************/
BinaryStream::BinaryStream() throw()
    : _path(), _stream(NULL), _open(false)
{
}
/****************************************************************************/
BinaryStream::BinaryStream(const std::string& path) throw ()
    : _path(path), _stream(NULL), _open(false)
{
}
/****************************************************************************/
BinaryStream::~BinaryStream() throw()
{
    if (_stream)
        this->close();
}
/****************************************************************************/
void
BinaryStream::open() throw ()
{
    if (_open)
	return;

    _stream = std::fopen(_path.c_str(), this->mode());

    _open = true;
}
/****************************************************************************/
void
BinaryStream::open(const std::string& path) throw ()
{
    if (_open)
	return;

    _path.assign(path);

    this->open();
}
/****************************************************************************/
void
BinaryStream::close() throw()
{
    if (not _open)
	return;

    assert(_stream != NULL);
    std::fclose(_stream);
    _stream = NULL;

    _open = false;
}
/****************************************************************************/
BinaryIStream::BinaryIStream() throw()
    : BinaryStream()
{
}
/****************************************************************************/
BinaryIStream::BinaryIStream(const std::string& path) throw ()
    : BinaryStream(path)
{
    this->open();
}
/****************************************************************************/
BinaryIStream::~BinaryIStream() throw()
{
}
/****************************************************************************/
const char * const
BinaryIStream::mode() const
{
    return "rb";
}
/****************************************************************************/
BinaryOStream::BinaryOStream() throw()
    : BinaryStream()
{
}
/****************************************************************************/
BinaryOStream::BinaryOStream(const std::string& path) throw ()
    : BinaryStream(path)
{
    this->open();
}
/****************************************************************************/
BinaryOStream::~BinaryOStream() throw()
{
}
/****************************************************************************/
const char * const
BinaryOStream::mode() const
{
    return "wb";
}
/****************************************************************************/
} // namespace io
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
