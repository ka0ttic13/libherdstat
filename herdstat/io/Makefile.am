# $Id$

include $(top_builddir)/Makefile.am.common

cc_sources = \
	binary_stream.cc

hh_sources = \
	binary_stream.hh \
	binary_stream_iterator.hh

noinst_LTLIBRARIES = libio.la
libio_la_SOURCES = $(cc_sources) $(hh_sources)

library_includedir=$(includedir)/$(PACKAGE)-$(VERSION_MAJOR).$(VERSION_MINOR)/herdstat/io
library_include_HEADERS = $(hh_sources)

MAINTAINERCLEANFILES = Makefile.in *~ *.loT

srchtml: $(foreach f, $(libio_la_SOURCES), $(f).html)

%.cc.html: %.cc
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat/io || mkdir $(top_srcdir)/html/herdstat/io
	@source-highlight -c ../../src.css -s cpp -f html -t4 -n -i $? -o $(top_srcdir)/html/herdstat/io/$@

%.hh.html: %.hh
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat/io || mkdir $(top_srcdir)/html/herdstat/io
	@source-highlight -c ../../src.css -s cpp -f html -t4 -n -i $? -o $(top_srcdir)/html/herdstat/io/$@

