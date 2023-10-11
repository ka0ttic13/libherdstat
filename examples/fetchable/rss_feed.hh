#ifndef _HAVE_FETCHABLE_RSS_FEED_HH
#define _HAVE_FETCHABLE_RSS_FEED_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <string>
#include <vector>
#include <ostream>
#include <herdstat/fetchable.hh>
#include <herdstat/parsable.hh>
#include <herdstat/xml/saxparser.hh>

/**
 * @class RSSFeedEntry
 * @brief Represents a single entry in a RSS feed.
 */

class RSSFeedEntry
{
	public:
		void set_title(const std::string& title) { _title = title; }
		void set_link(const std::string& link) { _link = link; }
		void set_date(const std::string& date) { _date = date; }
		void set_creator(const std::string& creator) { _creator = creator; }
		void set_subject(const std::string& subject) { _subject = subject; }
		void set_body(const std::string& body) { _body = body; }

		const std::string& title() const { return _title; }
		const std::string& link() const { return _link; }
		const std::string& date() const { return _date; }
		const std::string& creator() const { return _creator; }
		const std::string& subject() const { return _subject; }
		const std::string& body() const { return _body; }

	private:
		std::string _title;
		std::string _link;
		std::string _date;
		std::string _creator;
		std::string _subject;
		std::string _body;
};

/**
 * @class RSSFeed
 * @brief Represents a RSS XML Feed.
 */

class RSSFeed : public herdstat::Fetchable,
                public herdstat::Parsable,
                protected herdstat::xml::SAXHandler
{
	public:
		RSSFeed(const std::string& url) throw();
		virtual ~RSSFeed() throw();

                /// Display feed.
		void display(std::ostream& stream) const;

		/// Get feed URL.
		const std::string& url() const { return _url; }
		/// Get feed description.
		const std::string& desc() const { return _desc; }
		/// Get feed language.
		const std::string& lang() const { return _lang; }
		/// Get feed creator.
		const std::string& creator() const { return _creator; }
		/// Get feed entries.
		const std::vector<RSSFeedEntry>& entries() const { return _entries; }

	protected:
                /// Fetch feed.
		virtual void do_fetch(const std::string& path = "") const
			throw (herdstat::FetchException);

                /// Parse feed.
		virtual void do_parse(const std::string& path = "")
			throw (herdstat::FileException,
                               herdstat::xml::ParserException);

                ///@{
		/// SAX2 callbacks
		virtual bool start_element(const std::string&, const attrs_type&);
		virtual bool end_element(const std::string&);
		virtual bool do_text(const std::string&);
	        ///@}

	private:
		const std::string _url;
		std::vector<RSSFeedEntry> _entries;
		std::string _desc;
		std::string _lang;
		std::string _creator;
		bool in_main_title, in_main_desc, in_lang, in_creator, in_date,
		     in_item, in_link, in_subject, in_body, in_desc, in_title;
		std::vector<RSSFeedEntry>::iterator cur_entry;
};

#endif /* _HAVE_FETCHABLE_RSS_FEED_HH */

/* vim: set tw=80 sw=8 ts=8 sts=8 fdm=marker noet : */
