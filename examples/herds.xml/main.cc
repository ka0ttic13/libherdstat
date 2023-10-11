#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <cstdlib>
#include <herdstat/util/string.hh>
#include <herdstat/xml/init.hh>
#include <herdstat/portage/herds_xml.hh>

int
main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: herds.xml <path>" << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		/// Initialize underlying libxml2 things.
		herdstat::xml::GlobalInit();

		herdstat::portage::HerdsXML herds_xml(argv[1]);
		const herdstat::portage::Herds& herds(herds_xml.herds());

		/// Display all herd names.
		std::cout << "All herd names: " << std::endl;
		std::transform(herds.begin(), herds.end(),
			std::ostream_iterator<std::string>(std::cout, " "),
			std::mem_fun_ref(&herdstat::portage::Herd::name));
		std::cout << std::endl << std::endl;

		/// fill the developer object with info herds.xml knows about
		herdstat::portage::Developer dev("ka0ttic");
		herds_xml.fill_developer(dev);

		std::cout << "Info for developer 'ka0ttic':" << std::endl
			  << "Name:  " << dev.name() << std::endl
			  << "Email: " << dev.email() << std::endl
			  << "Herds: "
			  << herdstat::util::join(dev.herds().begin(),
						  dev.herds().end(), ",")
			  << std::endl;
	}
	catch (const herdstat::xml::ParserException& e)
	{
		std::cerr << "Error parsing " << e.file() << ": "
		    << e.error() << std::endl;
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
