/*
 * libherdstat -- herdstat/util/vars.hh
 * $Id: vars.hh 189 2005-12-11 13:32:32Z ka0ttic $
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

#ifndef HAVE_VARS_HH
#define HAVE_VARS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/vars.hh
 * @brief Defines the vars class.
 */

#include <map>
#include <utility>
#include <herdstat/util/file.hh>

namespace herdstat {
namespace util {

    /**
     * @class Vars vars.hh herdstat/util/vars.hh
     * @brief Represents a file with variables in the form of VARIABLE=VALUE,
     * stored in key,value pairs.  Does extremely simple variable substitution.
     *
     * @section example Example
     *
     * Below is an example showing a simple usage of the Vars class.  It simply
     * parses the specified file showing each variable's value (assuming the
     * file you specify contains variable assignments).
     *
     * @include vars/main.cc
     */

    class Vars : public BaseFile,
                 public MapBase<std::string, std::string>
    {
        public:
            /// Default constructor.
            Vars() throw();

            /** Constructor.
             * @param path Path.
             * @exception FileException
             */
            Vars(const std::string &path) throw (FileException);

            /// Destructor.
            virtual ~Vars() throw();

            /** Dump keys/values to specified stream.
             * @param s Output stream.
             */
            virtual void dump(std::ostream &s) const;

        protected:
            /// Strip leading/trailing whitespace
            void strip_ws(std::string& str);

            /// Derivatives may override this to set any defaults
            virtual void do_set_defaults() { }
            virtual void do_read();

            /// Derivatives may override this to define something that must
            /// be done for each line of the file.
            virtual void do_perform_action_on(const std::string& line LIBHERDSTAT_UNUSED) { }

        private:
            void set_defaults();
            void perform_action_on(const std::string& line);

            /** Perform elementary variable substitution.
             * @param v Variable.
             */
            void subst(std::string &v);

            /// subst() recursion depth (safeguard).
            unsigned short _depth;
    };

} // namespace util
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 fdm=marker et : */
