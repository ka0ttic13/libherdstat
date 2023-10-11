/*
 * libherdstat -- herdstat/io/binary_stream_iterator.hh
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

#ifndef _HAVE_IO_BINARY_STREAM_ITERATOR_HH
#define _HAVE_IO_BINARY_STREAM_ITERATOR_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/io/binary_stream_iterator.hh
 * @brief Defines the BinaryIStreamIterator and BinaryOStreamIterator classes.
 */

#include <string>
#include <iterator>
#include <herdstat/io/binary_stream.hh>

namespace herdstat {
namespace io {

    /**
     * @class BinaryIStreamIterator binary_stream_iterator.hh herdstat/io/binary_stream_iterator.hh
     * @brief Provides input iterator semantics for BinaryIStream.
     *
     * @section quirks Quirks
     *
     * You can only use BinaryIStreamIterator when you know for sure that there
     * is only one type (template argument T) from the stream position at
     * construction to EOF.  For example, if you write a vector of int's to the
     * stream, then a vector of strings, and then try to use a
     * BinaryIStreamIterator<int>, it'll read until EOF, treating the strings
     * as int's.  BinaryIStreamIterator is not suitable for these cases.
     */

    template <typename T>
    class BinaryIStreamIterator
        : public std::iterator<std::input_iterator_tag, T,
	        	       ptrdiff_t, const T*, const T& >
    {
        public:
            /// Construct end of input stream iterator.
	    inline BinaryIStreamIterator()
                : _stream(NULL), _ok(false), _value() { }
            /// Construct start of input stream iterator.
	    inline BinaryIStreamIterator(BinaryIStream& stream)
	        : _stream(&stream), _ok(false), _value() { this->_read(); }
            /// Copy constructor.
	    inline BinaryIStreamIterator(const BinaryIStreamIterator& that)
	        : _stream(that._stream), _ok(that._ok), _value(that._value) { }

            /// Get const reference to read value.
	    inline const T&
	    operator*() const
	    {
	        return _value;
	    }

            /// Get const pointer to read value.
	    inline const T*
	    operator->() const
	    {
	        return &(operator*());
	    }

            /// Read next value.
	    inline BinaryIStreamIterator&
	    operator++()
	    {
	        this->_read();
	        return *this;
	    }

            /// Read next value.
	    inline BinaryIStreamIterator
	    operator++(int)
	    {
	        BinaryIStreamIterator tmp(*this);
	        this->_read();
	        return tmp;
	    }

            ///@{
            /// Comparison operators.
	    inline bool
	    operator==(const BinaryIStreamIterator& that) const
	    {
                return ((_ok == that._ok) and
                        (not _ok || _stream == that._stream));
	    }

	    inline bool
	    operator!=(const BinaryIStreamIterator& that) const
	    {
	        return not (*this == that);
	    }
            ///@}

        private:
            /// Read next value.
	    inline void _read()
	    {
                _ok = (_stream and *_stream);
	        if (_ok)
	        {
		    *_stream >> _value;
		    _ok = *_stream;
	        }
	    }

	    BinaryIStream *_stream;
	    bool _ok;
	    T _value;
    };


    /**
     * @class BinaryOStreamIterator binary_stream_iterator.hh herdstat/io/binary_stream_iterator.hh
     * @brief Provides output iterator semantics for BinaryOStream.
     */

    template <typename T>
    class BinaryOStreamIterator
        : public std::iterator<std::output_iterator_tag, void, void, void, void>
    {
        public:
            /** Constructor.
             * @param stream reference to a BinaryOStream.
             */
	    inline BinaryOStreamIterator(BinaryOStream& stream)
	        : _stream(&stream) { }

            /// Copy constructor.
	    inline BinaryOStreamIterator(const BinaryOStreamIterator& that)
	        : _stream(that._stream) { }

            /// Write value to output stream.
	    inline BinaryOStreamIterator&
	    operator=(const T& v)
	    {
	        *_stream << v;
	        return *this;
	    }

            ///@{
            /// Required iterator operators.  Simply returns reference to this.
	    inline BinaryOStreamIterator& operator*() { return *this; }
	    inline BinaryOStreamIterator& operator++() { return *this; }
	    inline BinaryOStreamIterator& operator++(int) { return *this; }
            ///@}

        private:
	    BinaryOStream *_stream;
    };

} // namespace io
} // namespace herdstat

#endif /* _HAVE_IO_BINARY_STREAM_ITERATOR_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
