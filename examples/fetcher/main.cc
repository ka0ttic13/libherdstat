#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <cstdlib>
#include <herdstat/fetcher/fetcher.hh>

int
main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr
		    << "usage: fetcher <url> <path>"
		    << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		herdstat::Fetcher fetch;
		fetch(argv[1], argv[2]);
	}
	catch (const herdstat::FetchException& e)
	{
		std::cerr << "Failed to save '" << argv[1] << "' to '"
		    << argv[2] << "." << std::endl;
		return EXIT_FAILURE;
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
