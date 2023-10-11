#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <string>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include <iterator>

#include <herdstat/cachable.hh>
#include <herdstat/util/file.hh>
#include <herdstat/util/glob.hh>
#include <herdstat/util/algorithm.hh>
#include <herdstat/util/functional.hh>
#include <herdstat/util/container_base.hh>

class MetadataList : public herdstat::Cachable,
		     public herdstat::util::VectorBase<std::string>
{
	public:
		MetadataList(const std::string& path,
			     const std::string& portdir);

		virtual ~MetadataList();

		virtual bool valid() const;
		virtual void fill();
		virtual void load();
		virtual void dump();

	private:
		const std::string _portdir;
};

MetadataList::MetadataList(const std::string& path,
			   const std::string& portdir)
	: herdstat::Cachable(path), _portdir(portdir)
{
}

MetadataList::~MetadataList()
{
}

bool
MetadataList::valid() const
{
	/* It's valid if it exists.  Realistically, most caches expire, so more
	 * often than not you'd have some kind of check here to see if the cache
	 * is expired, returning false if so */
	return herdstat::util::is_file(this->path());
}

void
MetadataList::fill()
{
	herdstat::util::Glob glob;
	glob(_portdir+"/*/metadata.xml");
	glob(_portdir+"/*/*/metadata.xml");
	this->insert(this->end(),
		glob.results().begin(),
		glob.results().end());
}

void
MetadataList::load()
{
	std::ifstream stream(this->path().c_str());
	if (not stream)
		throw herdstat::FileException(this->path());

	this->insert(this->end(),
		std::istream_iterator<std::string>(stream),
		std::istream_iterator<std::string>());
}

void
MetadataList::dump()
{
	std::ofstream stream(this->path().c_str());
	if (not stream)
		throw herdstat::FileException(this->path());

	std::sort(this->begin(), this->end());
	std::copy(this->begin(), this->end(),
		std::ostream_iterator<std::string>(stream, "\n"));
}

int
main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: metadata_list <portdir>" << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		MetadataList m("metadata_list.txt", argv[1]);	

		/* if cache is valid, load it */
		if (m.valid())
		{
			std::cout << "metadata_list.txt exists... loading it."
				<< std::endl;

			/* load cache */
			m.load();

			std::cout << "Successfully loaded metadata_list.txt."
				<< std::endl;
			std::cout << "Number of metadata.xml's in " << argv[1]
				<< ": " << m.size() << std::endl;
		}
		/* otherwise, fill the cache with data and dump it to disk */
		else
		{
			std::cout << "Generating metadata.xml list "
				<< "(may take a few minutes)..."
				<< std::endl;

			/* fill container */
			m.fill();
			
			std::cout << "Number of metadata.xml's in "
				<< argv[1] << ": " << m.size() << std::endl;
			
			/* dump container contents to disk */
			m.dump();
			
			std::cout << "Dumped list to metadata_list.txt." << std::endl;
		}
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
