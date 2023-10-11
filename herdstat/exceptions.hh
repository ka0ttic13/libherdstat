/*
 * libherdstat -- herdstat/exceptions.hh
 * $Id: exceptions.hh 190 2005-12-11 14:15:23Z ka0ttic $
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

#ifndef _HAVE_HERDSTAT_EXCEPTIONS_HH
#define _HAVE_HERDSTAT_EXCEPTIONS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/exceptions.hh
 * @brief Defines exception classes used in libherdstat.
 */

#include <exception>
#include <stdexcept>
#include <sys/types.h>
#include <regex.h>
#include <libebt/libebt.hh>

namespace herdstat {

    /// %Exception group for use by libebt.
    class ExceptionTag { };

    /**
     * @typedef BacktraceContext
     * @brief convenience typedef for backtrace contexts provided by libebt.
     */

    typedef libebt::BacktraceContext<ExceptionTag> BacktraceContext;

    /**
     * @class BaseException exceptions.hh herdstat/exceptions.hh
     * @brief Base exception class.  All exception classes defined by libherdstat
     * derive from this class.
     */

    class BaseException : public std::exception,
                          public libebt::Backtraceable<ExceptionTag>
    {
        protected:
            /// Default constructor.
            BaseException() throw();
            /// Destructor.
            virtual ~BaseException() throw();
    };

    /**
     * @class Exception exceptions.hh herdstat/exceptions.hh
     * @brief Generic exception class.
     */

    class Exception : public BaseException
    {
        public:
            /// Default constructor.
            Exception() throw();

            /// Copy constructor.
            Exception(const Exception& that) throw();

            /** Constructor.
             * @param fmt printf-like format string.
             * @param v va_list.
             */
            Exception(const char *fmt, va_list v) throw();

            //@{
            /** Constructor.
             * @param fmt printf-like format string.
             * @param ... variable args.
             */
            Exception(const char *fmt, ...) throw();
            Exception(const std::string& fmt, ...) throw();
            //@}

            /// Copy assignment operator.
            Exception& operator= (const Exception& that) throw();

            /// Destructor.
            virtual ~Exception() throw();

            /// Get error message.
            virtual const char *what() const throw();

        protected:
            inline const char *message() const throw() { return _buf; }

        private:
            char *_buf;
            va_list _v;
    };

    /**
     * @class ErrnoException exceptions.hh herdstat/exceptions.hh
     * @brief Exception class for errors where errno is set.
     */

    class ErrnoException : public Exception
    {
        public:
            /// Default constructor.
            ErrnoException() throw();

            //@{
            /** Constructor.
             * @param msg Error message prefix.
             */
            ErrnoException(const char *msg) throw();
            ErrnoException(const std::string& msg) throw();
            //@}

            /// Destructor.
            virtual ~ErrnoException() throw();

            /// Get error message prefix + strerror(errno).
            virtual const char *what() const throw();

            /// Get error code (errno) for this error.
            inline int code() const throw() { return _code; }

        private:
            int _code;
    };
    
    /**
     * @class FileException exceptions.hh herdstat/exceptions.hh
     * @brief Exception for file-related errors.
     */

    class FileException : public ErrnoException
    {
        public:
            /// Default constructor.
            FileException() throw();

            //@{
            /** Constructor.
             * @param msg Error message prefix.
             */
            FileException(const char *msg) throw();
            FileException(const std::string& msg) throw();
            //@}
            
            /// Destructor.
            virtual ~FileException() throw();
    };

    /**
     * @class BadCast exceptions.hh herdstat/exceptions.hh
     * @brief Exception for bad type casts.
     */

    class BadCast : public Exception
    {
        public:
            /// Default constructor.
            BadCast() throw();

            //@{
            /** Constructor.
             * @param msg Error message.
             */
            BadCast(const char *msg) throw();
            BadCast(const std::string& msg) throw();
            //@}

            /// Destructor.
            virtual ~BadCast() throw();
    };

    /**
     * @class BadRegex exceptions.hh herdstat/exceptions.hh
     * @brief Exception for regular expression errors.
     */

    class BadRegex : public Exception
    {
        public:
            /// Default constructor.
            BadRegex() throw();

            /** Constructor.
             * @param e error code.
             * @param re regex_t associated with this error.
             */
            BadRegex(int e, const regex_t *re) throw();

            /** Constructor.
             * @param s Error message.
             */
            BadRegex(const std::string& s) throw();

            /// Destructor.
            virtual ~BadRegex() throw();

            /// Get error message.
            virtual const char *what() const throw();

        private:
            int _err;
            const regex_t *_re;
    };

    /**
     * @class BadDate exceptions.hh herdstat/exceptions.hh
     * @brief Exception for invalid dates.
     */

    class BadDate : public Exception
    {
        public:
            /// Default constructor.
            BadDate() throw();

            //@{
            /** Constructor.
             * @param msg Error message.
             */
            BadDate(const char *msg) throw();
            BadDate(const std::string& msg) throw();
            //@}

            /// Destructor.
            virtual ~BadDate() throw();
    };

    /**
     * @class MalformedEmail exceptions.hh herdstat/exceptions.hh
     * @brief Exception for malformed email addresses.
     */

    class MalformedEmail : public Exception
    {
        public:
            /// Default constructor.
            MalformedEmail() throw();

            //@{
            /** Constructor.
             * @param msg Error message.
             */
            MalformedEmail(const char *msg) throw();
            MalformedEmail(const std::string& msg) throw();
            //@}

            /// Destructor.
            virtual ~MalformedEmail() throw();
    };

} // namespace herdstat

#endif /* _HAVE_HERDSTAT_EXCEPTIONS_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
