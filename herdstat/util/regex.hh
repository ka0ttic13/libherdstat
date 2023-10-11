/*
 * libherdstat -- herdstat/util/regex.hh
 * $Id: regex.hh 194 2005-12-12 12:57:29Z ka0ttic $
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

#ifndef HAVE_REGEX_HH
#define HAVE_REGEX_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/regex.hh
 * @brief Defines the Regex class.
 */

#include <string>
#include <functional>
#include <cstddef>
#include <sys/types.h>
#include <regex.h>

#include <herdstat/exceptions.hh>
#include <herdstat/util/container_base.hh>

namespace herdstat {
namespace util {

    /**
     * @class Regex regex.hh herdstat/util/regex.hh
     * @brief POSIX regular expressions interface.
     *
     * @section usage Usage
     *
     * The Regex class is extremely simple to use.  Simply construct the Regex
     * object with a regular expression (or use the assign() member).  To
     * compare the regular expression against a string to see if it matches,
     * just use the built-in operator==().  Likewise you can use operator!=()
     * to see if it doesn't match.  Keep in mind that when specifying the
     * regular expression string, you may need to do some additional escaping.
     * For example, if you want to use a literal '.' in a regular expression,
     * you'll need to use '\\.' rather than the usual '\.'.
     *
     * @section example Example
     *
     * Below is a simple example of using the Regex class:
     *
@code
std::string str;
...
const herdstat::util::Regex regex("^s.*l$", herdstat::util::Regex::icase);
if (str == regex)
{
    ...
}
@endcode
     *
     * Below is another example of using the Regex class to construct an
     * extended regular expression:
     *
@code
std::string str;
...
const herdstat::util::Regex regex("^\\.(dep|lib)s",
    herdstat::util::Regex::icase|herdstat::util::Regex::extended);
if (str == regex)
{
    ...
}
@endcode
     *
     * More often than not, you will have a container of strings in which you
     * want to pull out all strings that match a certain regular expression.  In
     * these cases you'll want to use the herdstat::util::regexMatch function
     * object in addition to an algorithm.
     * @see util::regexMatch for an example on it's usage.
     */

    class Regex
    {
        public:
            /// compilation cflags
            enum Cflags { };
            /// exec eflags
            enum Eflags { };

            /// REG_EXTENDED
            static const Cflags extended;
            /// REG_ICASE
            static const Cflags icase;
            /// REG_NOSUB
            static const Cflags nosub;
            /// REG_NEWLINE
            static const Cflags newline;

            /// REG_NOTBOL
            static const Eflags notbol;
            /// REG_NOTEOL
            static const Eflags noteol;

            /// Default constructor.
            Regex() throw();

            /** Copy constructor.
             * @exception BadRegex
             */
            Regex(const Regex& that) throw (BadRegex);

            /** Constructor.
             * @param c CFLAGS.
             * @param e EFLAGS.
             */
            Regex(int c, int e = 0) throw();

            /** Constructor.
             * @param r regular expression string.
             * @param c CFLAGS.
             * @param e EFLAGS.
             * @exception BadRegex
             */
            Regex(const std::string& r, int c = 0, int e = 0) throw (BadRegex);

            /// Destructor.
            ~Regex() throw();

            /** Assign a new regular expression.
             * @param r regular expression string.
             * @exception BadRegex
             */
            void assign(const std::string& r) throw (BadRegex);

            /** Assign a new regular expression.
             * @param r regular expression string.
             * @param c CFLAGS.
             * @param e EFLAGS.
             * @exception BadRegex
             */
            void assign(const std::string& r , int c, int e = 0) throw (BadRegex);

            /** Assign a new regular expression (no CFLAGS/EFLAGS).
             * @param s regular expression string.
             * @exception BadRegex
             * @returns a Regex object.
             */
            inline Regex& operator= (const std::string& s) throw (BadRegex);

            /** Copy assignment operator.
             * @exception BadRegex
             */
            Regex& operator= (const Regex& that) throw (BadRegex);

            /** Determine if this regex matches the specified std::string.
             * @param cmp Comparison string.
             * @returns   A boolean value.
             */
            inline bool operator== (const std::string& cmp) const throw();

            /** Determine if this regex does not match the specified std::string.
             * @param cmp Comparison string.
             * @returns   A boolean value.
             */
            inline bool operator!= (const std::string& cmp) const throw();

            /** Determine if this regex is equal to that regex.  Only compares
             * uncompiled regex strings.
             * @param that const reference to Regex object.
             * @returns A boolean value.
             */
            inline bool operator== (const Regex& that) const throw();

            /** Determine if this regex is not equal to that regex.  Only
             * compares uncompiled regex strings.
             * @param that const reference to Regex object.
             * @returns A boolean value.
             */
            inline bool operator!= (const Regex& that) const throw();

            /** Determine if this regex is less than that regex.  Only
             * compares uncompiled regex strings.
             * @param that const reference to Regex object.
             * @returns A boolean value.
             */
            inline bool operator< (const Regex& that) const throw();

            /** Determine if this regex is greater than that regex.  Only
             * compares uncompiled regex strings.
             * @param that const reference to Regex object.
             * @returns A boolean value.
             */
            inline bool operator> (const Regex& that) const throw();

            /// Get regular expression string.
            inline const std::string& operator()() const throw() { return _str; }

            /// Get regular expression string.
            inline const std::string& str() const throw() { return _str; }

            /** Is this regular expression std::string empty?
             * @returns A boolean value.
             */
            inline bool empty() const throw();

            /// Get CFLAGS.
            inline int cflags() const throw();
            /// Set CFLAGS.
            inline void set_cflags(int cflags) throw();

            /// Get EFLAGS.
            inline int eflags() const throw();
            /// Set EFLAGS.
            inline void set_eflags(int eflags) throw();

        private:
            /// Clean up compiled regex_t
            void cleanup() throw();
            /// Compile regex.
            void compile() throw (BadRegex);

            std::string _str;
            bool        _compiled;
            int         _cflags;
            int         _eflags;
            regex_t     _regex;
    };

    inline Regex&
    Regex::operator= (const std::string& re) throw (BadRegex)
    {
        this->assign(re);
        return *this;
    }

    inline bool
    Regex::operator== (const std::string& cmp) const throw()
    {
        return (regexec(&_regex, cmp.c_str(), 0, NULL, _eflags) == 0);
    }

    inline bool
    Regex::operator!= (const std::string& cmp) const throw()
    {
        return not (*this == cmp);
    }

    inline bool
    Regex::operator== (const Regex& that) const throw()
    {
        return (_str == that._str);
    }

    inline bool
    Regex::operator!= (const Regex& that) const throw()
    {
        return (_str != that._str);
    }

    inline bool
    Regex::operator< (const Regex& that) const throw()
    {
        return (_str < that._str);
    }

    inline bool
    Regex::operator> (const Regex& that) const throw()
    {
        return (_str > that._str);
    }

    inline bool
    Regex::empty() const throw()
    {
        return _str.empty();
    }

    inline int
    Regex::cflags() const throw()
    {
        return _cflags;
    }

    inline void
    Regex::set_cflags(int cflags) throw()
    {
        _cflags = cflags;
    }

    inline int
    Regex::eflags() const throw()
    {
        return _eflags;
    }

    inline void
    Regex::set_eflags(int eflags) throw()
    {
        _eflags = eflags;
    }

    ///@{
    /// Compare a Regex with a std::string on the left-hand side.
    inline bool
    operator==(const std::string& lhs, const Regex& rhs) throw()
    {
        return (rhs == lhs);
    }

    inline bool
    operator!=(const std::string& lhs, const Regex& rhs) throw()
    {
        return (rhs != lhs);
    }
    ///@}

    /**
     * @class RegexMap regex.hh herdstat/util/regex.hh
     * @brief Acts like an unsorted map (vector of unique pairs) with Regex
     * objects mapped to objects of type T.  Provides a few map-compatible
     * member functions such as insert(), operator[](), and find().
     */

    template <typename T>
    class RegexMap
        : public herdstat::util::VectorBase<std::pair<Regex, T> >
    {
        public:
            typedef herdstat::util::VectorBase<std::pair<Regex, T> > base_type;
            typedef typename base_type::container_type container_type;
            typedef typename container_type::size_type size_type;
            typedef typename container_type::difference_type difference_type;
            typedef typename container_type::value_type value_type;
            typedef typename container_type::iterator iterator;
            typedef typename container_type::const_iterator const_iterator;
            typedef Regex key_type;
            typedef T mapped_type;

            mapped_type& operator[](const key_type& k);
            std::pair<iterator, bool> insert(const value_type& v);

            inline iterator find(const std::string& str);
            inline const_iterator find(const std::string& str) const;
    };

    template <typename T>
    inline typename RegexMap<T>::iterator
    RegexMap<T>::find(const std::string& str)
    {
        for (iterator i = this->begin() ; i != this->end() ; ++i)
            if (i->first == str) return i;
        return this->end();
    }

    template <typename T>
    inline typename RegexMap<T>::const_iterator
    RegexMap<T>::find(const std::string& str) const
    {
        for (const_iterator i = this->begin() ; i != this->end() ; ++i)
            if (i->first == str) return i;
        return this->end();
    }

    template <typename T>
    typename RegexMap<T>::mapped_type&
    RegexMap<T>::operator[](const key_type& k)
    {
        for (iterator i = this->begin() ; i != this->end() ; ++i)
            if (i->first == k) return i->second;
        return this->insert(this->end(), value_type(k, "")).second;
    }

    template <typename T>
    std::pair<typename RegexMap<T>::iterator, bool>
    RegexMap<T>::insert(const value_type& v)
    {
        for (iterator i = this->begin() ; i != this->end() ; ++i)
            if (i->first == v.first)
                return std::pair<iterator, bool>(this->end(), false);
        return std::pair<iterator, bool>(
                base_type::insert(this->end(), v), true);
    }

} // namespace util
} // namespace herdstat

#endif /* HAVE_REGEX_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
