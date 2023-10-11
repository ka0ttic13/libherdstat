#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <string>
#include <cstdlib>
#include <herdstat/fetcher/fetcher.hh>

int
main(int argc, char **argv)
{
	herdstat::FetcherOptions opts;
	std::string url, path;
	opts.set_verbose(true);

	if (argc == 3)
	{
		url.assign(argv[1]);
		path.assign(argv[2]);
	}
	else if (argc == 4)
	{
		opts.set_implementation(argv[1]);
		url.assign(argv[2]);
		path.assign(argv[3]);
	}
	else
	{
		std::cerr
		    << "usage: fetcher_options <implementation (default: wget)> <url> <path>"
		    << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		herdstat::Fetcher fetch(opts);
		fetch(url, path);
	}
	catch (const herdstat::FetchException& e)
	{
		std::cerr << "Failed to save '" << url << "' to '"
		    << path << "." << std::endl;
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
