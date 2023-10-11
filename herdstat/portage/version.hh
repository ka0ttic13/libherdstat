/*
 * libherdstat -- herdstat/portage/version.hh
 * $Id: version.hh 194 2005-12-12 12:57:29Z ka0ttic $
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

#ifndef HAVE_PORTAGE_VERSION_HH
#define HAVE_PORTAGE_VERSION_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/version.hh
 * @brief Defines version-related classes (version sorting, version string
 * container, etc).
 */

#include <string>
#include <set>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <cassert>

#include <herdstat/util/container_base.hh>
#include <herdstat/util/functional.hh>
#include <herdstat/util/file.hh>

namespace herdstat {
namespace portage {

    // {{{ VersionComponents
    /**
     * @class VersionComponents version.hh herdstat/portage/version.hh
     * @brief Version component (${P}, ${PN}, etc) map.
     *
     * @section overview Overview
     *
     * For each ebuild, portage defines some preset variables based on the
     * ebuild's file name.  For a complete list of these variables, see the
     * ebuild(5) manual page.  The VersionComponents class maps these variables
     * names to their respective values for the given ebuild.
     *
     * @section usage Usage
     *
     * Instantiate VersionComponents with the path to an ebuild (or use the
     * assign() member) and then access the variables with operator[]().  You
     * can also use the iterators to iterate over the elements if you desire.
     *
     * @section example Example
     *
     * Below is a simple example of using the VersionComponents class:
     *
     * @include version_components/main.cc
     */

    class VersionComponents
    {
        public:
            typedef std::map<std::string, std::string> container_type;
            typedef container_type::iterator iterator;
            typedef container_type::const_iterator const_iterator;
            typedef container_type::size_type size_type;
            typedef container_type::value_type value_type;
            typedef container_type::key_type key_type;
            typedef container_type::mapped_type mapped_type;

            /// Default constructor.
            VersionComponents() throw();

            /** Constructor.
             * @param path Path to ebuild.
             */
            VersionComponents(const std::string& path) throw();

            /// Destructor.
            ~VersionComponents() throw();

            /** Assign new path.
             * @param path Path to ebuild.
             */
            void assign(const std::string& path) throw();

            /** Get value mapped to given version component.
             * @param key version component (P, PN, etc).
             * @returns const reference to value mapped to @a key.
             */
            inline const mapped_type& operator[](const key_type& key) const throw();

            ///@{
            /// container_type subset
            const_iterator begin() const { return _vmap.begin(); }
            const_iterator end() const { return _vmap.end(); }
            size_type size() const { return _vmap.size(); }
            bool empty() const { return _vmap.empty(); }
            const_iterator find(const key_type& key) const
            { return _vmap.find(key); }
            ///@}

            /// Get version string.
            inline const std::string& version() const throw();

        private:
            /// Parse version string and insert components into map.
            void parse() throw();

            std::string _verstr;
            mutable container_type _vmap;
    };

    inline const VersionComponents::mapped_type&
    VersionComponents::operator[](const key_type& key) const throw()
    {
        return _vmap[key];
    }

    inline const std::string&
    VersionComponents::version() const throw()
    {
        return _verstr;
    }
    // }}}

    // {{{ VersionString
    /**
     * @class VersionString version.hh herdstat/portage/version.hh
     * @brief Represents a version string corresponding to the given ebuild.
     *
     * @section overview Overview
     *
     * A VersionString instance by itself is not all that useful.  It doesn't do
     * any version parsing (it uses VersionComponents for that).  It's main
     * purpose is version sorting via the comparison operators (operator<(),
     * etc).  These comparison operators do real portage-style version sorting.
     *
     * @section example Example
     *
     * Below is a simple example of using the VersionString class:
     *
@code
herdstat::portage::VersionString v1("/path/to/foo-1.0.ebuild");
herdstat::portage::VersionString v2("/path/to/foo-1.2.ebuild");
if (v1 < v2)
{
    ...
}
const herdstat::portage::VersionComponents& vc(v1.components());
...
std::cout << v1.str() << std::endl;
@endcode
     *
     * @see Versions for a more common VersionString usage example.
     */

    class VersionString
    {
        public:
            /// Default constructor.
            VersionString() throw();

            /** Constructor.
             * @param path Path to ebuild.
             */
            VersionString(const std::string &path) throw();

            /// Copy constructor.
            VersionString(const VersionString& that) throw();

            /// Copy assignment operator.
            VersionString& operator=(const VersionString& that) throw();

            /// Get version string.
            std::string str() const throw();

            /** Assign a new path.
             * @param path Path to ebuild.
             */
            void assign(const std::string& path) throw();

            /// Implicit conversion to std::string.
            operator std::string() const throw() { return this->str(); }

            /** Get version string (minus the suffix).
             * @returns String object.
             */
            const std::string& version() const throw() { return _version(); }

            /** Get path to ebuild for this version.
             * @returns String object.
             */
            const std::string& ebuild() const throw() { return _ebuild; }

            /** Get version component map for this version string.
             * @returns Reference to version_map object.
             */
            const VersionComponents& components() const throw() { return _v; }

            ///@{
            /// Compare this VersionString against that VersionString.
            bool operator< (const VersionString& that) const throw();
            inline bool operator<=(const VersionString& that) const throw()
            { return not (*this > that); }
            inline bool operator> (const VersionString& that) const throw()
            { return (that < *this); }
            inline bool operator>=(const VersionString& that) const throw()
            { return not (*this < that); }
            inline bool operator==(const VersionString& that) const throw();
            inline bool operator!=(const VersionString& that) const throw()
            { return not (*this == that); }
            ///@}

        private:
            /**
             * @class suffix
             * @brief Represents a version suffix (_alpha, _beta, etc).
             */

            class suffix
            {
                public:
                    /// Default constructor.
                    suffix() throw();

                    /** Constructor.
                     * @param pvr PVR string object (version+revision).
                     */
                    suffix(const std::string& pvr) throw();

                    /** Assign a new suffix.
                     * @param pvr PVR string object (version+revision).
                     */
                    void assign(const std::string& pvr) throw()
                    { this->parse(pvr); }

                    /** Get suffix string.
                     * @returns String object.
                     */
                    const std::string& str() const throw() { return _suffix; }

                    /** Get suffix version string.
                     * @returns String object.
                     */
                    const std::string& version() const throw()
                    { return _suffix_ver; }

                    ///@{
                    /// Compare this suffix against that suffix.
                    bool operator< (const suffix& that) const throw();
                    bool operator<=(const suffix& that) const throw()
                    { return not (*this > that); }
                    bool operator> (const suffix& that) const throw()
                    { return (that < *this); }
                    bool operator>=(const suffix& that) const throw()
                    { return not (*this < that); }
                    bool operator== (const suffix& that) const throw();
                    bool operator!= (const suffix& that) const throw()
                    { return not (*this == that); }
                    ///@}

                private:
                    /// Parse ${PVR}
                    void parse(const std::string &pvr) const throw();

                    /// Suffix std::string.
                    mutable std::string _suffix;
                    /// Suffix version std::string.
                    mutable std::string _suffix_ver;
            };

            /**
             * @class nosuffix
             * @brief Represents package version minus the suffix.
             */

            class nosuffix
            {
                public:
                    nosuffix() throw();

                    /** Constructor.
                     * @param pv PV string object.
                     */
                    nosuffix(const std::string& pv) throw();

                    /** Assign a new $PV.
                     * @param pv PV string object.
                     */
                    void assign(const std::string& pv) throw()
                    { this->parse(pv); }

                    /** Get version string minus suffix.
                     * @returns String object.
                     */
                    const std::string& operator() () const throw()
                    { return _version; }

                    ///@{
                    /// Compare this nosuffix against that nosuffix.
                    bool operator< (const nosuffix& that) const throw();
                    bool operator> (const nosuffix& that) const throw()
                    { return (that < *this); }
                    bool operator== (const nosuffix& that) const throw();
                    bool operator!= (const nosuffix& that) const throw()
                    { return not (*this == that); }
                    ///@}

                private:
                    /// Parse ${PV}.
                    void parse(const std::string& pv) const throw();

                    /// Version string (minus suffix).
                    mutable std::string _version;
                    /// Any extra non-digit characters.
                    mutable std::string _extra;
            };

            /// Absolute path to ebuild.
            mutable std::string _ebuild;
            /// Version components map.
            mutable VersionComponents _v;
            /// Reference to actual version string
            mutable std::string _verstr;
            /// Our version suffix.
            mutable suffix _suffix;
            /// Our version minus suffix.
            mutable nosuffix _version;
    };

    inline bool
    VersionString::operator==(const VersionString& that) const throw()
    {
        return ( (_version == that._version) and
                 (_suffix  == that._suffix)  and
                 (_v["PR"] == that._v["PR"]) );
    }
    // }}}

    // {{{ Versions
    /** 
     * @class Versions version.hh herdstat/portage/version.hh
     * @brief Sorted VersionString container.
     *
     * @section overview Overview
     *
     * Generally used for all versions of a single package.
     *
     * @section example Example
     *
     * Below is a simple example of using the Versions class to show properly
     * sorted versions of the given package:
     *
     * @include versions/main.cc
     */

    class Versions : public util::SetBase<VersionString>
    {
        public:
            /// Default constructor.
            Versions() throw();

            /** Constructor.  Instantiate VersionString objects for each
             * ebuild existing in the specified package directory.
             * @param path Path to package directory.
             */
            Versions(const std::string &path) throw();

            /** Constructor.  Instantiate VersionString objects for each
             * ebuild existing in each element (package directories).
             * @param v Vector of package directory paths.
             */
            Versions(const std::vector<std::string>& v) throw();

            /// Destructor.
            virtual ~Versions() throw();

            /** Get "least" VersionString (as determined by
             * std::less<VersionString>).
             * @pre The instance this function is invoked upon must not be
             * empty().
             * @returns const reference to "least" element.
             * @exception Exception.
             */
            inline const VersionString& front() const throw (Exception);

            /** Get "greatest" VersionString (as determined by
             * std::less<VersionString>).
             * @pre The instance this function is invoked upon must not be
             * empty().
             * @returns const reference to "greatest" element.
             * @exception Exception.
             */
            inline const VersionString& back() const throw (Exception);

            //@{
            /** Find version string using ebuild matching path.
             * @param path Ebuild path.
             * @returns iterator to first match or end() if no match.
             */
            inline iterator find(const std::string& path) throw();
            inline const_iterator find(const std::string& path) const throw();
            //@}

            /** Insert given VersionString.
             * @param v const reference to VersionString.
             * @returns True if insertion was successful.
             */
            inline bool insert(const VersionString& v) throw();

            /** Instantiate and insert a VersionString object with the
             * specified path.
             * @param p Path.
             * @returns True if insertion was successful.
             */
            inline bool insert(const std::string& p) throw();

            /** Assign a new package directory clearing any previously
             * contained VersionString instances.
             * @param p Path to package directory.
             */
            void assign(const std::string& p) throw();

            /** Append a new package directory.
             * @param p Path to package directory.
             */
            void append(const std::string& p) throw();
    };

    inline Versions::iterator
    Versions::find(const std::string& p) throw()
    {
        return this->find(VersionString(p));
    }

    inline Versions::const_iterator
    Versions::find(const std::string& p) const throw()
    {
        return this->find(VersionString(p));
    }

    inline bool
    Versions::insert(const std::string& path) throw()
    {
        return util::SetBase<VersionString>::insert(VersionString(path)).second;
    }

    inline bool
    Versions::insert(const VersionString& v) throw()
    {
        return util::SetBase<VersionString>::insert(v).second;
    }

    inline const VersionString&
    Versions::front() const throw (Exception)
    {
        if (this->empty())
            throw Exception("Versions::front() called on an empty Versions instance.");

        return *(this->begin());
    }

    inline const VersionString&
    Versions::back() const throw (Exception)
    {
        if (this->empty())
            throw Exception("Versions::back() called on an empty Versions instance.");

        const_iterator i = this->end();
        return *(--i);
    }
    // }}}

    // {{{ VersionsMap
    /**
     * @class VersionsMap version.hh herdstat/portage/version.hh
     * @brief Template class for mapping VersionString objects to objects of
     * type T.
     * @see KeywordsMap for an example of using the VersionsMap class template.
     */

    template <typename T>
    class VersionsMap : public util::MapBase<VersionString, T>
    {
        public:
            virtual ~VersionsMap() throw() { }
    };
    // }}}

    // {{{ NewVersionStringPair
    /**
     * @struct NewVersionStringPair version.hh herdstat/portage/version.hh
     * @brief Function object for creating a new std::pair<VersionString, T>.
     * Implicit interface assumes T has a constructor that takes a std::string.
     */

    template <typename T>
    struct NewVersionStringPair
        : std::unary_function<std::string, std::pair<VersionString, T> >
    {
        std::pair<VersionString, T>
        operator()(const std::string& path) const
        {
            return std::make_pair(VersionString(path), T(path));
        }
    };
    // }}}

} // namespace portage
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 fdm=marker et : */
