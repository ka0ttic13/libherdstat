/*
 * libherdstat -- herdstat/portage/devaway_xml.hh
 * $Id: devaway_xml.hh 169 2005-12-02 13:11:50Z ka0ttic $
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

#ifndef _HAVE_DevawayXML_HH
#define _HAVE_DevawayXML_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/devaway_xml.hh
 * @brief Defines the interface for Gentoo's devaway.xml.
 */

#include <herdstat/portage/data_source.hh>
#include <herdstat/portage/developer.hh>

namespace herdstat {
namespace portage {

    /**
     * @class DevawayXML devaway_xml.hh herdstat/portage/devaway_xml.hh
     * @brief Represents Gentoo's devaway.xml.
     *
     * @section usage Usage
     *
     * Usage of the DevawayXML class is identical to that of the
     * portage::HerdsXML class with the exception that the underlying data is
     * stored in a portage::Developers object (accessible via the devs()
     * member).
     *
     * @see portage::HerdsXML documentation.
     */

    class DevawayXML : public DataSource
    {
        public:
            /// Default constructor.
            DevawayXML() throw();

            /** Constructor.
             * @param path Path to devaway.xml.
             * @exception FileException, xml::ParserException
             */
            DevawayXML(const std::string& path)
                throw (FileException, xml::ParserException);
            
            /// Destructor.
            virtual ~DevawayXML() throw();

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
            /// Get developers.
            inline Developers& devs();

            /// Get vector of all usernames as well as all email addy's.
            const std::vector<std::string> keys() const;

        protected:
            /** Parse devaway.xml.
             * @param path Path to devaway.xml (defaults to empty).
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
            bool in_devaway, in_dev, in_reason;
            Developers::iterator _cur_dev;
    };

    inline Developers& DevawayXML::devs() { return _devs; }
    inline const Developers& DevawayXML::devs() const { return _devs; }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_DEVAWAY_XML_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
