#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
#include <iterator>

#include <herdstat/util/regex.hh>
#include <herdstat/portage/package_list.hh>
#include <herdstat/portage/package_finder.hh>

int
main(int argc, char **argv)
{
	if ((argc < 2 or argc > 3) or
	    (argc == 2 and std::strcmp(argv[1], "-r") == 0) or
	    (argc == 3 and std::strcmp(argv[1], "-r") != 0))
	{
		std::cerr << "usage: package_finder [-r] <criteria>" << std::endl;
		std::cerr << "  -r  Treat <criteria> as a regular expression."
			<< std::endl;
		return EXIT_FAILURE;
	}

	const bool regex = (argc == 3);
	const char * const criteria = (regex ? argv[2] : argv[1]);

	try
	{
		std::cout << "Performing search for '" << criteria << "'..."
			<< std::endl;

		// get list of all packages
		herdstat::portage::PackageList pkgs;
		// use that list for searching
		herdstat::portage::PackageFinder find(pkgs);

		// get reference to search results
		const std::vector<herdstat::portage::Package>& results(find.results());

		// perform search
		if (regex)
			find(herdstat::util::Regex(criteria));
		else
			find(criteria);

		// display search results
		std::cout << std::endl
			<< "Search results(" << results.size() << "):"
			<< std::endl;
		std::transform(results.begin(), results.end(),
			std::ostream_iterator<std::string>(std::cout, "\n"),
			std::mem_fun_ref(&herdstat::portage::Package::full));
	}
	catch (const herdstat::portage::NonExistentPkg& e)
	{
		std::cerr << e.what() << std::endl;
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
