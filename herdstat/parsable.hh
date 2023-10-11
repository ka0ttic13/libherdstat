/*
 * libherdstat -- src/parsable.hh
 * $Id: parsable.hh 154 2005-11-26 13:37:02Z ka0ttic $
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

#ifndef HAVE_PARSABLE_HH
#define HAVE_PARSABLE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/parsable.hh
 * @brief Defines the parsable abstract interface.
 */

#include <string>
#include <herdstat/util/timer.hh>
#include <herdstat/xml/exceptions.hh>

namespace herdstat {

    /**
     * @class Parsable parsable.hh herdstat/parsable.hh
     * @brief Abstract base class for parsable things.
     *
     * The Parsable base class is used to describe objects as being
     * "parsable".  Derivatives define their own do_parse virtual function that
     * calls the parse_file() member function.
     *
     * @section example Example
     *
     * Below is an example application that uses the Parsable base class to
     * describe an RSS feed as being parsable.  The RSSFeed class defines the
     * do_parse virtual to parse the RSS feed.
     *
     * @include fetchable/rss_feed.hh
     *
     * Defines the RSSFeed and RSSFeedEntry interfaces.
     *
     * @include fetchable/rss_feed.cc
     *
     * Defines the RSSFeed and RSSFeedEntry implementations.
     *
     * @include fetchable/main.cc
     *
     * Defines main().
     */

    class Parsable
    {
        public:
            typedef util::Timer timer_type;

            /// Default constructor.
            Parsable() throw() : _parsed(false), _path(), _timer() { }

            /** Constructor.
             * @param path Path of parsable file.
             */
            Parsable(const std::string& path) throw()
                : _parsed(false), _path(path), _timer() { }
            
            /// Destructor.
            virtual ~Parsable() { }

            /** Parse specified file.
             * @param path Path of parsable file (defaults to empty).
             * @exception FileException, xml::ParserException
             */
            inline void parse(const std::string& path = "")
                throw (FileException, xml::ParserException);

            /// Have we already parsed?
            bool parsed() const { return _parsed; }
            /// Get path of parsable file.
            const std::string &path() const { return _path; }
            /// Get elapsed time it took to parse.
            timer_type::size_type elapsed() const { return _timer.elapsed(); }

        protected:
            /** Do the actual parsing.
             * @exception FileException, xml::ParserException
             */
            virtual void do_parse(const std::string& path = "")
                throw (FileException, xml::ParserException) = 0;

            /** Set path of parsable file.
             * @param path Path of parsable file.
             */
            void set_path(const std::string &path) const { _path.assign(path); }

            /// Get reference to timer object.
            timer_type& timer() { return _timer; }

        private:
            bool _parsed;
            mutable std::string _path;
            timer_type  _timer;
    };

    inline void
    Parsable::parse(const std::string& path)
        throw (FileException, xml::ParserException)
    {
        if (_parsed) return;
        do_parse(path);
        _parsed = true;
    }

} // namespace herdstat

#endif /* HAVE_PARSABLE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
