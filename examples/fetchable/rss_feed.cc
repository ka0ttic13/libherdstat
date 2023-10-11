#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <algorithm>
#include <functional>
#include <herdstat/util/file.hh>
#include <herdstat/util/string.hh>

#include "rss_feed.hh"

RSSFeed::RSSFeed(const std::string& url) throw()
    : herdstat::Fetchable(), herdstat::Parsable(), herdstat::xml::SAXHandler(),
      _url(url), _entries(),
      _desc(), _lang(), _creator(), in_main_title(false), in_main_desc(false),
      in_lang(false), in_creator(false), in_date(false), in_item(false),
      in_link(false), in_subject(false), in_body(false), in_desc(false),
      in_title(false), cur_entry()
{
}

RSSFeed::~RSSFeed() throw()
{
}

void
RSSFeed::do_fetch(const std::string& path) const
    throw (herdstat::FetchException)
{
	const herdstat::Fetcher& fetcher(this->fetcher());
	const std::string file(path.empty() ?
				herdstat::util::basename(_url) : path);
	fetcher(_url, file);
}

void
RSSFeed::do_parse(const std::string& path)
    throw (herdstat::FileException, herdstat::xml::ParserException)
{
	const std::string file(path.empty() ?
			herdstat::util::basename(_url) : path);

	if (not herdstat::util::is_file(file))
		throw herdstat::FileException(file);

	this->parse_file(file.c_str());
}

struct DisplayRSSFeedEntry
	: std::binary_function<RSSFeedEntry, std::ostream *, void>
{
	void operator()(const RSSFeedEntry& entry, std::ostream *stream) const
	{
		*stream << "Title: " << entry.title() << std::endl
		       << "Author: " << entry.creator() << std::endl
		       << "Subject: " << entry.subject() << std::endl
		       << "Body: " << entry.body() << std::endl << std::endl;
	}
};

void
RSSFeed::display(std::ostream& stream) const
{
	std::for_each(_entries.begin(), _entries.end(),
		std::bind2nd(DisplayRSSFeedEntry(), &stream));
}

bool
RSSFeed::start_element(const std::string& name, const attrs_type& attrs)
{
	/* ... */
	return true;
}

bool
RSSFeed::end_element(const std::string& name)
{
	/* ... */
	return true;
}

bool
RSSFeed::do_text(const std::string& str)
{
	/* ... */
	return true;
}

/* vim: set tw=80 sw=8 ts=8 sts=8 fdm=marker noet : */
