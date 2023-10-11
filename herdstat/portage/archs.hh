/*
 * libherdstat -- herdstat/portage/archs.hh
 * $Id: archs.hh 190 2005-12-11 14:15:23Z ka0ttic $
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

#ifndef _HAVE_ARCHS_HH
#define _HAVE_ARCHS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file archs.hh
 * @brief Defines the Archs class.
 */

#include <herdstat/util/file.hh>

namespace herdstat {
namespace portage {

    /**
     * @class Archs archs.hh herdstat/portage/archs.hh
     * @brief Represents a list of portage-recognized architecture keywords
     * (those listed in $PORTDIR/profiles/arch.list).
     *
     * @section usage Usage
     *
     * Use the Archs class like you would any std::set<std::string>.
     */

    class Archs : public util::SetBase<std::string>,
                  protected util::BaseFile
    {
        public:
            /** Constructor.
             * @param portdir PORTDIR
             * @exception FileException
             */
            Archs(const std::string& portdir) throw (FileException);

            /// Destructor.
            virtual ~Archs() throw();

        protected:
            /// Read arch.list.
            virtual void do_read();
    };

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_ARCHS_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
