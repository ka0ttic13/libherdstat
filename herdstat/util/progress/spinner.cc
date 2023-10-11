/*
 * libherdstat -- herdstat/util/progress/twirl.cc
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

#include <herdstat/util/progress/spinner.hh>

namespace herdstat {
namespace util {
/*** static members *********************************************************/
const char * const Spinner::_sequence = "/-\\|";
/****************************************************************************/
Spinner::Spinner(const std::string& color) throw()
    : ProgressMeter(color), _seqp(_sequence)
{
}
/****************************************************************************/
Spinner::~Spinner() throw()
{
    this->stop();
}
/****************************************************************************/
void
Spinner::do_start() throw()
{
    std::printf("%c", *_seqp++);
}
/****************************************************************************/
void
Spinner::do_stop() throw()
{
    /* output length is constant */
    append_outlen(1);
}
/****************************************************************************/
void
Spinner::do_increment(int cur LIBHERDSTAT_UNUSED) throw()
{
    /* reset to beginning of sequence */
    if (not *_seqp)
        _seqp = _sequence;

    std::printf("\b%c", *_seqp++);
}
/****************************************************************************/
} // namespace util
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
