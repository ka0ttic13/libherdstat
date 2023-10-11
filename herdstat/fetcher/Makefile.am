# $Id: Makefile.am 158 2005-11-29 13:19:55Z ka0ttic $

include $(top_builddir)/Makefile.am.common

cc_sources = \
	exceptions.cc \
	options.cc \
	wgetfetcher.cc \
	curlfetcher.cc \
	impmap.cc \
	fetcher.cc

hh_sources = \
	exceptions.hh \
	options.hh \
	fetcherimp.hh \
	wgetfetcher.hh \
	curlfetcher.hh \
	impmap.hh \
	fetcher.hh

noinst_LTLIBRARIES = libfetcher.la
libfetcher_la_SOURCES = $(hh_sources) $(cc_sources)
libfetcher_la_LIBADD  = @CURL_LIBS@

library_includedir=$(includedir)/$(PACKAGE)-$(VERSION_MAJOR).$(VERSION_MINOR)/herdstat/fetcher
library_include_HEADERS = $(hh_sources)

MAINTAINERCLEANFILES = Makefile.in *~ *.loT

srchtml: $(foreach f, $(libfetcher_la_SOURCES), $(f).html)

%.cc.html: %.cc
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat/fetcher || \
		mkdir $(top_srcdir)/html/herdstat/fetcher
	@source-highlight -c ../../src.css -s cpp -f html -t4 -n -i $? -o \
		$(top_srcdir)/html/herdstat/fetcher/$@

%.hh.html: %.hh
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat/fetcher || \
		mkdir $(top_srcdir)/html/herdstat/fetcher
	@source-highlight -c ../../src.css -s cpp -f html -t4 -n -i $? -o \
		$(top_srcdir)/html/herdstat/fetcher/$@

