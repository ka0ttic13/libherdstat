/*
 * libherdstat -- herdstat/portage/package_list.cc
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

#include <herdstat/portage/package_list.hh>

namespace herdstat {
namespace portage {
/****************************************************************************/
PackageList::PackageList(bool fill, util::ProgressMeter *progress)
    : _portdir(GlobalConfig().portdir()),
      _overlays(GlobalConfig().overlays()),
      _filled(false)
{
    if (fill)
        this->fill(progress);
}
/****************************************************************************/
PackageList::PackageList(const std::string& portdir,
                         const std::vector<std::string>& overlays,
                         bool fill, util::ProgressMeter *progress)
    : _portdir(portdir), _overlays(overlays), _filled(false)
{
    if (fill)
        this->fill(progress);
}
/****************************************************************************/
PackageList::~PackageList() throw()
{
}
/****************************************************************************/
void
PackageList::fill(util::ProgressMeter *progress)
{
    BacktraceContext c("herdstat::portage::PackageList::fill()");

    if (_filled)
        return;

    std::string path;
    const Categories& categories(GlobalConfig().categories());
    Categories::const_iterator ci, cend;

    /* we can only use the estimate here */
    this->reserve(PKGLIST_RESERVE);

    /* search portdir */
    for (ci = categories.begin(), cend = categories.end() ; ci != cend ; ++ci)
    {
        path.assign(_portdir+"/"+(*ci));
        if (not util::is_dir(path))
            continue;

        /* add category itself */
        this->push_back(Package(*ci, _portdir));

        /* for each pkg in category, insert "cat/pkg" into container */
        const util::Directory cat(path);
//        std::transform(cat.begin(), cat.end(),
//            std::back_inserter(this->container()),
//            std::bind2nd(NewPackage(), _portdir));

        util::Directory::const_iterator i;
        for (i = cat.begin() ; i != cat.end() ; ++i)
        {
            if (progress)
                ++*progress;

            this->push_back(Package(get_pkg_from_path(*i), _portdir));
        }
    }

    /* search overlays, if any */
    if (not _overlays.empty())
    {
        std::vector<std::string>::const_iterator oi, oend = _overlays.end();
        for (ci = categories.begin() ; ci != cend ; ++ci)
        {
            for (oi = _overlays.begin() ; oi != oend ; ++oi)
            {
                path.assign(*oi+"/"+(*ci));
                if (not util::is_dir(path))
                    continue;

                this->push_back(Package(*ci, *oi));

                /* for each pkg in category, insert "cat/pkg" */
                const util::Directory cat(path);
//                std::transform(cat.begin(), cat.end(),
//                    std::back_inserter(this->container()),
//                    std::bind2nd(NewPackage(), *oi));
                
                util::Directory::const_iterator i;
                for (i = cat.begin() ; i != cat.end() ; ++i)
                {
                    if (progress)
                        ++*progress;

                    this->push_back(Package(get_pkg_from_path(*i), *oi));
                }
            }
        }
    }

    std::sort(this->begin(), this->end());

    /* container may contain duplicates if overlays were searched */
    if (not _overlays.empty())
        this->erase(std::unique(this->begin(), this->end()), this->end());

    /* trim unused space */
    if (this->capacity() > (this->size() + 10))
        container_type(this->container()).swap(this->container());

    _filled = true;
}
/****************************************************************************/
} // namespace portage
} // namespace herdstat

/* vim: set tw=80 sw=4 fdm=marker et : */
