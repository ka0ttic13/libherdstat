/*
 * libherdstat -- herdstat/io/binary_stream.hh
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

#ifndef _HAVE_IO_BINARY_STREAM_HH
#define _HAVE_IO_BINARY_STREAM_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/io/binary_stream.hh
 * @brief Defines the BinaryStream family of classes.
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

namespace herdstat {
namespace io {

    /**
     * @class BinaryStream binary_stream.hh herdstat/io/binary_stream.hh
     * @brief C++-like stream interface for C's fread/fwrite.
     */

    class BinaryStream
    {
	public:
            /// Destructor.
	    virtual ~BinaryStream() throw();

            /** Open stream.
             * @param path path of file to open.
             */
	    void open(const std::string& path) throw ();

            /// Close stream.
	    void close() throw();

            /// Is stream open?
	    inline bool is_open() const { return _open; }
            /// Get path.
	    inline const std::string& path() const { return _path; }

            ///@{
            /** Check if stream's status is ok.  Allows the use of BinaryStream
             * classes in boolean expressions.
             */
            inline operator void*() const
            { return (operator!() ? NULL : const_cast<BinaryStream*>(this)); }

	    inline bool operator!() const
	    {
		return ((_stream == NULL) or (std::ferror(_stream)) or
		        (std::feof(_stream)));
	    }
            ///@}

	protected:
	    template <typename T> friend class BinaryIStreamIterator;

            /// Default constructor.
	    BinaryStream() throw();

            /** Constructor.
             * @param path Path of file.
             */
	    BinaryStream(const std::string& path) throw ();

            /// Open stream (path already set).
            void open() throw();

            /// For derivatives to define their open mode.
	    virtual const char * const mode() const = 0;

            /// Set path.
	    inline void set_path(const std::string& path) { _path = path; }

            /// Get underlying FILE pointer.
	    inline FILE * const stream() const { return _stream; }

	private:
	    std::string _path;
	    FILE *_stream;
	    bool _open;
    };

    /**
     * @class BinaryIStream binary_stream.hh herdstat/io/binary_stream.hh
     * @brief BinaryStream opened for reading.
     */

    class BinaryIStream : public BinaryStream
    {
	public:
            /// Default constructor.
	    BinaryIStream() throw();

            /** Constructor.  Opens stream.
             * @param path Path of file to open.
             */
	    BinaryIStream(const std::string& path) throw ();

            /// Destructor.
	    virtual ~BinaryIStream() throw();

            /** Read value from stream.
             * @param v variable to save read value.
             */
            template <typename T>
            inline void read(T& v);

            /** Read value from stream.
             * @param v variable to save read value.
             * @returns reference to this.
             */
	    template <typename T>
	    inline BinaryIStream& operator>>(T& v);

	protected:
            /// Open mode.
	    virtual const char * const mode() const;
    };

    template <typename T>
    inline void
    BinaryIStream::read(T& v)
    {
        std::fread(static_cast<void *>(&v), sizeof(T), 1, this->stream());
    }

    /// Partial specialization for std::string.
    template <>
    inline void
    BinaryIStream::read<std::string>(std::string& str)
    {
	std::string::size_type len;
        this->read(len);

        if (not *this)
            return;

        char *buf = new char[len+1];
        buf[len] = 0;
        std::fread(static_cast<void*>(buf), sizeof(char), len, this->stream());
	str.assign(buf);
        delete[] buf;
    }

    template <typename T>
    inline BinaryIStream&
    BinaryIStream::operator>>(T& v)
    {
        this->read(v);
	return *this;
    }

    /**
     * @class BinaryOStream binary_stream.hh herdstat/io/binary_stream.hh
     * @brief BinaryStream opened for writing.
     */

    class BinaryOStream : public BinaryStream
    {
	public:
            /// Default constructor.
	    BinaryOStream() throw();

            /** Constructor.  Opens stream.
             * @param path Path of file to open.
             */
	    BinaryOStream(const std::string& path) throw ();

            /// Destructor.
	    virtual ~BinaryOStream() throw();

            /** Write value to stream.
             * @param v Value to write to stream.
             */
            template <typename T>
            inline void write(const T& v);

            /// char * overload which calls the std::string specialization.
            inline void write(const char * const str);

            /** Write value to stream.
             * @param v Value to write to stream.
             * @returns reference to this.
             */
	    template <typename T>
	    inline BinaryOStream& operator<<(const T& v);

	protected:
            /// Open mode.
	    virtual const char * const mode() const;
    };

    template <typename T>
    inline void
    BinaryOStream::write(const T& v)
    {
        std::fwrite(static_cast<const void *>(&v),
                sizeof(T), 1, this->stream());
    }

    /// Partial specialization for std::string.
    template <>
    inline void
    BinaryOStream::write<std::string>(const std::string& str)
    {
	const std::string::size_type len(str.length());
        this->write(len);

        if (not *this)
            return;

        std::fwrite(static_cast<const void *>(str.c_str()),
                sizeof(char), len, this->stream());
    }

    inline void
    BinaryOStream::write(const char * const str)
    {
        this->write(std::string(str));
    }

    template <typename T>
    inline BinaryOStream&
    BinaryOStream::operator<<(const T& v)
    {
        this->write(v);
	return *this;
    }

} // namespace io
} // namespace herdstat

#endif /* _HAVE_IO_BINARY_STREAM_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
