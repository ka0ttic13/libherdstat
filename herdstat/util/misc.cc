/*
 * libherdstat -- herdstat/util/misc.cc
 * $Id: misc.cc 189 2005-12-11 13:32:32Z ka0ttic $
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

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <ctime>
#include <unistd.h>

#include <herdstat/exceptions.hh>
#include <herdstat/util/file.hh>
#include <herdstat/util/string.hh>
#include <herdstat/util/misc.hh>

namespace herdstat {
namespace util {
/****************************************************************************/
std::map<ASCIIColor, std::string>&
MakeColorMap()
{
    static std::map<ASCIIColor, std::string> m;
    if (m.empty())
    {
#define INSERT_COLOR(x,y) m.insert(std::make_pair(x, y))

        INSERT_COLOR(red,     "\033[0;31m");
        INSERT_COLOR(green,   "\033[0;32m");
        INSERT_COLOR(blue,    "\033[1;34m");
        INSERT_COLOR(yellow,  "\033[1;33m");
        INSERT_COLOR(orange,  "\033[0;33m");
        INSERT_COLOR(magenta, "\033[1;35m");
        INSERT_COLOR(cyan,    "\033[1;36m");
        INSERT_COLOR(black,   "\033[0;30m");
        INSERT_COLOR(white,   "\033[0;1m");
        INSERT_COLOR(none,    "\033[00m");

#undef INSERT_COLOR

    }

    return m;
}

ColorMap::ColorMap() throw()
    : _cm(MakeColorMap())
{
}

const std::string&
ColorMap::operator[] (const std::string& color) const
{
    if (color == "red") return _cm[red];
    else if (color == "green") return _cm[green];
    else if (color == "blue") return _cm[blue];
    else if (color == "yellow") return _cm[yellow];
    else if (color == "orange") return _cm[orange];
    else if (color == "magenta") return _cm[magenta];
    else if (color == "cyan") return _cm[cyan];
    else if (color == "black") return _cm[black];
    else if (color == "white") return _cm[white];
    
    return _cm[none];
}
/****************************************************************************/
void
#ifdef UNICODE
debug(const gchar *fmt, ...)
#else /* UNICODE */
debug(const char *fmt, ...)
#endif /* UNICODE */
{
#ifdef DEBUG
    va_list v;
    va_start(v, fmt);

    std::string s(util::sprintf(fmt, v));
    std::cerr << "!!! " << s << std::endl;
    
    va_end(v);
#endif /* DEBUG */
}
/****************************************************************************/
std::string
getcwd()
{
    char *pwd = ::getcwd(NULL, 0);
    if (not pwd)
	throw ErrnoException("getcwd");

    std::string s(pwd);
    std::free(pwd);
    return s;
}
/****************************************************************************
 * Given an email address, return the username.                             *
 ****************************************************************************/
std::string
get_user_from_email(const std::string &email)
{
    std::string::size_type pos = email.find('@');
    if (pos == std::string::npos)
        return email;

    return email.substr(0, pos);
}
/****************************************************************************
 * Try to determine user.  This is used for hilighting occurrences          *
 * of the user's username in ouput.  ECHANGELOG_USER is checked first       *
 * since a developer might use a different username than what his           *
 * developer username is.                                                   *
 ****************************************************************************/
std::string
current_user()
{
    std::string user;
    std::string::size_type pos;

    char *result = std::getenv("ECHANGELOG_USER");
    if (result)
    {
	user = result;
	if ((pos = user.find('<')) != std::string::npos)
	{
	    user = user.substr(pos + 1);
	    if ((pos = user.find('>')) != std::string::npos)
		user = user.substr(0, pos);
	}
	else
	    user.clear();
    }
    else if ((result = std::getenv("USER")))
    {
	user = result;
	user += "@gentoo.org";
    }

    return (user.empty() ? "nobody@gentoo.org" : user);
}
/****************************************************************************/
const std::string
format_date(const std::time_t &epoch, const char *fmt)
{
    std::string date;

    if (epoch != 0)
    {
        char buf[255] = { 0 };
        std::strftime(buf, sizeof(buf) - 1, fmt, std::localtime(&epoch));
        date.assign(buf);
    }

    return (date.empty() ? "(no date)" : date);
}

const std::string
format_date(const std::string &epoch, const char *fmt)
{
    return format_date(std::strtol(epoch.c_str(), NULL, 10), fmt);
}
/****************************************************************************/
std::time_t
str2epoch(const char *str, const char *fmt)
{
    BacktraceContext c("herdstat::util::str2epoch");

    struct tm t;
    std::memset(&t, '\0', sizeof(t));
    char *p = strptime(str, fmt, &t);
    if (not p or (*p != '\0'))
        throw BadDate(str);
    return std::mktime(&t);
}
/****************************************************************************/
/* given string in form of "10 January 2000", get elapsed number of years.
 * returns empty string on any failure. */
const std::string
get_elapsed_yrs(const std::string& date)
{
    std::time_t now, joined_date;

    try
    {
        joined_date = str2epoch(date.c_str(), "%d %b %Y");
        if (joined_date == static_cast<std::time_t>(-1))
            return std::string();
    }
    catch (const BadDate& e)
    {
        return std::string();
    }

    if ((now = std::time(NULL)) == static_cast<std::time_t>(-1))
        return std::string();

    double seconds = std::difftime(now, joined_date);
    return (util::sprintf("%.2f", seconds/31536000)+" yrs");
}
/****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
