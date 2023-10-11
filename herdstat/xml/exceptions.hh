/*
 * libherdstat -- herdstat/xml/exceptions.hh
 * $Id: exceptions.hh 148 2005-11-25 12:03:55Z ka0ttic $
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

#ifndef _HAVE_XML_EXCEPTIONS_HH
#define _HAVE_XML_EXCEPTIONS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/xml/exceptions.hh
 * @brief xml-related exception classes.
 */

#include <herdstat/exceptions.hh>

namespace herdstat {
namespace xml {

    /**
     * @class ParserException exceptions.hh herdstat/xml/exceptions.hh
     * @brief XML Parser exception.
     */

    class ParserException : public Exception
    {
        public:
            ParserException() throw() : _file(), _error() { }
            ParserException(const std::string &f, const std::string &e) throw()
                : _file(f), _error(e) { }
            virtual ~ParserException() throw() { }

            virtual const std::string& file() const throw() { return _file; }
            virtual const std::string& error() const throw() { return _error; }

        private:
            std::string _file, _error;
    };

} // namespace xml
} // namespace herdstat

#endif /* _HAVE_XML_EXCEPTIONS_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
