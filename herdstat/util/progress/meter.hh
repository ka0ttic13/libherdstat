/*
 * libherdstat -- herdstat/util/progress/meter.hh
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

#ifndef _HAVE_PROGRESS_METER_HH
#define _HAVE_PROGRESS_METER_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/progress/meter.hh
 * @brief Provides the ProgressMeter abstract class definition.
 */

#include <string>
#include <cstdio>
#include <herdstat/defs.hh>

namespace herdstat {
namespace util {

    /**
     * @class ProgressMeter meter.hh herdstat/util/progress/meter.hh
     * @brief Provides the abstract interface for progress meters.
     *
     * @section example Example
     *
     * Below is a simple example of using the ProgressMeter interface:
     * 
     * @include progress/main.cc
     *
     * For examples of writing your own ProgressMeter implementation, take a
     * look at the code for the Spinner class or the PercentMeter class.
     */

    class ProgressMeter
    {
        public:
            /// Destructor.
            virtual ~ProgressMeter() throw();

            /** Start progress meter.
             * @param total Total number of items that will be processed.
             * @param title Title to display before the meter (defaults to "").
             */
            void start(unsigned total, const std::string& title = "") throw();

            /// Stop progress meter.
            void stop();

            ///@{
            /// Increment progress.
            inline bool operator++() throw();
            inline bool operator++(int) throw() { return operator++(); }
            ///@}

            /// Has this meter been started?
            inline bool started() const { return _started; }
            /// Get current progress.
            inline const float& cur() const { return _cur; }

        protected:
            /** Constructor.
             * @param color ASCII color sequence (defaults to "").
             */
            ProgressMeter(const std::string& color = "") throw();

            /// Append value to _outlen.
            inline void append_outlen(unsigned len) { _outlen += len; }

            /** Abstract interface for starting the meter, implemented by each
             * ProgressMeter derivative.
             */
            virtual void do_start() throw() = 0;

            /** Abstract interface for stopping the meter.  This has a default
             * implementation.
             */
            virtual void do_stop() throw() { }

            /** Abstract interface for incrementing the progress meter,
             * implemented by each ProgressMeter derivative.
             */
            virtual void do_increment(int cur) throw() = 0;

        private:
            float _cur;
            float _step;
            bool _started;
            unsigned _outlen;
            const std::string _color;
    };

    inline bool
    ProgressMeter::operator++() throw()
    {
        if (not _started)
            return false;

        _cur += _step;

        std::printf("%s", _color.c_str());
        this->do_increment(static_cast<int>(_cur));
        std::printf("\033[00m");

        std::fflush(stdout);
        return true;
    }

} // namespace util
} // namespace herdstat

#endif /* _HAVE_PROGRESS_METER_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
