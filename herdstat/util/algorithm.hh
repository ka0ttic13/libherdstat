/*
 * libherdstat -- herdstat/util/algorithm.hh
 * $Id: algorithm.hh 157 2005-11-28 12:41:22Z ka0ttic $
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

#ifndef _HAVE_UTIL_ALGORITHM_HH
#define _HAVE_UTIL_ALGORITHM_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file herdstat/util/algorithm.hh
 * @brief Defines the general purpose algorithms.
 */

#include <iterator>

namespace herdstat {
namespace util {

    /**
     * For each element in the range [first,last) for which UnaryPred
     * returns true, assign the result of UnaryOp to the given output iterator.
     * Like std::transform, but only "transforms" if UnaryPred returns true.
     * For times where std::replace_copy_if is not appropriate.
     *
     * @section example Example
     *
     * Below is a simple example of using transform_if:
     *
@code
std::vector<int> v1, v2;
v1.push_back(1);
v1.push_back(10);
v1.push_back(199);
v1.push_back(666);
herdstat::util::transform_if(v1.begin(), v1.end(),
    std::back_inserter(v2),
    std::bind2nd(std::greater<int>(), 10),
    std::bind2nd(std::plus<int>(), 5));
@endcode
     * The above code snippet can be read as "for each element in v1 that is
     * greater than 10, add 5 to it and insert it into v2".
     */

    template <typename InputIterator, typename OutputIterator,
              typename UnaryOp, typename UnaryPred>
    OutputIterator
    transform_if(InputIterator first, InputIterator last,
                 OutputIterator result, UnaryPred pred, UnaryOp op)
    {
        for ( ; first != last ; ++first)
        {
            if (pred(*first))
                *result++ = op(*first);
        }

        return result;
    }

    /**
     * For each element in the range [first,last) for which UnaryPred returns
     * true, copy to the given output iterator.  Like std::copy but only copies
     * if UnaryPred returns true.
     *
     * @section example Example
     *
     * Below is a simple example of using copy_if:
@code
std::vector<std::string> paths, files;
paths.push_back("/path/to/some/file");
paths.push_back("/path/to/some/other/file");
paths.push_back("/path/to/some/directory");
herdstat::util::copy_if(paths.begin(), paths.end(),
    std::back_inserter(files), herdstat::util::IsFile());
@endcode
     * The above code snippet can be read as "for each element in the paths
     * vector, if it's a valid file, insert it into the files vector".
     */

    template <typename InputIterator, typename OutputIterator,
              typename UnaryPred>
    OutputIterator
    copy_if(InputIterator first, InputIterator last,
            OutputIterator result, UnaryPred pred)
    {
        for ( ; first != last ; ++first )
        {
            if (pred(*first))
                *result++ = *first;
        }

        return result;
    }

    /**
     * Determine whether all elements in the range [first,last) are equal.
     */

    template <typename InputIterator>
    bool
    all_equal(InputIterator first, InputIterator last)
    {
        typename std::iterator_traits<InputIterator>::value_type v(*first);
        const typename std::iterator_traits<InputIterator>::difference_type size =
            std::distance(first, last);
        return (size == std::count(first, last, v));
    }

    /**
     * Determine whether the return values of UnaryOp run on each in the range
     * [first,last) are equal.
     */

    template <typename InputIterator, typename UnaryOp>
    bool
    all_equal(InputIterator first, InputIterator last, UnaryOp op)
    {
        typename std::iterator_traits<InputIterator>::value_type v(op(*first++));

        while (first != last)
        {
	    if (v != op(*first++))
	        return false;
        }

        return true;
    }

} // namespace util
} // namespace herdstat

#endif /* _HAVE_UTIL_ALGORITHM_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
