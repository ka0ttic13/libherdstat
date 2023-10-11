/*
 * libherdstat -- herdstat/xml/saxparser.cc
 * $Id: saxparser.cc 169 2005-12-02 13:11:50Z ka0ttic $
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <herdstat/util/string.hh>
#include <herdstat/xml/saxparser.hh>

namespace herdstat {
namespace xml {
/****************************************************************************/
SAXHandler::~SAXHandler()
{
}
/****************************************************************************/
bool
SAXHandler::text(const std::string& str)
{
    if (not util::is_all_whitespace(str))
        return do_text(str);

    return true;
}
/****************************************************************************/
SAXParser::SAXParser(SAXHandler *handler) throw()
    : _handler(handler)
{
}
/****************************************************************************/
SAXParser::~SAXParser() throw()
{
}
/****************************************************************************/
void
SAXParser::parse(const std::string &path) throw (ParserException)
{
    BacktraceContext c("xml::saxparser::parse("+path+")");

    if (not this->_handler->parse_file(path.c_str()))
        throw ParserException(path, this->_handler->get_error_message());
}
/****************************************************************************/
} // namespace xml
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
