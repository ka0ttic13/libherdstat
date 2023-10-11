#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <string>
#include <herdstat/fetcher/fetcherimp.hh>
#include <herdstat/fetcher/fetcher.hh>

class MyFetcherImp : public herdstat::FetcherImp
{
	public:
		MyFetcherImp(const herdstat::FetcherOptions& opts) throw();
		virtual ~MyFetcherImp() throw();
		virtual bool fetch(const std::string& url,
			           const std::string& path) const
			throw (herdstat::FileException);
};

MyFetcherImp::MyFetcherImp(const herdstat::FetcherOptions& opts) throw()
	: herdstat::FetcherImp(opts)
{
}

MyFetcherImp::~MyFetcherImp() throw()
{
}

bool
MyFetcherImp::fetch(const std::string& url, const std::string& path) const
	throw (herdstat::FileException)
{
	/* a real FetcherImp derivative would
	 * obviously actually fetch the file.
	 */

	std::cout << "Pretending to fetch '"
		<< url << "' and save it to '"
		<< path << "'." << std::endl;
	return true;
}

int
main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "usage: fetcherimp <url> <path>" << std::endl;
		return EXIT_FAILURE;
	}

	const std::string url(argv[1]);
	const std::string path(argv[2]);

	try
	{
		herdstat::FetcherOptions opts;
		opts.set_implementation("my_fetcher");

		herdstat::FetcherImpMap imps(opts);
		imps.insert<MyFetcherImp>("my_fetcher");

		herdstat::Fetcher fetch(imps, opts);
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
