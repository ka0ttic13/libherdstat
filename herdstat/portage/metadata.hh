/*
 * libherdstat -- herdstat/portage/metadata.hh
 * $Id: metadata.hh 177 2005-12-06 13:02:41Z ka0ttic $
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

#ifndef _HAVE_METADATA_HH
#define _HAVE_METADATA_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/metadata.hh
 * @brief Defines the metadata class.
 */

#include <string>
#include <herdstat/util/regex.hh>
#include <herdstat/portage/herd.hh>

namespace herdstat {
namespace portage {

    /**
     * @class Metadata metadata.hh herdstat/portage/metadata.hh
     * @brief Represents the data contained in a metadata.xml file.
     */

    class Metadata
    {
        public:
            /// Default constructor.
            Metadata();

            /** Constructor.
             * @param pkg Package name.
             */
            Metadata(const std::string &pkg);

            /// Copy constructor.
            Metadata(const Metadata& that);

            /// Destructor.
            ~Metadata();

            /// Copy assignment operator.
            Metadata& operator= (const Metadata& that);

            /// Is this metadata from a cateogry?
            inline bool is_category() const;
            /// Get package name this metadata belongs to.
            inline const std::string& pkg() const;
            /// Get package name this metadata belongs to.
            inline const std::string& name() const; /* synonym for pkg() */
            /// Get long description.
            inline const std::string& longdesc() const;

            /// Set whether this is a category metadata.
            inline void set_category(bool cat);
            /// Set package name.
            inline void set_pkg(const std::string &pkg);
            /// Set long description.
            inline void set_longdesc(const std::string &longdesc);

            /// Get herds contained in this metadata.
            inline Herds& herds();
            /// Get herds contained in this metadata.
            inline const Herds& herds() const;
            /// Get developers contained in this metadata.
            inline Developers& devs();
            /// Get developers contained in this metadata.
            inline const Developers& devs() const;

            ///@{
            /** Determine equivelance of this Metadata compared to that
             * Metadata.  Only compares the package name.
             * @param that const reference to another Metadata object.
             * @returns A boolean value.
             */
            inline bool operator< (const Metadata& that) const;
            inline bool operator<=(const Metadata& that) const;
            inline bool operator> (const Metadata& that) const;
            inline bool operator>=(const Metadata& that) const;
            inline bool operator==(const Metadata& that) const;
            inline bool operator!=(const Metadata& that) const;
            ///@}

        private:
            std::string _pkg;
            std::string _longdesc;
            bool _cat;
            mutable Herds *_herds;
            mutable Developers *_devs;
    };

    inline bool Metadata::is_category() const { return _cat; }
    inline const std::string& Metadata::pkg() const { return _pkg; }
    inline const std::string& Metadata::name() const { return _pkg; }
    inline const std::string& Metadata::longdesc() const { return _longdesc; }
    inline void Metadata::set_category(bool cat) { _cat = cat; }
    inline void Metadata::set_pkg(const std::string& pkg) { _pkg.assign(pkg); }
    inline void Metadata::set_longdesc(const std::string& longdesc)
    { _longdesc.assign(longdesc); }

    inline const Herds&
    Metadata::herds() const
    {
        if (not _herds) _herds = new Herds();
        return *_herds;
    }

    inline const Developers&
    Metadata::devs() const
    {
        if (not _devs) _devs = new Developers();
        return *_devs;
    }

    inline Herds&
    Metadata::herds()
    {
        if (not _herds) _herds = new Herds();
        return *_herds;
    }

    inline Developers&
    Metadata::devs()
    {
        if (not _devs) _devs = new Developers();
        return *_devs;
    }

    inline bool
    Metadata::operator< (const Metadata& that) const
    {
        return (_pkg < that._pkg);
    }

    inline bool
    Metadata::operator<=(const Metadata& that) const
    {
        return not (*this > that);
    }

    inline bool
    Metadata::operator> (const Metadata& that) const
    {
        return (that < *this);
    }

    inline bool
    Metadata::operator>=(const Metadata& that) const
    {
        return not (*this < that);
    }

    inline bool
    Metadata::operator==(const Metadata& that) const
    {
        return (_pkg == that._pkg);
    }

    inline bool
    Metadata::operator!=(const Metadata& that) const
    {
        return not (*this == that);
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_METADATA_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
