/*
 * libherdstat -- herdstat/util/timer.hh
 * $Id: timer.hh 168 2005-12-02 12:44:31Z ka0ttic $
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

#ifndef HAVE_TIMER_HH
#define HAVE_TIMER_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/timer.hh
 * @brief Defines the Timer class.
 */

#include <sys/time.h>

namespace herdstat {
namespace util {

    /**
     * @class Timer timer.hh herdstat/util/timer.hh
     * @brief Represents a timer.
     *
     * @section example Example
     *
     * Below is a simple example of using the Timer class:
     *
@code
herdstat::util::Timer timer;
timer.start();
...
timer.stop();
std::cout << "Took " << timer.elapsed()
    << "ms to perform something." << std::endl;
@endcode
     *
     */

    class Timer
    {
        public:
            typedef long size_type;

            /// Default constructor.
            Timer() throw();

            /// Destructor.
            ~Timer() throw();

            /// Start timer.
            void start() throw();

            /// Stop timer.
	    void stop() throw();

            /** Is the timer running?
             * @returns A boolean value.
             */
            inline bool is_running() const;

            /** Get elapsed time (in milliseconds).
             * @returns An long integer value.
             */
            inline const size_type& elapsed() const;

            /// Reset elapsed value.
            inline void reset();

        private:
	    timeval _begin, _end;
	    size_type _elapsed;
            bool _running;
    };

    inline bool
    Timer::is_running() const
    {
        return _running;
    }

    inline const Timer::size_type&
    Timer::elapsed() const
    {
        return _elapsed;
    }

    inline void
    Timer::reset()
    {
        _elapsed = 0;
    }

} // namespace util
} // namespace herdstat

#endif

/* vim: set tw=80 sw=4 fdm=marker et : */
