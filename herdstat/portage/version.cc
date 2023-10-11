/*
 * libherdstat -- herdstat/portage/version.cc
 * $Id: version.cc 204 2005-12-22 15:57:43Z ka0ttic $
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

#include <locale>
#include <vector>
#include <iterator>
#include <memory>
#include <cstdlib>
#include <climits>
#include <cassert>

#include <herdstat/util/misc.hh>
#include <herdstat/util/string.hh>
#include <herdstat/util/algorithm.hh>
#include <herdstat/portage/util.hh>
#include <herdstat/portage/functional.hh>
#include <herdstat/portage/exceptions.hh>
#include <herdstat/portage/version.hh>

// {{{ ValidSuffixes
struct SuffixLess : std::binary_function<std::string, std::string, bool>
{
    /* s1 < s2? */
    bool operator()(const std::string& s1, const std::string& s2) const
    {
        if (s1 == s2)  return false;
        if (s1 == "p") return false;
        if (s2 == "p") return true;

        /* except for "p", they are already
         * sorted by std::string::operator< */
        return (s1 < s2);
    }
};

class ValidSuffixes
{
    public:
        typedef std::vector<std::string> container_type;
        typedef container_type::value_type value_type;
        typedef container_type::const_iterator const_iterator;

        /* for testing against return value of find() */
        inline const_iterator end() const { return _s.end(); }

        /* get location of v or end() if it doesn't exist */
        inline const_iterator find(const value_type& v) const
        {
            std::pair<const_iterator, const_iterator> p =
                std::equal_range(_s.begin(), _s.end(), v, SuffixLess());
            return (p.first == p.second ? _s.end() : p.first);
        }
        
        /* does v exist? */
        inline bool count(const value_type& v) const
        {
            return std::binary_search(_s.begin(), _s.end(), v, SuffixLess());
        }

    private:
        friend const ValidSuffixes& GlobalValidSuffixes();

        ValidSuffixes() : _s()
        {
            const char * const suffixes[] = {"alpha","beta","pre","rc","p"};
            _s.assign(suffixes, suffixes+(sizeof(suffixes)/sizeof(suffixes[0])));
        }

        container_type _s;
};

const ValidSuffixes&
GlobalValidSuffixes()
{
    static ValidSuffixes s;
    return s;
}
// }}}

namespace herdstat {
namespace portage {
/****************************************************************************/
// {{{ VersionComponents
/****************************************************************************/
VersionComponents::VersionComponents() throw()
    : _verstr(), _vmap()
{
}
/****************************************************************************/
VersionComponents::VersionComponents(const std::string &path) throw()
    : _verstr(util::chop_fileext(util::basename(path))), _vmap()
{
    this->parse();
}
/****************************************************************************/
VersionComponents::~VersionComponents() throw()
{
}
/****************************************************************************/
void
VersionComponents::assign(const std::string& path) throw()
{
    _verstr.assign(util::chop_fileext(util::basename(path)));
    _vmap.clear();
    this->parse();
}
/****************************************************************************/
void
VersionComponents::parse() throw()
{
    /* append -r0 if necessary */
    std::string::size_type pos = _verstr.rfind("-r0");
    if (pos == std::string::npos)
    {
        if (((pos = _verstr.rfind("-r")) == std::string::npos) or
            (((pos+2) <= _verstr.size()) and 
             not std::isdigit(_verstr.at(pos+2))))
        {
            _verstr.append("-r0");
        }
    }

    std::vector<std::string> parts;
    util::split(_verstr, std::back_inserter(parts), "-");

    /* If parts > 3, ${PN} contains a '-' */
    if (parts.size() > 3)
    {
        std::string PN;
        while (parts.size() > 2)
        {
            PN += "-" + parts.front();
            parts.erase(parts.begin());
        }

        parts.insert(parts.begin(), PN);
    }

    /* this should NEVER != 3. */
    assert(parts.size() == 3);

    /* fill our map with the components */
    std::pair<iterator, bool> pn = _vmap.insert(value_type("PN", parts[0]));
    std::pair<iterator, bool> pv = _vmap.insert(value_type("PV", parts[1]));
    std::pair<iterator, bool> pr = _vmap.insert(value_type("PR", parts[2]));
    assert(pn.second and pv.second and pr.second);
    _vmap.insert(value_type("P", pn.first->second+"-"+pv.first->second));
    std::pair<iterator, bool> pvr = _vmap.insert(value_type("PVR",
        pv.first->second+"-"+pr.first->second));
    _vmap.insert(value_type("PF", pn.first->second+"-"+pvr.first->second));

    /* remove $PN from _verstr */
    std::string::size_type len(_vmap["PN"].length());
    if (_vmap["PN"].find('-') == std::string::npos)
        ++len;
    _verstr.erase(0, len);
}
// }}}
/****************************************************************************/
// {{{ VersionString::suffix
/****************************************************************************/
VersionString::suffix::suffix() throw()
    : _suffix(), _suffix_ver()
{
}
/****************************************************************************/
VersionString::suffix::suffix(const std::string& pvr) throw()
    : _suffix(), _suffix_ver()
{
    this->parse(pvr);
}
/****************************************************************************/
void
VersionString::suffix::parse(const std::string &pvr) const throw()
{
    _suffix_ver.clear();
    _suffix.assign(pvr);

    /* chop revision */
    std::string::size_type pos = _suffix.rfind("-r");
    if (pos != std::string::npos)
        _suffix.erase(pos);

    /* get suffix */
    pos = _suffix.rfind('_');
    if (pos != std::string::npos)
    {
        _suffix.erase(0, pos+1);

        /* get suffix version */
        pos = _suffix.find_first_of("0123456789");
        if (pos != std::string::npos)
        {
            _suffix_ver = _suffix.substr(pos);
            _suffix.erase(pos);
        }

        /* ignore invalid suffixes */
        if (not GlobalValidSuffixes().count(_suffix))
            _suffix.clear();
    }
    else
        _suffix.clear();
}
/****************************************************************************/
bool
VersionString::suffix::operator< (const suffix& that) const throw()
{
    const ValidSuffixes& suffixes(GlobalValidSuffixes());
    ValidSuffixes::const_iterator ti, si;

    ti = suffixes.find(_suffix);
    si = suffixes.find(that._suffix);

    /* both have a suffix */
    if ((ti != suffixes.end()) and (si != suffixes.end()))
    {
        /* same suffix, so compare suffix version */
        if (ti == si)
        {
            if (not _suffix_ver.empty() and not that._suffix_ver.empty())
                return ( util::destringify<unsigned long>(_suffix_ver) <
                         util::destringify<unsigned long>(that._suffix_ver) );
            else if (_suffix_ver.empty() and that._suffix_ver.empty())
                return true;
            else
                return not that._suffix_ver.empty();
        }

        return ti < si;
    }

    /* that has no suffix */
    else if (ti != suffixes.end())
        /* only the 'p' suffix is > than no suffix */
        return not (*ti == "p");
    /* this has no suffix */
    else if (si != suffixes.end())
        /* only the 'p' suffix is > than no suffix */
        return (*si == "p");

    return false;
}
/****************************************************************************/
bool
VersionString::suffix::operator== (const suffix& that) const throw()
{
    const ValidSuffixes& suffixes(GlobalValidSuffixes());
    ValidSuffixes::const_iterator ti, si;

    ti = suffixes.find(_suffix);
    si = suffixes.find(that._suffix);

    /* both have a suffix */
    if ((ti != suffixes.end()) and (si != suffixes.end()))
    {
        /* same suffix, so compare suffix version */
        if (ti == si)
        {
            if (not _suffix_ver.empty() and not that._suffix_ver.empty())
                return ( util::destringify<unsigned long>(_suffix_ver) ==
                         util::destringify<unsigned long>(that._suffix_ver) );
            else if (_suffix_ver.empty() and that._suffix_ver.empty())
                return true;
            else
                return not that._suffix_ver.empty();
        }

        return ti == si;
    }
    else if ((ti != suffixes.end()) or (si != suffixes.end()))
        return false;

    return true;
}
// }}}
/****************************************************************************/
// {{{ VersionString::nosuffix
/****************************************************************************/
VersionString::nosuffix::nosuffix() throw()
    : _version(), _extra()
{
}
/****************************************************************************/
VersionString::nosuffix::nosuffix(const std::string& pv) throw()
    : _version(), _extra()
{
    this->parse(pv);
}
/****************************************************************************/
void
VersionString::nosuffix::parse(const std::string& pv) const throw()
{
    _extra.clear();
    _version.assign(pv);

    /* strip suffix */
    std::string::size_type pos = _version.find('_');
    if (pos != std::string::npos)
        _version.erase(pos);

    /* find first non-digit */
    pos = _version.find_first_not_of("0123456789.");
    if (pos != std::string::npos)
    {
        _extra = _version.substr(pos);
        _version.erase(pos);
    }
}
/****************************************************************************/
bool
VersionString::nosuffix::operator< (const nosuffix& that) const throw()
{
    bool differ = false;
    bool result = false;

    /* std::string comparison should be sufficient for == */
    if (*this == that)
        return false;
    else if (_version == that._version)
        return _extra < that._extra;

    std::vector<std::string> thisparts, thatparts;
    util::split(_version, std::back_inserter(thisparts), ".");
    util::split(that._version, std::back_inserter(thatparts), ".");

    std::vector<std::string>::size_type stoppos =
        std::min<std::vector<std::string>::size_type>(thisparts.size(),
                                                       thatparts.size());

    /* TODO: if thisparts.size() and thatpart.size() == 1, convert to long
     * and compare */

    std::vector<std::string>::iterator thisiter, thatiter;
    for (thisiter = thisparts.begin(), thatiter = thatparts.begin() ;
         stoppos != 0 ; ++thisiter, ++thatiter, --stoppos)
    {
        /* loop until the version components differ */

        /* TODO: use std::mismatch() ?? */
        unsigned long thisver =
            util::destringify<unsigned long>(*thisiter);
        unsigned long thatver =
            util::destringify<unsigned long>(*thatiter);

        bool same = false;
        if (thisver == thatver)
        {
            /* 1 == 01 ? they're the same in comparison speak but 
             * absolutely not the same in version std::string speak */
            if (*thisiter == (std::string("0") + *thatiter))
                same = true;
            else
                continue;
        }
        
        result = ( same ? true : thisver < thatver );
        differ = true;
        break;
    }

    if (not differ)
        return (thisparts.size() <= thatparts.size());

    return result;
}
/****************************************************************************/
bool
VersionString::nosuffix::operator== (const nosuffix& that) const throw()
{
    /* std::string comparison should be sufficient for == */
    return ((_version == that._version) and
            (_extra   == that._extra));
}
// }}}
/****************************************************************************/
// {{{ VersionString
/****************************************************************************/
VersionString::VersionString() throw()
    : _ebuild(), _v(), _verstr(), _suffix(), _version()
{
}
/****************************************************************************/
VersionString::VersionString(const std::string& path) throw()
    : _ebuild(path), _v(path), _verstr(_v.version()),
      _suffix(_v["PVR"]), _version(_v["PV"])
{
}
/****************************************************************************/
VersionString::VersionString(const VersionString& that) throw()
    : _ebuild(), _v(), _verstr(), _suffix(), _version()
{
    *this = that;
}
/****************************************************************************/
VersionString&
VersionString::operator=(const VersionString& that) throw()
{
    const_cast<std::string&>(_ebuild) = that._ebuild;
    const_cast<VersionComponents&>(_v) = that._v;
    const_cast<std::string&>(_verstr) = that._verstr;
    const_cast<suffix&>(_suffix) = that._suffix;
    const_cast<nosuffix&>(_version) = that._version;
    return *this;
}
/****************************************************************************/
void
VersionString::assign(const std::string& path) throw()
{
    _ebuild.assign(path);
    _v.assign(path);
    _verstr.assign(_v.version());
    _suffix.assign(_v["PVR"]);
    _version.assign(_v["PV"]);
}
/****************************************************************************/
std::string
VersionString::str() const throw()
{
    /* chop -r0 if necessary */
    std::string::size_type pos = _verstr.rfind("-r0");
    if (pos != std::string::npos)
        return _verstr.substr(0, pos);

    return _verstr;
}
/****************************************************************************/
bool
VersionString::operator< (const VersionString& that) const throw()
{
    if (_version < that._version)
        return true;
    else if (_version == that._version)
    {
        if (_suffix < that._suffix)
            return true;
        else if (_suffix == that._suffix)
        {
            unsigned long thisrev =
                util::destringify<unsigned long>(_v["PR"].substr(1));
            unsigned long thatrev =
                util::destringify<unsigned long>(that._v["PR"].substr(1));
            return (thisrev <= thatrev);
        }
    }

    return false;
}
// }}}
/****************************************************************************/
// {{{ Versions
/****************************************************************************/
Versions::Versions() throw()
    : util::SetBase<VersionString>()
{
}
/****************************************************************************/
Versions::Versions(const std::string& path) throw()
    : util::SetBase<VersionString>()
{
    this->assign(path);
}
/****************************************************************************/
Versions::Versions(const std::vector<std::string>& paths) throw()
    : util::SetBase<VersionString>()
{
    std::for_each(paths.begin(), paths.end(),
        std::bind2nd(util::Appender<Versions, std::string>(), this));
}
/****************************************************************************/
Versions::~Versions() throw()
{
}
/****************************************************************************/
void
Versions::assign(const std::string& path) throw()
{
    this->clear();

    if (not util::is_dir(path))
        return;

    const util::Directory pkgdir(path);
    util::copy_if(pkgdir.begin(), pkgdir.end(),
        std::inserter(this->container(), this->end()), IsEbuild());
}
/****************************************************************************/
void
Versions::append(const std::string& path) throw()
{
    const util::Directory pkgdir(path);
    util::copy_if(pkgdir.begin(), pkgdir.end(),
        std::inserter(this->container(), this->end()), IsEbuild());
}
/****************************************************************************/
// }}}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
