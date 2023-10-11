#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iterator>

#include <herdstat/exceptions.hh>
#include <herdstat/util/vars.hh>

struct VarAndValue
{
	std::string operator()(const herdstat::util::Vars::value_type& v) const
	{ return (v.first + " = " + v.second); }
};

int
main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: vars_reader <path>" << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		herdstat::util::Vars vars(argv[1]);
		std::transform(vars.begin(), vars.end(),
			std::ostream_iterator<std::string>(std::cout, "\n"),
			VarAndValue());
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
