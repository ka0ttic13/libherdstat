/*
 * libherdstat -- herdstat/portage/categories.hh
 * $Id: categories.hh 157 2005-11-28 12:41:22Z ka0ttic $
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

#ifndef _HAVE_CATEGORIES_HH
#define _HAVE_CATEGORIES_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <string>
#include <herdstat/util/file.hh>
#include <herdstat/util/container_base.hh>

/**
 * @file herdstat/portage/categories.hh
 * @brief Defines the Categories class.
 */

namespace herdstat {
namespace portage {

    /**
     * @class Categories categories.hh herdstat/portage/categories.hh
     * @brief Represents a container of package categories.  Contents are only
     * validated if told to do so.  Otherwise, you'll want to make sure an
     * element is valid before using it.
     *
     * @section overview Overview
     *
     * The Categories class contains a unique list of portage package
     * categories.  It reads the categories file located in the specified
     * PORTDIR (PORTDIR/profiles/categories) as well as the user-defined
     * categories file in /etc/portage/categories.
     *
     * If 'true' is passed to the Categories constructor's 'validate' argument,
     * a portage::QAException will be thrown if an invalid (eg it doesn't
     * exist) category is encountered.
     *
     * @section usage Usage
     *
     * Use the Categories class as you would any std::set<std::string>.
     */

    class Categories : public util::SetBase<std::string>,
                       protected util::BaseFile
    {
        public:
            /** Constructor.
             * @param portdir PORTDIR to look in.
             * @param validate Bail if an invalid category is found?
             * @exception FileException
             */
            Categories(const std::string& portdir,
                       bool validate = false) throw (FileException);

            /// Destructor.
            virtual ~Categories() throw();

        protected:
            virtual void do_read();

        private:
            std::string _portdir;
            const bool _validate;
    };

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_CATEGORIES_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
