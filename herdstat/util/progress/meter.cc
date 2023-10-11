/*
 * libherdstat -- herdstat/util/progress/meter.cc
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/progress/meter.hh>

namespace herdstat {
namespace util {
/****************************************************************************/
ProgressMeter::ProgressMeter(const std::string& color) throw()
    : _cur(0), _step(0), _started(false), _outlen(0), _color(color)
{
}
/****************************************************************************/
ProgressMeter::~ProgressMeter() throw()
{
}
/****************************************************************************/
void
ProgressMeter::start(unsigned total, const std::string& title) throw()
{
    if (_started) return;
    _started = true;

    _step = 100.0 / total;

    if (not title.empty())
    {
        std::printf("%s ", title.c_str());
        _outlen = title.length()+1;
    }

    std::printf("%s", _color.c_str());
    this->do_start();
    std::printf("\033[00m");
    std::fflush(stdout);
}
/****************************************************************************/
void
ProgressMeter::stop()
{
    if (not _started)
        return;

    this->do_stop();

    for (unsigned i = 0 ; i < _outlen ; ++i)
        std::printf("\b \b");
    std::fflush(stdout);

    _cur = _step = _outlen = _started = 0;
}
/****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
