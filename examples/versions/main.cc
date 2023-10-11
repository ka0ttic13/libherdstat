#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include <iterator>
#include <herdstat/portage/util.hh> /* for get_pkg_from_path() */
#include <herdstat/portage/version.hh>

int
main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: versions <pkgdir>" << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		herdstat::portage::Versions v(argv[1]);
		std::cout << "Sorted versions for "
			<< herdstat::portage::get_pkg_from_path(argv[1])
			<< ":" << std::endl << std::endl;
		std::transform(v.begin(), v.end(),
			std::ostream_iterator<std::string>(std::cout, "\n"),
			std::mem_fun_ref(&herdstat::portage::VersionString::str));
	}
	catch (const herdstat::BaseException& e)
	{
		std::cerr << "Oops!\n  * " << e.backtrace(":\n	* ")
		    << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/* vim: set tw=80 sw=8 ts=8 sts=8 fdm=marker noet : */
