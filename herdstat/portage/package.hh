/*
 * libherdstat -- herdstat/portage/package.hh
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

#ifndef _HAVE__PACKAGE_HH
#define _HAVE__PACKAGE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/package.hh
 * @brief Provides the Package class definition.
 */

#include <herdstat/util/regex.hh>
#include <herdstat/portage/config.hh>
#include <herdstat/portage/ebuild.hh>
#include <herdstat/portage/keywords.hh>

namespace herdstat {
namespace portage {

    class PackageDirectory;

    /**
     * @class Package package.hh herdstat/portage/package.hh
     * @brief Represents a "package" that exists in either PORTDIR or an
     * overlay.
     */

    class Package
    {
        public:
            /// Default constructor.
            Package();

            /// Copy constructor.
            Package(const Package& that);

            /** Constructor.
             * @param name Package name.
             * @param portdir Directory package lives in.
             */
            Package(const std::string& name,
                    const std::string& portdir = GlobalConfig().portdir());

            /// Destructor.
            ~Package();

            /// Copy assignment operator.
            Package& operator= (const Package& that);

            /// Implicit conversion to category/package string.
            inline operator const std::string&() const;

            /// Get full category/package name.
            inline const std::string& full() const;
            /// Set full category/package name.
            void set_full(const std::string& full);

            /// Get package name.
            inline const std::string& name() const;
            /// Set package name.
            void set_name(const std::string& name);

            /// Get category this package is in.
            inline const std::string& category() const;
            /// Set category this package is in.
            inline void set_category(const std::string& cat);

            /// Get portdir this package is in (may be an overlay).
            inline const std::string& portdir() const;
            /// Set portdir this package is in.
            inline void set_portdir(const std::string& dir);

            /// Get path to package directory.
            inline const std::string& path() const;
            /// Set path to package directory.
            inline void set_path(const std::string& path);

            /// Is this package located in an overlay?
            inline bool in_overlay() const;

            /// Get a KeywordsMap object for each ebuild of this package.
            inline const KeywordsMap& keywords() const;

            /// Get a PackageDirectory object for this package.
            const PackageDirectory& pkgdir() const;

            ///@{
            /** Compare that Package to this Package.
             * Compares the full category/package string and portdir.
             */
            inline bool operator< (const Package& that) const;
            inline bool operator<=(const Package& that) const;
            inline bool operator> (const Package& that) const;
            inline bool operator>=(const Package& that) const;
            inline bool operator==(const Package& that) const;
            inline bool operator!=(const Package& that) const;
            ///@}

            ///@{
            /// Compare the given string to our full category/package name.
            inline bool operator< (const std::string& full) const;
            inline bool operator<=(const std::string& full) const;
            inline bool operator> (const std::string& full) const;
            inline bool operator>=(const std::string& full) const;
            inline bool operator==(const std::string& full) const;
            inline bool operator!=(const std::string& full) const;
            ///@}

            ///@{
            /** Compare the given regular expression to our full
             * category/package name.
             */
            inline bool operator==(const util::Regex& re) const;
            inline bool operator!=(const util::Regex& re) const;
            ///@}

        private:
            std::string _name;
            std::string _cat;
            std::string _dir;
            std::string _full;
            std::string _path;
            mutable KeywordsMap *_kwmap;
            mutable PackageDirectory *_pkgdir;
    };

    inline Package::operator const std::string&() const { return _full; }
    inline const std::string& Package::category() const { return _cat; }
    inline void Package::set_category(const std::string& cat) { _cat.assign(cat); }
    inline const std::string& Package::name() const { return _name; }
    inline const std::string& Package::portdir() const { return _dir; }
    inline const std::string& Package::full() const { return _full; }
    inline void Package::set_portdir(const std::string& dir) { _dir.assign(dir); }
    inline void Package::set_path(const std::string& path) { _path.assign(path); }
    inline const std::string& Package::path() const
    { assert(not _path.empty()); return _path; }

    inline bool Package::in_overlay() const
    {
        static const std::string& portdir(GlobalConfig().portdir());
        return (_dir != portdir);
    }

    inline bool
    Package::operator< (const Package& that) const
    {
        /* if package names are equal, this is only less than that if this
         * portdir is the real portdir and that portdir isn't */
        return (_full == that._full ?
                    not ((not in_overlay() and not that.in_overlay()) or
                        not that.in_overlay()) : _full < that._full);
    }

    inline bool
    Package::operator<=(const Package& that) const
    { return not (*this > that); }

    inline bool
    Package::operator> (const Package& that) const
    { return (that < *this); }
    
    inline bool
    Package::operator>= (const Package& that) const
    { return not (*this < that); }
    
    inline bool
    Package::operator== (const Package& that) const
    { return ((_full == that._full) and (_dir == that._dir)); }
    
    inline bool
    Package::operator!= (const Package& that) const
    { return not (*this == that); }

    inline bool
    Package::operator< (const std::string& full) const
    { return (_full < full); }
    inline bool
    Package::operator<=(const std::string& full) const
    { return (_full <= full); }
    inline bool
    Package::operator> (const std::string& full) const
    { return (_full > full); }
    inline bool
    Package::operator>=(const std::string& full) const
    { return (_full >= full); }
    inline bool
    Package::operator==(const std::string& full) const
    { return (_full == full); }
    inline bool
    Package::operator!=(const std::string& full) const
    { return (_full != full); }

    inline bool
    Package::operator==(const util::Regex& re) const
    { return (re == _full); }

    inline bool
    Package::operator!=(const util::Regex& re) const
    { return (re != _full); }

    inline const KeywordsMap&
    Package::keywords() const
    {
        if (not _kwmap)
            _kwmap = new KeywordsMap(_path);
        return *_kwmap;
    }

    ///@{
    /** Comparison operators for when a Package is on the right hand side.
     * @param lhs const reference to a package name string.
     * @param rhs const reference to a Package object.
     * @returns A boolean value.
     */
    inline bool
    operator< (const std::string& lhs, const Package& rhs)
    {
        return (lhs < rhs.full());
    }

    inline bool
    operator<=(const std::string& lhs, const Package& rhs)
    {
        return (lhs <= rhs.full());
    }

    inline bool
    operator> (const std::string& lhs, const Package& rhs)
    {
        return (lhs > rhs.full());
    }

    inline bool
    operator>=(const std::string& lhs, const Package& rhs)
    {
        return (lhs >= rhs.full());
    }

    inline bool
    operator==(const std::string& lhs, const Package& rhs)
    {
        return (lhs == rhs.full());
    }

    inline bool
    operator!=(const std::string& lhs, const Package& rhs)
    {
        return (lhs != rhs.full());
    }
    ///@}

    ///@{
    /** Comparison operators for when a Package is on the right hand side.
     * @param lhs const reference to a util::Regex object.
     * @param rhs const reference to a Package object.
     */
    inline bool
    operator==(const util::Regex& lhs, const Package& rhs)
    {
        return (lhs == rhs.full());
    }

    inline bool
    operator!=(const util::Regex& lhs, const Package& rhs)
    {
        return (lhs != rhs.full());
    }
    ///@}

} // namespace portage
} // namespace herdstat

#endif /* _HAVE__PACKAGE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
