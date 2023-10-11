/*
 * libherdstat -- herdstat/portage/exceptions.cc
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/portage/exceptions.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
BadVersionSuffix::BadVersionSuffix(const std::string& msg) throw()
    : Exception(msg)
{
}
/****************************************************************************/
BadVersionSuffix::~BadVersionSuffix() throw()
{
}
/****************************************************************************/
const char *
BadVersionSuffix::what() const throw()
{
    std::string msg("Invalid version suffix: ");
    msg += this->message();
    return msg.c_str();
}
/****************************************************************************/
AmbiguousPkg::AmbiguousPkg(const std::vector<std::string>& pkgs) throw()
    : _name(), _packages(pkgs)
{
    assert(not _packages.empty());
    _set_name(_packages.front());
}
/****************************************************************************/
void
AmbiguousPkg::_set_name(const std::string& name) throw()
{
    std::string::size_type pos = name.find('/');
    _name.assign(pos == std::string::npos ? name : name.substr(++pos));
}
/****************************************************************************/
AmbiguousPkg::~AmbiguousPkg() throw()
{
}
/****************************************************************************/
NonExistentPkg::NonExistentPkg(const std::string& msg) throw()
    : Exception(msg), _regex(false)
{
}
/****************************************************************************/
NonExistentPkg::NonExistentPkg(const util::Regex& re) throw()
    : Exception(re()), _regex(true)
{
}
/****************************************************************************/
NonExistentPkg::~NonExistentPkg() throw()
{
}
/****************************************************************************/
const char *
NonExistentPkg::what() const throw()
{
    return (_regex ?
                (std::string("Failed to find any packages matching '")+
                this->message() + "'.").c_str() :
                (std::string(this->message()) + " doesn't seem to exist.").c_str());
}
/****************************************************************************/
QAException::QAException(const std::string& msg) throw()
    : Exception(msg)
{
}
/****************************************************************************/
QAException::~QAException() throw()
{
}
/****************************************************************************/
QAErrnoException::QAErrnoException(const std::string& msg) throw()
    : ErrnoException(msg)
{
}
/****************************************************************************/
QAErrnoException::~QAErrnoException() throw()
{
}
/****************************************************************************/
const char *
QAErrnoException::what() const throw()
{
    std::string msg("QA Violation: ");
    msg += ErrnoException::what();
    return msg.c_str();
}
/****************************************************************************/
InvalidKeywordMask::InvalidKeywordMask(const char c) throw()
    : Exception(), _mask(c)
{
}
/****************************************************************************/
InvalidKeywordMask::~InvalidKeywordMask() throw()
{
}
/****************************************************************************/
const char *
InvalidKeywordMask::what() const throw()
{
    std::string msg("Invalid  keyword mask character '");
    msg += _mask + "'.";
    return msg.c_str();
}
/****************************************************************************/
InvalidArch::InvalidArch(const std::string& arch) throw()
    : Exception(arch)
{
}
/****************************************************************************/
InvalidArch::~InvalidArch() throw()
{
}
/****************************************************************************/
const char *
InvalidArch::what() const throw()
{
    std::string msg("Invalid arch '");
    msg += std::string(this->message()) + "'.";
    return msg.c_str();
}
/****************************************************************************/
InvalidAtom::InvalidAtom(const std::string& atom) throw()
    : Exception("Invalid DEPEND atom '%s'", atom.c_str())
{
}
/****************************************************************************/
InvalidAtom::~InvalidAtom() throw()
{
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
