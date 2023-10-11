/*
 * libherdstat -- herdstat/portage/herds_xml.hh
 * $Id: herds_xml.hh 169 2005-12-02 13:11:50Z ka0ttic $
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

#ifndef _HAVE_HERDS_XML_HH
#define _HAVE_HERDS_XML_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/herds_xml.hh
 * @brief Defines the interface to herds.xml.
 */

#include <algorithm>
#include <herdstat/fetcher/fetcher.hh>
#include <herdstat/portage/data_source.hh>
#include <herdstat/portage/herd.hh>

namespace herdstat {
namespace portage {

    /**
     * @class HerdsXML herds_xml.hh herdstat/portage/herds_xml.hh
     * @brief Interface for Gentoo's herds.xml.
     *
     * @section example Example
     *
     * Below is an example on using the HerdsXML class.  After parsing herds.xml
     * (either via the parse() member or via the constructor that takes a path),
     * you may get the underlying portage::Herds container via the herds()
     * member.
     *
     * @include herds.xml/main.cc
     */

    class HerdsXML : public DataSource
    {
        public:
            /// Default constructor.
            HerdsXML() throw();

            /** Constructor.
             * @param path Path to herds.xml.
             * @exception FileException, xml::ParserException
             */
            HerdsXML(const std::string& path)
                throw (FileException, xml::ParserException);

            /// Destructor.
            virtual ~HerdsXML() throw();

            /** Fill a Developer object with data we contain relevant to the
             * developer.  At the very least, the Developer's user name must
             * have been set prior to calling this function.
             * @param dev Reference to a Developer object.
             * @exception Exception
             */
            virtual void fill_developer(Developer& dev) const throw (Exception);

            /** Set Gentoo CVS checkout directory.  herds.xml as well as
             * projectxml files will be looked for relative to this path.
             * @param path Path.
             */
            inline void set_cvsdir(const std::string& path);

            /** Set forceful fetching of projectxml files when parsing
             * herds.xml.
             * @param force Boolean value.
             */
            inline void set_force_fetch(bool force);

            /// Implicit conversion to Herds::container_type
            inline operator Herds::container_type() const;

            /// Get herds found in herds.xml.
            inline const Herds& herds() const;
            /// Get herds found in herds.xml.
            inline Herds& herds();

            /* convienence */

            /// Get number of herds found in herds.xml.
            inline Herds::size_type size() const;
            /// Were no herds found in herds.xml?
            inline bool empty() const;

        protected:
            /** Parse herds.xml.
             * @param path Path to herds.xml (defaults to empty).
             * @exception FileException, xml::ParserException
             */
            virtual void do_parse(const std::string& path = "")
                throw (FileException, xml::ParserException);

            ///@{
            /// SAX2 Callbacks
            virtual bool start_element(const std::string &name,
                                       const attrs_type  &attrs);
            virtual bool end_element(const std::string &name);
            virtual bool do_text(const std::string &text);
            ///@}

        private:
            Herds _herds;
            std::string _cvsdir;
            bool _force_fetch;
            Fetcher _fetch; /* for fetching <maintainingproject> XML's */
            static const char * const _local_default;

            /* internal state variables */
            bool in_herd,
                 in_herd_name,
                 in_herd_email,
                 in_herd_desc,
                 in_maintainer,
                 in_maintainer_name,
                 in_maintainer_email,
                 in_maintainer_role,
                 in_maintaining_prj;

            Herds::iterator _cur_herd;
            Herd::iterator  _cur_dev;
    };

    inline HerdsXML::operator Herds::container_type() const { return _herds; }
    inline const Herds& HerdsXML::herds() const { return _herds; }
    inline Herds& HerdsXML::herds() { return _herds; }
    inline bool HerdsXML::empty() const { return _herds.empty(); }
    inline Herds::size_type HerdsXML::size() const { return _herds.size(); }
    inline void HerdsXML::set_cvsdir(const std::string& path) { _cvsdir.assign(path); }
    inline void HerdsXML::set_force_fetch(bool v) { _force_fetch = v; }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_HERDS_XML_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
