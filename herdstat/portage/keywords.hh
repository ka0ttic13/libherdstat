/*
 * libherdstat -- herdstat/portage/keywords.hh
 * $Id: keywords.hh 194 2005-12-12 12:57:29Z ka0ttic $
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

#ifndef _HAVE_KEYWORDS_HH
#define _HAVE_KEYWORDS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file keywords.hh
 * @brief Defines the Keyword/Keywords classes.
 */

#include <string>
#include <herdstat/util/container_base.hh>
#include <herdstat/portage/exceptions.hh>
#include <herdstat/portage/ebuild.hh>
#include <herdstat/portage/archs.hh>
#include <herdstat/portage/version.hh>

namespace herdstat {
namespace portage {

    // {{{ Keyword
    /**
     * @class Keyword keywords.hh herdstat/portage/keywords.hh
     * @brief Represents a single architecture keyword.
     *
     * @section usage Usage
     *
     * Simply instantiate with a keyword string (eg "~mips").  You can get that
     * same string later using the str() member.  You can get the architecture
     * using the arch() member.  You can get the mask character with the mask()
     * member.  If there is no mask character (meaning it's a stable keyword),
     * the mask() member returns the nul byte ('\\0').  For convenience, the
     * member functions is_stable(), is_testing(), and is_masked() are provided.
     * These functios simply test the mask character for the respective mask
     * type.  For sorting purposes, comparison operators such as operator<()
     * are provided.
     */

    class Keyword
    {
        public:
            /** Constructor.
             * @param kw keyword string.
             * @exception InvalidKeywordMask, InvalidArch
             */
            Keyword(const std::string& kw)
                throw (InvalidKeywordMask, InvalidArch);

            /// Get mask character (or nul byte if empty).
            char mask() const { return _mask; }
            /// Get architecture.
            const std::string& arch() const { return _arch; }
            /// Get keyword string.
            const std::string str() const
            { return (std::string(1, _mask)+_arch); }

            /** Is this Keyword less that that Keyword?
             * @param that const reference to Keyword
             * @returns Boolean value.
             */
            inline bool operator< (const Keyword& that) const throw();

            /** Is this Keyword greater than that Keyword?
             * @param that const reference to Keyword
             * @returns Boolean value
             */
            bool operator> (const Keyword& that) const throw()
            { return (that < *this); }

            /** Is this Keyword equal to that Keyword?
             * @param that const reference to Keyword
             * @returns Boolean value
             */
            bool operator==(const Keyword& that) const throw()
            { return ((_mask == that._mask) and (_arch == that._arch)); }

            /** Is this Keyword not equal to that Keyword?
             * @param that const reference to Keyword
             * @returns Boolean value
             */
            bool operator!=(const Keyword& that) const throw()
            { return (*this != that); }

            /// Is this a masked keyword?
            bool is_masked() const throw() { return _mask == '-'; }
            /// Is this a testing keyword?
            bool is_testing() const throw() { return _mask == '~'; }
            /// Is this a stable keyword?
            bool is_stable() const throw() { return _mask.empty(); }

        private:
            // {{{ Keyword::maskc
            /**
             * @class maskc
             * @brief Keyword mask character ('~' for example).
             */
            class maskc
            {
                public:
                    /// Default constructor.
                    maskc() throw();

                    /** Assignment operator.
                     * @param c mask character.
                     * @exception InvalidKeywordMask
                     */
                    maskc& operator= (const char c) throw (InvalidKeywordMask);
                    
                    /// Implicit conversion to char
                    operator char() const { return _c; }

                    /// Do we not hold a mask character?
                    bool empty() const { return (_c == '\0'); }

                    /** Is this maskc less than that maskc?
                     * @param that const reference to maskc
                     * @returns Boolean value
                     */
                    bool operator< (const maskc& that) const throw();

                    /** Is this maskc greater than that maskc?
                     * @param that const reference to maskc
                     * @returns Boolean value
                     */
                    bool operator> (const maskc& that) const throw()
                    { return (that < *this); }

                    /** Is this maskc equal to that maskc?
                     * @param const reference to maskc
                     * @returns Boolean value
                     */
                    bool operator==(const maskc& that) const throw()
                    { return (_c == that._c); }
                    
                    /** Is this maskc not equal to that maskc?
                     * @param const reference to maskc
                     * @returns Boolean value
                     */
                    bool operator!=(const maskc& that) const throw()
                    { return (*this != that); }

                    ///@{
                    /// Compare this with a character.
                    bool operator< (const char c) const throw()
                    { return (_c < c); }
                    bool operator> (const char c) const throw()
                    { return (_c > c); }
                    bool operator==(const char c) const throw()
                    { return (_c == c); }
                    bool operator!=(const char c) const throw()
                    { return (_c != c); }
                    ///@}
                
                private:
                    char _c;
            };
            // }}}

            /** Parse keyword.
             * @exception InvalidKeywordMask
             */
            void parse(const std::string& kw) throw (InvalidKeywordMask);

            std::string _arch;
            maskc _mask;
            const Archs& _valid_archs;
            static const char * const _valid_masks;
    };

    inline bool
    Keyword::operator< (const Keyword& that) const throw()
    {
        return ((_mask == that._mask) ?
                (_arch < that._arch) : (_mask < that._mask));
    }
    // }}}

    // {{{ Keywords
    /**
     * @class Keywords keywords.hh herdstat/portage/keywords.hh
     * @brief Keyword container.
     *
     * @section overview Overview
     *
     * Every ebuild defines a KEYWORDS variable that contains a list of
     * architecture "keywords" that the package is known to work/not work with.
     *
     * The Keywords class was designed to hold all keywords from a given ebuild,
     * however it can also be used in a more generic sense as a general
     * portage::Keyword container.
     *
     * The Keywords class uses portage::Keyword::operator<() to sort keywords
     * from least to greatest.  A masked Keyword ('-') is considered less than a
     * testing Keyword ('~'), which is considered less than a stable keyword (no
     * mask character).  Keywords with the same mask character are then sorted
     * by std::string::operator<().
     *
     * @section usage Usage
     *
     * The Keywords class has the same public interface as a std::set.
     *
     * You can use the all_* member functions to determine if all the keywords
     * have the respective mask type (eg all_masked() returns true if all
     * keywords are masked with the '-' character).
     *
     * You can use the str() member function to get a pretty colored keywords
     * string.
     */

    class Keywords : public util::SetBase<Keyword>
    {
        public:
            /// Default constructor.
            Keywords() throw();

            /** Constructor.
             * @param path Path to ebuild.
             * @exception Exception
             */
            Keywords(const std::string& path) throw (Exception);

            /** Constructor.
             * @param e Pre-existing ebuild instance.
             * @exception Exception
             */
            Keywords(const Ebuild& e) throw (Exception);

            /// Destructor.
            virtual ~Keywords() throw();

            /** Assign new ebuild path.
             * @param path Path to ebuild
             * @exception Exception
             */
            void assign(const std::string& path) throw (Exception);

            /** Assign new ebuild.
             * @param e Pre-existing ebuild instance
             * @exception Exception
             */
            void assign(const Ebuild& e) throw (Exception);

            /// Get formatted keywords string.
            inline const std::string& str() const throw();

            /// Get path to ebuild associated with these keywords.
            inline const std::string& path() const throw();

            /// Are all keywords masked?
            inline bool all_masked() const throw();
            /// Are all keywords testing?
            inline bool all_testing() const throw();
            /// Are all keywords stable?
            inline bool all_stable() const throw();

        private:
            void fill() throw (Exception);
            /// prepare keywords string
            void format() throw();

            Ebuild _ebuild;
            std::string _str;
    };

    inline const std::string& Keywords::str() const throw() { return _str; }
    inline const std::string& Keywords::path() const throw() { return _ebuild.path(); }

    inline bool
    Keywords::all_masked() const throw()
    {
        const difference_type size(this->size());
        return (std::count_if(this->begin(), this->end(),
                    std::mem_fun_ref(&Keyword::is_masked)) == size);
    }

    inline bool
    Keywords::all_testing() const throw()
    {
        const difference_type size(this->size());
        return (std::count_if(this->begin(), this->end(),
                    std::mem_fun_ref(&Keyword::is_testing)) == size);
    }

    inline bool
    Keywords::all_stable() const throw()
    {
        const difference_type size(this->size());
        return (std::count_if(this->begin(), this->end(),
                    std::mem_fun_ref(&Keyword::is_stable)) == size);
    }
    // }}}

    // {{{ KeywordsMap
    /**
     * @class KeywordsMap keywords.hh herdstat/portage/keywords.hh
     * @brief Maps VersionString objects to Keywords objects.
     */

    class KeywordsMap : public VersionsMap<Keywords>
    {
        public:
            /** Constructor.  Instantiate/insert a new VersionString/Keywords
             * object for each ebuild in the given package directory.
             * @param pkgdir Package directory.
             * @exception Exception
             */
            KeywordsMap(const std::string& pkgdir) throw (Exception);

            /// Destructor.
            virtual ~KeywordsMap() throw();

            /** Get "least" pair (as determined by std::less<VersionString>).
             * @pre The instance this member is invoked upon must not be
             * empty().
             * @returns const reference to "least" pair.
             * @exception Exception.
             */
            inline const value_type& front() const throw (Exception);

            /** Get "greatest" pair (as determined by std::less<VersionString>).
             * @pre The instance this member is invoked upon must not be
             * empty().
             * @returns const reference to "greatest" pair.
             * @exception Exception.
             */
            inline const value_type& back() const throw (Exception);
    };

    inline const KeywordsMap::value_type&
    KeywordsMap::front() const throw (Exception)
    {
        if (this->empty())
            throw Exception("KeywordsMap::front() called on an empty KeywordsMap instance.");

        return *(this->begin());
    }

    inline const KeywordsMap::value_type&
    KeywordsMap::back() const throw (Exception)
    {
        if (this->empty())
            throw Exception("KeywordsMap::back() called on an empty KeywordsMap instance.");

        const_iterator i = this->end();
        return *(--i);
    }
    // }}}

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_KEYWORDS_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
