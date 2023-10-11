/*
 * libherdstat -- herdstat/portage/keywords.cc
 * $Id: keywords.cc 204 2005-12-22 15:57:43Z ka0ttic $
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

#include <cstring>

#include <herdstat/exceptions.hh>
#include <herdstat/util/misc.hh>
#include <herdstat/util/string.hh>
#include <herdstat/util/algorithm.hh>
#include <herdstat/portage/functional.hh>
#include <herdstat/portage/util.hh>
#include <herdstat/portage/config.hh>
#include <herdstat/portage/keywords.hh>

namespace herdstat {
namespace portage {
/*** static members *********************************************************/
const char * const Keyword::_valid_masks = "-~";
/****************************************************************************/
Keyword::maskc::maskc() throw()
    : _c('\0')
{
}
/****************************************************************************/
Keyword::maskc&
Keyword::maskc::operator=(const char mc) throw (InvalidKeywordMask)
{
    BacktraceContext c("portage::Keyword::maskc::operator=(" + std::string(1, mc) + ")");

    if (std::strchr(_valid_masks, mc) == NULL)
        throw InvalidKeywordMask(mc);

    _c = mc;
    return *this;
}
/****************************************************************************/
bool
Keyword::maskc::operator< (const maskc& that) const throw()
{
    if (_c == that._c)
        return false;

    /* '-' is less than everything */
    if (_c == '-')
        return true;

    if (not this->empty() and that.empty())
        return true;

    return false;
}
/****************************************************************************/
Keyword::Keyword(const std::string& kw) throw (InvalidKeywordMask, InvalidArch)
    : _arch(), _mask(), _valid_archs(GlobalConfig().archs())
{
    BacktraceContext c("portage::Keyword::Keyword("+kw+")");

    this->parse(kw);

    if (not _valid_archs.count(_arch))
        throw InvalidArch(_arch);
}
/****************************************************************************/
void
Keyword::parse(const std::string& kw) throw (InvalidKeywordMask)
{
    if (std::strchr(_valid_masks, kw[0]))
        _mask = kw[0];

    _arch = (_mask.empty() ? kw : kw.substr(1));
}
/****************************************************************************/
Keywords::Keywords() throw()
    : _ebuild(), _str()
{
}
/****************************************************************************/
Keywords::Keywords(const std::string& path) throw (Exception)
    : _ebuild(path), _str()
{
    this->fill();
    this->format();
}
/****************************************************************************/
Keywords::Keywords(const Ebuild& e) throw (Exception)
    : _ebuild(e), _str()
{
    this->fill();
    this->format();
}
/****************************************************************************/
Keywords::~Keywords() throw()
{
}
/****************************************************************************/
void
Keywords::assign(const std::string& path) throw (Exception)
{
    _ebuild.read(path);
    this->fill();
    this->format();
}
/****************************************************************************/
void
Keywords::assign(const Ebuild& e) throw (Exception)
{
    _ebuild = e;
    this->fill();
    this->format();
}
/****************************************************************************/
void
Keywords::fill() throw (Exception)
{
    BacktraceContext c("portage::Keywords::fill()");

    if (_ebuild["KEYWORDS"].empty())
        throw Exception(_ebuild.path()+": no KEYWORDS variable defined");

    this->clear();

    /* split the keywords string, inserting each into our container */
    util::split(_ebuild["KEYWORDS"],
        std::inserter(this->container(), this->end()));
}
/****************************************************************************/
void
Keywords::format() throw()
{
    static util::ColorMap cmap;

    iterator i = this->begin();
    while (i != this->end())
    {
//    for (iterator i = this->begin() ; i != this->end() ; ++i, ++n)
//    {
        switch (i->mask())
        {
            case '-':
                _str += cmap[red];
                break;
            case '~':
                _str += cmap[yellow];
                break;
            default:
                _str += cmap[blue];
        }

        _str += i->str() + cmap[none];

//        if ((n+1) != this->size())
        if (++i != this->end())
            _str += " ";
    }
}
/****************************************************************************/
struct NewPair
{
    std::pair<VersionString, Keywords>
    operator()(const std::string& ebuild) const
    {
        std::pair<VersionString, Keywords> p;

        p.first.assign(ebuild);

        try
        {
            p.second.assign(ebuild);
        }
        catch (const Exception&)
        {
        }

        return p;
    }
};

KeywordsMap::KeywordsMap(const std::string& pkgdir) throw (Exception)
{
    BacktraceContext c("portage::KeywordsMap::KeywordsMap("+pkgdir+")");

    if (not util::is_dir(pkgdir))
        throw FileException(pkgdir);

    const util::Directory dir(pkgdir);
    util::transform_if(dir.begin(), dir.end(),
        std::inserter(this->container(), this->end()),
        IsEbuild(), NewPair());;
}
/****************************************************************************/
KeywordsMap::~KeywordsMap() throw()
{
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
