# $Id$

include $(top_builddir)/Makefile.am.common

cc_sources = \
	meter.cc \
	percent.cc \
	spinner.cc \
	dots.cc \
	ellipse.cc

hh_sources = \
	meter.hh \
	percent.hh \
	spinner.hh \
	dots.hh \
	ellipse.hh

noinst_LTLIBRARIES = libprogress.la
libprogress_la_SOURCES = $(cc_sources) $(hh_sources)
library_includedir=$(includedir)/$(PACKAGE)-$(VERSION_MAJOR).$(VERSION_MINOR)/herdstat/util/progress
library_include_HEADERS = $(hh_sources)

MAINTAINERCLEANFILES = Makefile.in *~ *.loT

srchtml: $(foreach f, $(libprogress_la_SOURCES), $(f).html)

%.cc.html: %.cc
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat/util/progress || \
		mkdir $(top_srcdir)/html/herdstat/util/progress
	@source-highlight -c ../../../src.css -s cpp -f html -t4 -n -i $? -o \
		$(top_srcdir)/html/herdstat/util/progress/$@

%.hh.html: %.hh
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat/util/progress || \
		mkdir $(top_srcdir)/html/herdstat/util/progress
	@source-highlight -c ../../../src.css -s cpp -f html -t4 -n -i $? -o \
		$(top_srcdir)/html/herdstat/util/progress/$@

