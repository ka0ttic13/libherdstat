/*
 * libherdstat -- herdstat/portage/project_xml.hh
 * $Id: project_xml.hh 205 2005-12-22 16:02:52Z ka0ttic $
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

#ifndef _HAVE_PROJECT_XML_HH
#define _HAVE_PROJECT_XML_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/project_xml.hh
 * @brief Defines the interface for Gentoo projectxml files.
 */

#include <set>
#include <herdstat/progressable.hh>
#include <herdstat/noncopyable.hh>
#include <herdstat/fetchable.hh>
#include <herdstat/parsable.hh>
#include <herdstat/xml/saxparser.hh>
#include <herdstat/portage/herd.hh>

namespace herdstat {
namespace portage {

    /**
     * @class ProjectXML project_xml.hh herdstat/portage/project_xml.hh
     * @brief Interface for Gentoo's projectxml-style XML files.
     *
     * @section usage Usage
     *
     * Usage of the ProjectXML class is identical to that of the
     * portage::HerdsXML class with the exception that the underlying data is
     * stored in a portage::Herd object (accessible via the devs() member).
     *
     * @see portage::HerdsXML documentation.
     */

    class ProjectXML : public Parsable,
                       public Progressable,
                       public Fetchable,
                       protected xml::SAXHandler,
                       private Noncopyable
    {
        public:
            /** Constructor.
             * @param path Path of projectxml file relative to
             * $cvsdir/gentoo/xml/htdocs.  If cvsdir is empty, we look in
             * $localstatedir and fetch it if necessary.
             * @param cvsdir Path to Gentoo cvs checkout directory.
             * @param force_fetch Whether or not to force fetching of the
             * projectxml file.
             * @exception FileException, xml::ParserException
             */
            ProjectXML(const std::string& path,
                       const std::string& cvsdir, bool force_fetch)
                throw (FileException, xml::ParserException);

            /// Destructor.
            virtual ~ProjectXML() throw();

            /// Get Herd.
            inline const Herd& devs() const;

        protected:
            /** Parse projectxml file.
             * @param path Path to projectxml file (defaults to empty).
             * @exception FileException, xml::ParserException
             */
            virtual void do_parse(const std::string& path = "")
                throw (FileException, xml::ParserException);

            /** Fetch projectxml file.
             * @param path Path to projectxml file (defaults to empty).
             * @exception FetchException
             */
            virtual void do_fetch(const std::string& path = "") const
                throw (FetchException);

            ///@{
            /// SAX2 Callbacks
            virtual bool start_element(const std::string& name,
                                       const attrs_type&  attrs);
            virtual bool end_element(const std::string& name);
            virtual bool do_text(const std::string& text);
            ///@}

        private:
            Herd _devs;
            const std::string& _cvsdir;
            const bool _force_fetch;
            bool in_sub, in_dev, in_task;
            std::string _cur_role;
            static const char * const _baseURL;
            static const char * const _baseLocal;
            /* for keeping track of what we've parsed already
             * to prevent infinite recursion. */
            static std::set<std::string> _parsed;
    };

    inline const Herd& ProjectXML::devs() const { return _devs; }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_PROJECT_XML.hh */

/* vim: set tw=80 sw=4 fdm=marker et : */
