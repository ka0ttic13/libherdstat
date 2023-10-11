/*
 * libherdstat -- herdstat/portage/ebuild.hh
 * $Id: ebuild.hh 155 2005-11-27 13:37:27Z ka0ttic $
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

#ifndef _HAVE_EBUILD_HH
#define _HAVE_EBUILD_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/ebuild.hh
 * @brief Defines the ebuild class.
 */

#include <map>
#include <herdstat/util/vars.hh>
#include <herdstat/portage/version.hh>

namespace herdstat {
namespace portage {

    /**
     * @class Ebuild ebuild.hh herdstat/portage/ebuild.hh
     * @brief Represents ebuild variables.
     * This is really identical to util::Vars, except it defines
     * do_set_defaults() and inserts variables that should be
     * pre-existing (${PN}, ${P}, etc).
     *
     * @section example Example
     *
     * The example for util::Vars applies equally for the Ebuild class.
     *
     * @see util::Vars
     */

    class Ebuild : public util::Vars
    {
        public:
            /// Default constructor.
            Ebuild() throw();

            /** Constructor.
             * @param path Path to ebuild.
             * @exception FileException
             */
            Ebuild(const std::string &path) throw (FileException);

            /// Destructor.
            virtual ~Ebuild() throw();

            /// Assign a new path.
            void assign(const std::string& path);

        protected:
            /// Set default variables.
            virtual void do_set_defaults();
            /// Action to perform on each line read
//            virtual void do_perform_action_on(const std::string& line);

        private:
//            typedef std::map<std::string, ebuild * > eclass_map;
            /// set of eclasses we've parsed; used for preventing recursion
//            static eclass_map _eclasses;
            VersionComponents _vmap;
    };

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_EBUILD_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
