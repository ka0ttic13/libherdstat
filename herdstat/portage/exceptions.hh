/*
 * libherdstat -- herdstat/portage/exceptions.hh
 * $Id: exceptions.hh 208 2005-12-22 16:05:43Z ka0ttic $
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

#ifndef HAVE_PORTAGE_EXCEPTIONS_HH
#define HAVE_PORTAGE_EXCEPTIONS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/exceptions.hh
 * @brief Defines portage-related exception classes.
 */

#include <iostream>
#include <vector>

#include <herdstat/exceptions.hh>
#include <herdstat/util/regex.hh>

namespace herdstat {
namespace portage {

    /**
     * @class BadVersionSuffix exceptions.hh herdstat/portage/exceptions.hh
     * @brief Bad version suffix exception.
     */

    class BadVersionSuffix : public Exception
    {
        public:
            /// Constructor
            BadVersionSuffix(const std::string &msg) throw();
            /// Destructor
            virtual ~BadVersionSuffix() throw();
            /// Get message
            virtual const char *what() const throw();
    };

    /**
     * @class AmbiguousPkg exceptions.hh herdstat/portage/exceptions.hh
     * @brief Ambiguous package name exception.
     */

    class AmbiguousPkg : public Exception
    {
        public:
            /** Constructor.
             * @param pkgs const reference to a vector of package names.
             */
            AmbiguousPkg(const std::vector<std::string>& pkgs) throw();

            /** Constructor.
             * @param first beginning input iterator
             * @param last ending input iterator
             */
            template <typename InputIterator>
            AmbiguousPkg(InputIterator first, InputIterator last) throw()
                : _name(), _packages(first, last) { _set_name(*first); }

            /// Destructor
            virtual ~AmbiguousPkg() throw();

            /// Get ambiguous package name (just the ambigious part).
            inline const std::string& name() const throw() { return _name; }
            /// Get const reference to vector of ambigious package names
            inline const std::vector<std::string>& packages() const throw()
            { return _packages; }

        private:
            void _set_name(const std::string& name) throw();

            /// Ambiguous name.
            std::string _name;
            /// Vector of possible matches.
            const std::vector<std::string> _packages;
    };

    /**
     * @class NonExistentPkg exceptions.hh herdstat/portage/exceptions.hh
     * @brief Non-existent package exception.
     */

    class NonExistentPkg : public Exception
    {
        public:
            /** Constructor.
             * @param msg package name.
             */
            NonExistentPkg(const std::string& msg) throw();

            /** Constructor.
             * @param re package name regular expression.
             */
            NonExistentPkg(const util::Regex& re) throw();

            /// Destructor.
            virtual ~NonExistentPkg() throw();

            /// Get message.
            virtual const char *what() const throw();
        
        private:
            const bool _regex;
    };

    /**
     * @class QAException exceptions.hh herdstat/portage/exceptions.hh
     * @brief Quality Assurance exception.
     */

    class QAException : public Exception
    {
        public:
            /** Constructor.
             * @param msg QA error message.
             */
            QAException(const std::string& msg) throw();

            /// Destructor.
            virtual ~QAException() throw();
    };

    /**
     * @class QAErrnoException exceptions.hh herdstat/portage/exceptions.hh
     * @brief Quality Assurance (with strerror()) exception.
     */

    class QAErrnoException : public ErrnoException
    {
        public:
            /** Constructor.
             * @param msg QA error message.
             */
            QAErrnoException(const std::string& msg) throw();

            /// Destructor.
            virtual ~QAErrnoException() throw();

            /// Get message.
            virtual const char *what() const throw();
    };

    /**
     * @class InvalidKeywordMask exceptions.hh herdstat/portage/exceptions.hh
     * @brief Exception for invalid mask characters ('~' in ~arch).
     */

    class InvalidKeywordMask : public Exception
    {
        public:
            /** Constructor.
             * @param c keyword mask character
             */
            InvalidKeywordMask(const char c) throw();

            /// Destructor.
            virtual ~InvalidKeywordMask() throw();

            /// Get message.
            virtual const char *what() const throw();

        private:
            const char _mask;
    };

    /**
     * @class InvalidArch exceptions.hh herdstat/portage/exceptions.hh
     * @brief Exception for invalid architectures.
     */

    class InvalidArch : public Exception
    {
        public:
            /** Constructor.
             * @param arch architecture
             */
            InvalidArch(const std::string& arch) throw();

            /// Destructor.
            virtual ~InvalidArch() throw();

            /// Get message.
            virtual const char *what() const throw();
    };

    class InvalidAtom : public Exception
    {
        public:
            /** Constructor.
             * @param atom atom string.
             */
            InvalidAtom(const std::string& atom) throw();

            /// Destructor.
            virtual ~InvalidAtom() throw();
    };

} // namespace portage
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 fdm=marker et : */
