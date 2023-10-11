/*
 * libherdstat -- herdstat/util/string.hh
 * $Id: string.hh 219 2005-12-26 12:31:04Z ka0ttic $
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

#ifndef HAVE_STRING_HH
#define HAVE_STRING_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/string.hh
 * @brief Defines string-related classes/functions.
 */

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstdarg>
#include <cerrno>
#include <cctype>
#include <cstring>

#include <herdstat/exceptions.hh>

namespace herdstat {
namespace util {

    /**
     * Return the basename of the given path.
     * @param path path string.
     * @returns basename of @a path.
     */

    std::string basename(const std::string& path) throw();
    
    /**
     * Return the dirname of the given path.
     * @param path path string.
     * @returns directory that @a path is located in.
     */

    std::string dirname(const std::string& path) throw();

    /**
     * Chop file extension from the given path.
     * @param path path string.
     * @param depth Number of period-delimited extensions to chop.
     * @returns Resulting string.
     */

    const char *chop_fileext(const std::string& path,
                             unsigned short depth = 1) throw();

    /**
     * Tidy whitespace of the given string.
     * @param s String object
     * @returns Resulting std::string object.
     */

    std::string tidy_whitespace(const std::string& s) throw();

    //@{
    /// sprintf() wrappers
    std::string sprintf(const char *, ...) throw();
    std::string sprintf(const char *, va_list) throw();
    std::string sprintf(const std::string&, ...) throw();
    std::string sprintf(const std::string&, va_list) throw();
    //@}

    /** Function template for splitting a string using the given delimiter and
     * writing each part to the given output iterator.
     * @param str string to split.
     * @param result output iterator to write parts to.
     * @param delim Delimiter to use (defaults to " ").
     * @param append_empty Insert an empty element if two consecutive delimiters
     * are encountered?
     *
     * @section example Example
     *
@code
std::string foo("This is an example of using util::split");
std::vector<std::string> foov;
util::split(foo, std::back_inserter(foov));
...
std::set<std::string> foos;
util::split(foo, std::inserter(foos, foos.end()));
@endcode
     */
    template <typename OutputIterator>
    void split(const std::string& str, OutputIterator result,
               const std::string& delim = " ", bool append_empty = false);

    /** Function template for creating a string from the range [first,last)
     * using the specified delimiter in between each element.
     * @param first beginning input iterator.
     * @param last ending input iterator.
     * @param delim Delimiter to use (defaults to " ").
     * @returns resulting string.
     *
     * @section example Example
     *
@code
std::vector<std::string> foov;
foov.push_back("This");
foov.push_back("is an example");
foov.push_back("of using util::join");
std::string foo(util::join(foov.begin(), foov.end()));
@endcode
     */
    template <typename InputIterator>
    std::string join(InputIterator first, InputIterator last,
                     const std::string& delim = " ");

    /**
     * Return a copy of the given string with the ASCII color sequences removed.
     * @param s string object.
     * @returns Resulting string object.
     */

    std::string strip_colors(const std::string& s) throw();

    /**
     * Determine if all characters in the given string are whitespace.
     * @param s string.
     * @returns true if all chars are whitespace.
     */

    inline bool
    is_all_whitespace(const std::string& s) throw()
    {
        const std::string::difference_type size(s.size());
        return (std::count_if(s.begin(), s.end(), ::isspace) == size);
    }

    /**
     * Convert string to all lowercase.
     * @param s String object.
     * @returns Resulting string object.
     */

    inline std::string
    lowercase(const std::string& s) throw()
    {
        std::string result;
        std::transform(s.begin(), s.end(),
            std::back_inserter(result), ::tolower);
        return result;
    }

    /**
     * Convert string to all lowercase (in place).
     * @param s String object.
     */

    inline void
    lowercase_inplace(std::string& s) throw()
    {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    }

    /** strdup replacement in case it's not available from your C library.
     * @param s string to duplicate.
     * @returns Duplicated string (memory obtained with malloc()).
     * @exception std::bad_alloc
     */
    inline char *
    strdup(const char * const s) throw (std::bad_alloc)
    {
        char *tmp = static_cast<char *>(std::malloc(std::strlen(s) + 1));
        if (not tmp)
            throw std::bad_alloc();

        std::strcpy(tmp, s);
        return tmp;
    }

    /**
     * Convert a type to a std::string.
     * @param v Value of type T.
     * @returns A std::string object.
     */

    template <typename T>
    std::string
    stringify(const T& v)
    {
        std::ostringstream os;
        os << v;
        return os.str();
    }

    /// stringify specialization for bool
    template <>
    inline std::string
    stringify<bool>(const bool& v)
    {
        std::ostringstream os;
        os << std::boolalpha << v;
        return os.str();
    }

    /// stringify specialization for std::vector<std::string>
    template <>
    inline std::string
    stringify<std::vector<std::string> >(const std::vector<std::string>& v)
    {
        return join(v.begin(), v.end());
    }

    /// stringify specialization for std::string.
    template <>
    inline std::string
    stringify<std::string>(const std::string& v)
    {
        return v;
    }

    /**
     * Convert a std::string to a type.
     * @param s A std::string object.
     * @returns Value of type T.
     */

    template <typename T>
    T
    destringify(const std::string& s) throw (BadCast)
    {
        std::istringstream is(s.c_str());

        T v;
        is >> v;

        if (not is.eof())
            throw BadCast("Failed to cast '"+s+"'.");

        return v;
    }

    /// destringify specialization for std::vector<std::string>.
    template <>
    inline std::vector<std::string>
    destringify<std::vector<std::string> >(const std::string& s) throw (BadCast)
    {
        std::vector<std::string> v;
        split(s, std::back_inserter(v));
        return v;
    }

    /// destringify specialization for int
    template <>
    inline int
    destringify<int>(const std::string& s) throw (BadCast)
    {
        char *invalid;
        int result = std::strtol(s.c_str(), &invalid, 10);
        if (*invalid)
            throw BadCast("Failed to cast '"+s+"' to int.");
        return result;
    }

    /// destringify specialization for long
    template <>
    inline long
    destringify<long>(const std::string& s) throw (BadCast)
    {
        char *invalid;
        long result = std::strtol(s.c_str(), &invalid, 10);
        if (*invalid)
            throw BadCast("Failed to cast '"+s+"' to long.");
        return result;
    }

    /// destringify specialization for unsigned long
    template <>
    inline unsigned long
    destringify<unsigned long>(const std::string& s) throw (BadCast)
    {
        char *invalid;
        unsigned long result = std::strtoul(s.c_str(), &invalid, 10);
        if (*invalid or ((result == ULONG_MAX) and (errno == ERANGE)))
            throw BadCast("Failed to cast '"+s+"' to unsigned long.");
        return result;
    }

    /// destringify specialization for double
    template <>
    inline double
    destringify<double>(const std::string& s) throw (BadCast)
    {
        char *invalid;
        double result = std::strtod(s.c_str(), &invalid);
        if (*invalid)
            throw BadCast("Failed to cast '"+s+"' to double.");
        return result;
    }

    /// destringify specialization for float
    template <>
    inline float
    destringify<float>(const std::string& s) throw (BadCast)
    {
        char *invalid;
        float result = std::strtod(s.c_str(), &invalid);
        if (*invalid)
            throw BadCast("Failed to cast '"+s+"' to float.");
        return result;
    }
    
    /// destringify specialization for bool
    template <>
    inline bool
    destringify<bool>(const std::string& s) throw (BadCast)
    {
        if (s == "true" or s == "yes" or s == "on")  return true;
        if (s == "false" or s == "no" or s == "off") return false;
        return destringify<int>(s);
    }

    template <typename OutputIterator>
    void split(const std::string& str, OutputIterator result,
               const std::string& delim, bool append_empty)
    {
        if (str.empty())
            return;

        std::string::size_type pos, lpos = 0;

        while (true)
        {
	    if ((pos = str.find(delim, lpos)) == std::string::npos)
	    {
	        *result++ = str.substr(lpos);
	        break;
	    }
	
	    const std::string sub(str.substr(lpos, pos - lpos));
	    if (not sub.empty() or append_empty)
	        *result++ = sub;

	    lpos = pos + delim.length();
        }
    }

    template <typename InputIterator>
    std::string
    join(InputIterator first, InputIterator last,
         const std::string& delim)
    {
        std::string result;

        while (first != last)
        {
	    result += *first++;
	    if (first != last)
	        result += delim;
        }

        return result;
    }

} // namespace util
} // namespace herdstat

#endif /* HAVE_STRING_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
