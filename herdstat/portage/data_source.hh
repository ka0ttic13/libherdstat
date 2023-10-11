/*
 * libherdstat -- herdstat/portage/data_source.hh
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

#ifndef _HAVE_PORTAGE_DATA_SOURCE_HH
#define _HAVE_PORTAGE_DATA_SOURCE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/data_source.hh
 * @brief Defines the DataSource abstract interface.
 */

#include <herdstat/parsable.hh>
#include <herdstat/progressable.hh>
#include <herdstat/noncopyable.hh>
#include <herdstat/util/progress/meter.hh>
#include <herdstat/xml/saxparser.hh>

namespace herdstat {
namespace portage {

    class Developer;

    /**
     * @class DataSource
     * @brief Abstract base class for Gentoo-related XML files that provide
     * information (eg herds.xml).
     */

    class DataSource : public Parsable,
                       public Progressable,
                       protected xml::SAXHandler,
                       private Noncopyable
    {
        public:
            /** Fill a Developer object with data this source provides that is
             * relevant to the specified developer.
             * @param dev reference to a Developer object.
             * @pre The @a dev parameter must at least have the developer's
             * user name set.
             * @exception Exception
             */
            virtual void fill_developer(Developer& dev) const
                throw (Exception) = 0;

        protected:
            /// Default constructor.
            DataSource() throw() { }

            /** Constructor.
             * @param path Path to XML file.
             */
            DataSource(const std::string& path) throw()
                : Parsable(path) { }

            /// Destructor.
            virtual ~DataSource() throw() { }
    };

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_PORTAGE_DATA_SOURCE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
