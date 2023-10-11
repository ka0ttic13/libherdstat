/*
 * libherdstat -- herdstat/fetcher/exceptions.hh
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

#ifndef _HAVE_FETCHER_EXCEPTIONS_HH
#define _HAVE_FETCHER_EXCEPTIONS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/fetcher/exceptions.hh
 * @brief Defines fetcher-related exception classes.
 */

#include <herdstat/exceptions.hh>

namespace herdstat {

    /**
     * @class FetchException
     * @brief Exception for fetching errors.
     */

    class FetchException : public Exception
    {
        public:
            /// Default constructor.
            FetchException() throw();
            /// Constructor.
            FetchException(const std::string& msg) throw();
            /// Destructor.
            virtual ~FetchException() throw();
    };

    /**
     * @class UnimplementedFetchMethod
     * @brief Exception for unimplemented fetch methods.
     */

    class UnimplementedFetchMethod : public Exception
    {
        public:
            /// Constructor.
            UnimplementedFetchMethod(const std::string& imp) throw();
            /// Destructor.
            virtual ~UnimplementedFetchMethod() throw();
            /// Description.
            virtual const char *what() const throw();
    };

} // namespace herdstat

#endif /* _HAVE_FETCHER_EXCEPTIONS_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
