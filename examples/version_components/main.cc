#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <cstdlib>
#include <herdstat/portage/version.hh>

int
main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: version_components <ebuild>" << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		herdstat::portage::VersionComponents v(argv[1]);
		std::cout << "Version components for '"
			  << herdstat::util::basename(argv[1])
			  << "':" << std::endl
			  << "${P}   = " << v["P"] << std::endl
			  << "${PN}  = " << v["PN"] << std::endl
			  << "${PV}  = " << v["PV"] << std::endl
			  << "${PR}  = " << v["PR"] << std::endl
			  << "${PVR} = " << v["PVR"] << std::endl
			  << "${PF}  = " << v["PF"] << std::endl;
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
