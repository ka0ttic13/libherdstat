/*
 * libherdstat -- herdstat/portage/license.hh
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

#ifndef _HAVE_LICENSE_HH
#define _HAVE_LICENSE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/license.hh
 * @brief Defines the License class.
 */

#include <string>

namespace herdstat {
namespace portage {

    /**
     * @class License license.hh herdstat/portage/license.hh
     * @brief Represents a LICENSE string.
     *
     * @section overview Overview
     *
     * Every ebuild declares a LICENSE variable (except maybe those that inherit
     * an eclass that declares the variable).  In most cases a single license is
     * declared and nothing special is needed in order to parse it.  However,
     * there are some ebuilds that use weird syntax like:
     *
@verbatim
LICENSE="|| ( GPL-2 BSD )"
@endverbatim
     *
     * Using the License class, you can easily turn that into a space-delimited
     * license string (available via the str() member).
     *
     * @section usage Usage
     *
     * Simply construct a License instance with a license string as found in an
     * ebuild.  The easiest way of doing this is by using the portage::Ebuild
     * class and selecting the LICENSE variable via
     * portage::Ebuild::operator[]().
     *
     * By passing 'true' to the License constructor's 'validate' argument, the
     * License class will throw a portage::QAException if it encounters a
     * license that does not exist in ${PORTDIR}/licenses.
     *
     * @section example Example
     *
     * Below is a simple example of using the License class:
     *
@code
herdstat::portage::Ebuild ebuild("/path/to/ebuild");
herdstat::portage::License license(ebuild["LICENSE"], true);
std::cout << "License(s): " << license.str() << std::endl;
@endcode
     */

    class License
    {
        public:
            /** Default constructor.
             * @param validate Bail if an invalid license is found?
             */
            License(bool validate = false) throw();

            /** Constructor.
             * @param str License string as found in an ebuild.
             * @param validate Bail if an invalid license is found?
             * @exception QAException
             */
            License(const std::string& str, bool validate = false)
                throw (QAException);

            /// Destructor.
            ~License() throw();

            /** Assign new license string.
             * @param str License string as found in an ebuild.
             * @param validate Bail if an invalid license is found?
             * @exception QAException
             */
            inline void assign(const std::string& str,
                               bool validate = false) throw (QAException);

            /// Get license string.
            inline const std::string& str() const throw();

            /// Implicit conversion to std::string.
            inline operator const std::string&() const throw();

        private:
            /** Parse license string.
             * @exception QAException
             */
            void parse() throw (QAException);

            bool _validate;
            std::string _license;
    };

    inline void
    License::assign(const std::string& str, bool validate) throw (QAException)
    {
        _validate = validate;
        _license = str;
        this->parse();
    }

    inline const std::string&
    License::str() const throw()
    {
        return _license;
    }

    inline License::operator
    const std::string&() const throw()
    {
        return _license;
    }

} // namespace portage
} // namespace herdstat

#endif /* _HAVE_LICENSE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
