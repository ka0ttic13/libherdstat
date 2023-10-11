/*
 * libherdstat -- herdstat/portage/config.hh
 * $Id: config.hh 157 2005-11-28 12:41:22Z ka0ttic $
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

#ifndef HAVE_PORTAGE_CONFIG_HH
#define HAVE_PORTAGE_CONFIG_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/portage/config.hh
 * @brief Defines the config class, the interface to Portage configuration.
 */

#include <vector>
#include <string>

#include <herdstat/noncopyable.hh>
#include <herdstat/exceptions.hh>
#include <herdstat/util/vars.hh>
#include <herdstat/portage/archs.hh>
#include <herdstat/portage/categories.hh>

namespace herdstat {
namespace portage {

    /**
     * @class Config config.hh herdstat/portage/config.hh
     * @brief Represents the current portage configuration.
     *
     * @section overview Overview
     *
     * The Config class gets the current portage configuration by first reading
     * /etc/make.globals (to get the default values) and then reading
     * /etc/make.conf.  Any variables set in the latter will override any set in
     * the former.
     *
     * @section usage Usage
     *
     * The Config class is a singleton, meaning it is guaranteed that there will
     * never be more than one instance at any one time.  We do this by making
     * the constructors private and declaring the function GlobalConfig() a
     * friend of the Config class.  GlobalConfig() creates a local static
     * instance of the Config class and then returns a const reference to it.
     * Using the GlobalConfig() function is the <em>only</em> way to access a
     * Config object.  This prevents the overhead of reading
     * make.conf/make.globals (and other files that it reads) more than
     * necessary.
     *
     * As stated in the previous section, the Config class stores variables and
     * their values as found in make.conf/make.globals.  The values to these
     * variables can be retrieved via the operator[]() member.
     *
     * @section example Example
     *
     * Below is a simple example of using the Config class:
     *
@code
const portage::Config& config(portage::GlobalConfig());
const std::string distdir(config["DISTDIR"]);
@endcode
     *
     */

    class Config : private Noncopyable
    {
        public:
            /// Get PORTDIR.
            inline const std::string& portdir() const;
            /// Get PORTDIR_OVERLAY
            inline const std::vector<std::string>& overlays() const;

            /** Get value of a portage configuration variable (anything in
             * make.conf/make.globals is valid).
             * @returns a copy of the value mapped to the specified variable
             * or an empty string if the value doesn't exist.
             */
            inline std::string operator[] (const std::string& var) const throw();

            /** Get categories.
             * @exception FileException
             */
            inline const Categories& categories() const throw (FileException);
            
            /** Get arch keywords.
             * @exception FileException
             */
            inline const Archs& archs() const throw (FileException);

        private:
            /// Only GlobalConfig() can instantiate this class.
            friend const Config& GlobalConfig() throw (FileException);

            /// Constructor.
            Config() throw (FileException);
            /// Destructor.
            ~Config() throw();

            util::Vars _vars;
            std::string _portdir;
            std::vector<std::string> _overlays;
            mutable Categories *_cats;
            mutable Archs *_archs;
    };

    inline const std::string& Config::portdir() const { return _portdir; }
    inline const std::vector<std::string>& Config::overlays() const
    { return _overlays; }

    inline const Categories&
    Config::categories() const throw (FileException)
    {
        if (not _cats) _cats = new Categories(_portdir);
        return *_cats;
    }

    inline const Archs&
    Config::archs() const throw (FileException)
    {
        if (not _archs) _archs = new Archs(_portdir);
        return *_archs;
    }

    inline std::string
    Config::operator[] (const std::string& var) const throw()
    {
        util::Vars::const_iterator i = _vars.find(var);
        return (i == _vars.end() ? std::string() : i->second);
    }

    /**
     * Sole access point to the Config class.
     * @exception FileException
     * @returns const reference to a local static instance of portage::config.
     * @see Config for an example of using the returned Config instance.
     */

    inline const Config&
    GlobalConfig() throw (FileException)
    {
        static Config c;
        return c;
    }

} // namespace portage
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 fdm=marker et : */
