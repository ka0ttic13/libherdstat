#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <cstdlib>
#include <herdstat/xml/init.hh>
#include "rss_feed.hh"

int
main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: feed_reader <url>" << std::endl;
		return EXIT_FAILURE;
	}

	/// initialize underlying libxml2 things
	herdstat::xml::GlobalInit();

	try
	{
		RSSFeed feed(argv[1]);
		feed.fetch();
		feed.parse();
		feed.display(std::cout);
	}
	catch (const herdstat::FetchException& e)
	{
		std::cerr << "Failed to fetch RSS feed: "
			<< argv[1] << std::endl;
		return EXIT_FAILURE;
	}
	catch (const herdstat::xml::ParserException& e)
	{
		std::cerr << "Error parsing RSS feed "
			<< e.file() << ": " << e.error() << std::endl;
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
