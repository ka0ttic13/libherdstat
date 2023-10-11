/*
 * libherdstat -- herdstat/util/regex.cc
 * $Id: regex.cc 189 2005-12-11 13:32:32Z ka0ttic $
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

/* use POSIX regular expressions */
#ifndef _POSIX_C_SOURCE
# define _POSIX_C_SOURCE    200112
#endif

#include <sys/types.h>
#include <regex.h>

#include <herdstat/util/regex.hh>

namespace herdstat {
namespace util {
/*** static members **********************************************************/
const Regex::Cflags Regex::extended = Regex::Cflags(REG_EXTENDED);
const Regex::Cflags Regex::icase = Regex::Cflags(REG_ICASE);
const Regex::Cflags Regex::nosub = Regex::Cflags(REG_NOSUB);
const Regex::Cflags Regex::newline = Regex::Cflags(REG_NEWLINE);
const Regex::Eflags Regex::notbol = Regex::Eflags(REG_NOTBOL);
const Regex::Eflags Regex::noteol = Regex::Eflags(REG_NOTEOL);
/*****************************************************************************/
Regex::Regex() throw()
    : _str(), _compiled(false), _cflags(0), _eflags(0), _regex()
{
}
/*****************************************************************************/
Regex::Regex(const Regex& that) throw (BadRegex)
    : _str(), _compiled(false), _cflags(0), _eflags(0), _regex()
{
    *this = that;
}
/*****************************************************************************/
Regex::Regex(int c, int e) throw()
    : _str(), _compiled(false), _cflags(c), _eflags(e), _regex()
{
}
/*****************************************************************************/
Regex::Regex(const std::string &regex, int c, int e) throw (BadRegex)
    : _str(regex), _compiled(false), _cflags(c), _eflags(e), _regex()
{
    this->compile();
}
/*****************************************************************************/
Regex::~Regex() throw()
{
    if (this->_compiled)
        this->cleanup();
}
/*****************************************************************************/
Regex&
Regex::operator= (const Regex& that) throw (BadRegex)
{
    /* compiler-generated copy constructor/assignment operator won't do
     * since we need to free the old regex_t and compile the new one */

    this->assign(that._str, that._cflags, that._eflags);
    return *this;
}
/*****************************************************************************/
void
Regex::assign(const std::string& regex) throw (BadRegex)
{
    if (this->_compiled)
        this->cleanup();

    this->_str.assign(regex);
    this->compile();
}
/*****************************************************************************/
void
Regex::assign(const std::string &regex, int c, int e) throw (BadRegex)
{
    if (this->_compiled)
        this->cleanup();

    this->_str.assign(regex);
    this->_cflags = c;
    this->_eflags = e;

    this->compile();
}
/*****************************************************************************/
void
Regex::compile() throw (BadRegex)
{
    if (this->_compiled)
        this->cleanup();

    int ret = regcomp(&(this->_regex), this->_str.c_str(), this->_cflags);
    if (ret != 0)
        throw BadRegex(ret, &(this->_regex));

    this->_compiled = true;
}
/*****************************************************************************/
void
Regex::cleanup() throw()
{
    regfree(&(this->_regex));
    this->_compiled = false;
    this->_str.clear();
}
/*****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
