/*
 * libherdstat -- herdstat/portage/userinfo_xml.hh
 * $Id: userinfo_xml.hh 169 2005-12-02 13:11:50Z ka0ttic $
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

#ifndef _HAVE_USERINFO_XML_HH
#define _HAVE_USERINFO_XML_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/userinfo_xml.hh
 * @brief Defines the interface to Gentoo's userinfo.xml.
 */

#include <herdstat/portage/data_source.hh>
#include <herdstat/portage/herd.hh>

namespace herdstat {
namespace portage {

    /**
     * @class UserinfoXML userinfo_xml.hh herdstat/portage/userinfo_xml.hh
     * @brief Represents Gentoo's userinfo.xml.
     *
     * @section usage Usage
     *
     * Usage of the UserinfoXML class is identical to that of the
     * portage::HerdsXML class with the exception that the underlying data is
     * stored in a portage::Developers object (accessible via the devs()
     * member).
     *
     * @see portage::HerdsXML documentation.
     */

    class UserinfoXML : public DataSource
    {
        public:
            /// Default constructor.
            UserinfoXML() throw();

            /** Constructor.
             * @param path Path to userinfo.xml.
             * @exception FileException, xml::ParserException
             */
            UserinfoXML(const std::string& path)
                throw (FileException, xml::ParserException);

            /// Destructor.
            virtual ~UserinfoXML() throw();

            /** Fill a Developer object with data we contain relevant to the
             * developer.  At the very least, the Developer's user name must
             * have been set prior to calling this function.
             * @param dev Reference to a Developer object.
             * @exception Exception
             */
            virtual void fill_developer(Developer& dev) const
                throw (Exception);

            /// Get developers.
            inline const Developers& devs() const;

            /* convenience */
            /// Get number of developers in userinfo.xml.
            inline Developers::size_type size() const;
            /// Were no developers in userinfo.xml?
            inline bool empty() const;

        protected:
            /** Parse userinfo.xml.
             * @param path Path to userinfo.xml (defaults to empty).
             * @exception FileException, xml::ParserException
             */
            virtual void do_parse(const std::string& path = "")
                throw (FileException, xml::ParserException);

            ///@{
            /// SAX2 Callbacks
            virtual bool start_element(const std::string& name,
                                       const attrs_type& attrs);
            virtual bool end_element(const std::string& name);
            virtual bool do_text(const std::string& text);
            ///@}

        private:
            Developers _devs;
            static const char * const _local_default;

            bool in_user,
                 in_firstname,
                 in_familyname,
                 in_pgpkey,
                 in_email,
                 in_joined,
                 in_birth,
                 in_roles,
                 in_status,
                 in_location;

            Developers::iterator _cur_dev;
    };

    inline const Developers& UserinfoXML::devs() const { return _devs; }
    inline Developers::size_type UserinfoXML::size() const { return _devs.size(); }
    inline bool UserinfoXML::empty() const { return _devs.empty(); }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_USERINFO_XML_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
