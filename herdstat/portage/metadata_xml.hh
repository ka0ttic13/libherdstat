/*
 * libherdstat -- herdstat/portage/metadata_xml.hh
 * $Id: metadata_xml.hh 205 2005-12-22 16:02:52Z ka0ttic $
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

#ifndef _HAVE_METADATA_XML_HH
#define _HAVE_METADATA_XML_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/metadata_xml.hh
 * @brief Defines the interface for metadata.xml files.
 */

#include <herdstat/parsable.hh>
#include <herdstat/progressable.hh>
#include <herdstat/xml/saxparser.hh>
#include <herdstat/portage/metadata.hh>

namespace herdstat {
namespace portage {

    /**
     * @class MetadataXML metadata_xml.hh herdstat/portage/metadata_xml.hh
     * @brief Interface to Gentoo's metadata.xml files.
     *
     * @section usage Usage
     *
     * Usage of the MetadataXML class is identical to that of the
     * portage::HerdsXML class with the exception that the underlying data is
     * stored in a portage::Metadata object (accessible via the data() member).
     *
     * @see portage::HerdsXML documentation.
     */

    class MetadataXML : public Parsable,
                        public Progressable,
                        protected xml::SAXHandler
    {
        public:
            /// Default constructor.
            MetadataXML() throw();

            /** Constructor.
             * @param path Path to metadata.xml.
             * @param pkg Package name for this metadata.xml (defaults to
             * empty).
             * @exception FileException, xml::ParserException
             */
            MetadataXML(const std::string& path, const std::string& pkg = "")
                throw (FileException, xml::ParserException);

            /// Destructor.
            virtual ~MetadataXML() throw();

            /// Get data associated with this metadata.xml.
            inline const Metadata& data() const;

            /* for convenience */
            /// Get long description.
            inline const std::string& longdesc() const;
            /// Get herds.
            inline const Herds& herds() const;
            /// Get developers.
            inline const Developers&  devs()  const;

        protected:
            /** Parse metadata.xml.
             * @param path Path to metadata.xml (defaults to empty).
             * @exception FileException, xml::ParserException
             */
            virtual void do_parse(const std::string& path = "")
                throw (FileException, xml::ParserException);

            virtual bool start_element(const std::string& name,
                                       const attrs_type& attrs);
            virtual bool end_element(const std::string& name);
            virtual bool do_text(const std::string& text);

        private:
            Metadata _data;

            bool in_herd,
                 in_maintainer,
                 in_email,
                 in_name,
                 in_desc,
                 in_longdesc,
                 in_en_longdesc;

            Developers::iterator _cur_dev;
            std::string _longdesc;
    };

    inline const Metadata& MetadataXML::data() const { return _data; }
    inline const Herds& MetadataXML::herds() const { return _data.herds(); }
    inline const Developers&  MetadataXML::devs()  const { return _data.devs(); }
    inline const std::string& MetadataXML::longdesc() const
    { return _data.longdesc(); }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_METADATA_XML.hh */

/* vim: set tw=80 sw=4 fdm=marker et : */
