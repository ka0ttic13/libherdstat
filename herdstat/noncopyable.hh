/*
 * libherdstat -- herdstat/noncopyable.hh
 * $Id: noncopyable.hh 155 2005-11-27 13:37:27Z ka0ttic $
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

#ifndef _HAVE_NONCOPYABLE_HH
#define _HAVE_NONCOPYABLE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/noncopyable.hh
 * @brief Defines the Noncopyable base class.
 */

namespace herdstat {

    /**
     * @class Noncopyable noncopyable.hh herdstat/noncopyable.hh
     * @brief Base class for noncopyable things.  Declares copy constructor and
     * copy assignment operator private.
     *
     * @section usage Usage
     *
     * Simple inherit (privately) from the Noncopyable class.  Any code
     * attempting to copy or assign (operator=) should fail to compile.
     */

    class Noncopyable
    {
        protected:
            Noncopyable() throw() { }
            virtual ~Noncopyable() { }

        private:
            Noncopyable(const Noncopyable&) throw();
            Noncopyable& operator= (const Noncopyable&) throw();
    };

} // namespace herdstat

#endif /* _HAVE_NONCOPYABLE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
