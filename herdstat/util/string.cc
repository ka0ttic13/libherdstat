/*
 * libherdstat -- herdstat/util/string.cc
 * $Id: string.cc 219 2005-12-26 12:31:04Z ka0ttic $
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
#include <iterator>
#include <vector>
#include <map>
#include <locale>
#include <functional>

#include <herdstat/exceptions.hh>
#include <herdstat/util/string.hh>

namespace herdstat {
namespace util {
/*****************************************************************************/
std::string
basename(const std::string& path) throw()
{
    std::string result(path);
    std::string::size_type pos;

    /* chop all trailing /'s */
    while (result[result.length() - 1] == '/' and result.length() > 1)
	result.erase(result.length() - 1);

    if ((pos = result.rfind('/')) != std::string::npos)
	result = result.substr(pos + 1);

    return ( result.empty() ? std::string("/") : result );
}
/*****************************************************************************/
std::string
dirname(const std::string& path) throw()
{
    std::string result(path);
    std::string::size_type pos;

    /* chop all trailing /'s */
    while (result[result.length() - 1] == '/' and result.length() > 1)
	result.erase(result.length() - 1);

    if ((pos = result.rfind('/')) != std::string::npos)
        result.erase(pos);
    else
        result.assign(".");

    return ( result.empty() ? std::string("/") : result );
}
/*****************************************************************************/
const char *
chop_fileext(const std::string& path, unsigned short depth) throw()
{
    std::string result(path);

    for (; depth > 0 ; --depth)
    {
        std::string::size_type pos = result.rfind('.');
        if (pos != std::string::npos)
            result = result.substr(0, pos);
    }

    return result.c_str();
}
/*****************************************************************************/
struct BothSpaces
{
    bool operator()(const char& c1, const char& c2) const
    { return (std::isspace(c1) and std::isspace(c2)); }
};

std::string
tidy_whitespace(const std::string &s) throw()
{
    if (s.empty())
	return s;

    std::string result;
    std::string::size_type pos;

    /* collapse whitespace */
    std::unique_copy(s.begin(), s.end(),
        std::back_inserter(result), BothSpaces());

    /* replace all newlines with a space */
    std::replace(result.begin(), result.end(), '\n', ' ');

    /* remove any leading whitespace */
    if ((pos = result.find_first_not_of(" \t")) != std::string::npos)
	result.erase(0, pos);

    /* remove any trailing whitespace */
    if ((pos = result.find_last_not_of(" \t")) != std::string::npos)
	result.erase(++pos);

    if (result == " ")
        return std::string();
	
    return result;
}
/*****************************************************************************/
std::string
sprintf(const char *fmt, ...) throw()
{
    va_list v;
    va_start(v, fmt);
    std::string s(util::sprintf(fmt, v));
    va_end(v);
    return s;
}
/*****************************************************************************/
std::string
sprintf(const char *fmt, va_list v) throw()
{
    char *buf;
    vasprintf(&buf, fmt, v);
    std::string s(buf);
    std::free(buf);
    return s;
}
/*****************************************************************************/
std::string
sprintf(const std::string& fmt, ...) throw()
{
    va_list v;
#ifdef HAVE_GCC4
    va_start(v, fmt);
#else
    va_start(v, fmt.c_str());
#endif

    std::string s(util::sprintf(fmt, v));
    va_end(v);
    return s;
}
/*****************************************************************************/
std::string
sprintf(const std::string& fmt, va_list v) throw()
{
    return util::sprintf(fmt.c_str(), v);
}
/*****************************************************************************/
std::string
strip_colors(const std::string& str) throw()
{
    std::string result(str);
    std::string::size_type pos, lpos = 0;

    while ((pos = result.find("\033", lpos)) != std::string::npos)
    {
	std::string::size_type mpos = result.find('m', pos);
	if (mpos == std::string::npos)
	    result.erase(pos);

	result.erase(pos, (mpos-pos)+1);
	lpos = ++pos;
    }

    return result;
}
/*****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
