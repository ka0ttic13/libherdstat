#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <herdstat/exceptions.hh>
#include <herdstat/util/functional.hh>
#include <herdstat/util/progress/spinner.hh>
#include <herdstat/util/progress/percent.hh>
#include <herdstat/util/progress/ellipse.hh>
#include <herdstat/util/progress/dots.hh>
#include <unistd.h>

int
main(int argc, char **argv)
{
	std::string type("percent");

	if (argc == 2)
		type.assign(argv[1]);
	else if (argc != 1)
	{
		std::cerr
		    << "usage: progress <type>"
		    << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		std::map<std::string, herdstat::util::ProgressMeter*> pmap;
		pmap["percent"] = new herdstat::util::PercentMeter();
		pmap["spinner"] = new herdstat::util::Spinner();
		pmap["ellipse"] = new herdstat::util::EllipseMeter();
		pmap["dots"]    = new herdstat::util::DotsMeter();

		herdstat::util::ProgressMeter *progress = pmap[type];
		if (not progress)
			throw herdstat::Exception("Unknown ProgressMeter type '"+type+"'.");

		progress->start(1000, "Some operation");

		for (size_t i = 0 ; i < 1000 ; ++i)
		{
			++*progress;

			/* obviously in a real example we'd actually do
			 * something */
			sleep(1);
		}

		std::for_each(pmap.begin(), pmap.end(),
			herdstat::util::compose_f_gx(
				herdstat::util::DeleteAndNullify<herdstat::util::ProgressMeter>(),
				herdstat::util::Second<std::map<std::string, herdstat::util::ProgressMeter*>::value_type>()));
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
