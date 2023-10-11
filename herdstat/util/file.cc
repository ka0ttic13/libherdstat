/*
 * libherdstat -- herdstat/util/file.cc
 * $Id: file.cc 205 2005-12-22 16:02:52Z ka0ttic $
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

#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>
#include <cstring>
#include <cassert>

#include <herdstat/exceptions.hh>
#include <herdstat/util/functional.hh>
#include <herdstat/util/file.hh>

namespace herdstat {
namespace util {
/*****************************************************************************/
Stat::Stat() throw()
    : _path(), _type(REGULAR), _exists(false), _opened(false)
{
}
/*****************************************************************************/
Stat::Stat(const std::string &p, bool opened) throw()
    : _path(p), _type(REGULAR), _exists(false), _opened(opened)
{
    this->operator()();
}
/*****************************************************************************/
void
Stat::assign(const std::string &p, bool opened) throw()
{
    this->_opened = opened;
    this->_path.assign(p);
    this->operator()();
}
/*****************************************************************************/
bool
Stat::operator()(void) throw()
{
    BacktraceContext s("herdstat::util::Stat::operator()("+_path+")");

    if (this->_opened)
    {
        /* TODO: figure out how to fstat an open stream. */
    }
    else
    {
        this->_exists = (::stat(this->_path.c_str(), this) == 0);
    }

    if (S_ISREG(this->st_mode))
        _type = REGULAR;
    else if (S_ISDIR(this->st_mode))
        _type = DIRECTORY;
    else if (S_ISCHR(this->st_mode))
        _type = CHARACTER;
    else if (S_ISBLK(this->st_mode))
        _type = BLOCK;
    else if (S_ISFIFO(this->st_mode))
        _type = FIFO;
    else if (S_ISLNK(this->st_mode))
        _type = LINK;
    else if (S_ISSOCK(this->st_mode))
        _type = SOCKET;

    return _exists;
}
/*****************************************************************************/
BaseFileObject::BaseFileObject() throw()
    : _stat(), _opened(false)
{
}
/*****************************************************************************/
BaseFileObject::BaseFileObject(const std::string &path) throw()
    : _stat(path), _opened(false)
{
}
/*****************************************************************************/
BaseFileObject::~BaseFileObject() throw()
{
}
/*****************************************************************************/
void
BaseFileObject::close() throw()
{
    BacktraceContext c("herdstat::util::BaseFileObject::close("+this->path()+")");

    if (not this->is_open())
        return;
    this->do_close();
    this->set_open(false);
}

void
BaseFileObject::read()
{
    BacktraceContext c("herdstat::util::BaseFileObject::read()");
    
    if (not this->is_open())
        throw Exception("BaseFileObject::read() called before BaseFileObject::open().");

    this->do_read();    
}

void
BaseFileObject::read(const std::string& path)
{
    BacktraceContext c("herdstat::util::BaseFileObject::read("+path+")");

    if (this->is_open())
        this->close();

    _stat.assign(path);
    this->set_path(path);
    this->open();

    this->do_read();
}
/*****************************************************************************/
BaseFile::BaseFile() throw()
    : BaseFileObject(), _stream(NULL), _mode(DEFAULT_MODE)
{
}
/*****************************************************************************/
BaseFile::BaseFile(const BaseFile& that) throw (FileException)
    : BaseFileObject(), _stream(NULL), _mode(DEFAULT_MODE)
{
    *this = that;
}
/*****************************************************************************/
BaseFile::BaseFile(const std::string &path, std::ios_base::openmode mode)
    throw (FileException)
    : BaseFileObject(path), _stream(NULL), _mode(mode)
{
    this->open(this->path().c_str(), mode);
}
/*****************************************************************************/
BaseFile&
BaseFile::operator=(const BaseFile& that) throw (FileException)
{
    BacktraceContext c("herdstat::util::BaseFile::operator=()");

    BaseFileObject::operator=(that);

    set_mode(that.mode());

    if (that._stream and that._stream->is_open())
        this->open(that.path().c_str(), mode());

    return *this;
}
/*****************************************************************************/
BaseFile::~BaseFile() throw()
{
    if (this->is_open())
        this->close();
}
/*****************************************************************************/
void
BaseFile::open(const char *n, std::ios_base::openmode mode)
    throw (FileException)
{
    if (this->path() != n)
        this->stat().assign(n);

    BacktraceContext c("herdstat::util::BaseFile::open("+this->path()+")");

    set_mode(mode);

    if (_stream)
    {
        if (_stream->is_open())
        {
            this->set_open(true);
            return;
        }
        
        _stream->open(n, mode);
    }
    else
        _stream = new std::fstream(n, mode);

    if (not _stream->is_open())
        throw FileException(n);

    this->set_open(true);
}
/*****************************************************************************/
void
BaseFile::open() throw (FileException)
{
    this->open(this->path().c_str(), DEFAULT_MODE);
}
/*****************************************************************************/
void
BaseFile::open(std::ios_base::openmode mode) throw (FileException)
{
    set_mode(mode);
    this->open(this->path().c_str(), mode);
}
/*****************************************************************************/
void
BaseFile::do_close() throw()
{
    if (_stream)
    {
        delete _stream;
        _stream = NULL;
    }
}
/*****************************************************************************/
File::File(const std::string &path, std::ios_base::openmode mode)
    throw (FileException)
    : BaseFile(path, mode)
{
    this->read();
}
/*****************************************************************************/
File::~File() throw()
{
}
/*****************************************************************************/
void
File::do_read()
{
    BacktraceContext c("herdstat::util::File::do_read("+this->path()+")");

    std::string line;
    while (std::getline(this->stream(), line))
        this->push_back(line);

    /*
     * this->insert(this->end(),
     *      std::istream_iterator<std::string>(this->stream()),
     *      std::istream_iterator<std::string>());
     */
}
/*****************************************************************************/
bool
File::operator== (const File &that) const
{
    BacktraceContext c("herdstat::util::File::operator==()");

    if (this->bufsize() != that.bufsize())
        return false;

    return std::equal(this->begin(), this->end(), that.begin());
}
/*****************************************************************************/
void
File::dump(std::ostream &os) const
{
    BacktraceContext c("herdstat::util::File::dump("+this->path()+")");
    std::copy(this->begin(), this->end(),
        std::ostream_iterator<value_type>(os, "\n"));
}
/*****************************************************************************/
void
File::write()
{
    BacktraceContext c("herdstat::util::File::write("+this->path()+")");
    this->dump(this->stream());
    this->clear();
}
/*****************************************************************************/
Directory::Directory(bool recurse, util::ProgressMeter *meter) throw()
    : Progressable(meter), BaseFileObject(), util::VectorBase<std::string>(),
      _dirp(NULL), _recurse(recurse)
{
}
/*****************************************************************************/
Directory::Directory(const std::string &path, bool recurse,
                     util::ProgressMeter *meter)
    throw (FileException)
    : Progressable(meter), BaseFileObject(path), util::VectorBase<std::string>(),
      _dirp(NULL), _recurse(recurse)
{
    this->open();
    this->read();
}
/*****************************************************************************/
Directory::Directory(const Directory& that)
    : Progressable(that.meter()), BaseFileObject(),
      util::VectorBase<std::string>(),
      _dirp(NULL), _recurse(false)
{
    *this = that;
}
/*****************************************************************************/
Directory::~Directory() throw()
{
    if (this->is_open())
        this->close();
}
/*****************************************************************************/
Directory&
Directory::operator= (const Directory& that)
{
    BaseFileObject::operator=(that);
    const_cast<bool&>(_recurse) = that._recurse;
    container() = that.container();

    if (that.is_open())
        this->open();

    return *this;
}
/*****************************************************************************/
void
Directory::do_close() throw()
{
    BacktraceContext c("herdstat::util::Directory::do_close("+this->path()+")");
    closedir(_dirp);
    _dirp = NULL;
}
/*****************************************************************************/
void
Directory::open() throw (FileException)
{
    BacktraceContext c("herdstat::util::Directory::open("+this->path()+")");

    if (this->is_open())
        return;

    assert(not this->path().empty());

    _dirp = opendir(this->path().c_str());
    if (not _dirp)
        throw FileException(this->path());

    this->set_open(true);
}
/*****************************************************************************/
void
Directory::do_read()
{
    BacktraceContext c("herdstat::util::Directory::do_read("+this->path()+")");

    struct dirent *d = NULL;
    while ((d = readdir(_dirp)))
    {
        if (meter())
            ++*meter();

        /* skip . and .. */
        if ((std::strcmp(d->d_name, ".") == 0) or
            (std::strcmp(d->d_name, "..") == 0))
            continue;

        this->push_back(this->path() + "/" + d->d_name);

        /* recurse into sub-directories */
        if (_recurse and util::is_dir(this->back()))
        {
            Directory dir(this->back(), _recurse, this->meter());
            this->insert(this->end(), dir.begin(), dir.end());
        }
    }
}
/*****************************************************************************/
Directory::iterator
Directory::find(const std::string &base) throw()
{
    const std::string path(this->path()+"/"+base);
    return std::find(this->begin(), this->end(), path);
}
/*****************************************************************************/
Directory::const_iterator
Directory::find(const std::string &base) const throw()
{
    const std::string path(this->path()+"/"+base);
    return std::find(this->begin(), this->end(), path);
}
/*****************************************************************************/
Directory::iterator
Directory::find(const Regex& regex) throw()
{
    return std::find_if(this->begin(), this->end(),
        std::bind1st(regexMatch(), regex));
}

/*****************************************************************************/
Directory::const_iterator
Directory::find(const Regex& regex) const throw()
{
    return std::find_if(this->begin(), this->end(),
        std::bind1st(regexMatch(), regex));
}
/*****************************************************************************
 * general purpose file-related functions                                    *
 *****************************************************************************/
void
copy_file(const std::string& from, const std::string& to) throw (FileException)
{
    BacktraceContext c("herdstat::util::copy_file("+from+", "+to+")");

    /* remove to if it exists */
    if (is_file(to) and (unlink(to.c_str()) != 0))
	throw FileException(to);

    std::ifstream ffrom(from.c_str());
    if (not ffrom)
	throw FileException(from);

    std::ofstream fto(to.c_str());
    if (not fto)
	throw FileException(to);

    /* read from ffrom and write to fto */

//    std::copy(std::istream_iterator<std::string>(ffrom),
//              std::istream_iterator<std::string>(),
//              std::ostream_iterator<std::string>(fto, "\n"));

    std::string line;
    while (std::getline(ffrom, line))
        fto << line << std::endl;
}
/*****************************************************************************/
void
move_file(const std::string& from, const std::string& to) throw (FileException)
{
    BacktraceContext c("herdstat::util::move_file("+from+", "+to+")");
    copy_file(from, to);
    if (unlink(from.c_str()) != 0)
	throw FileException(from);
}
/*****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
