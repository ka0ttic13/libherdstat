# $Id: Makefile.am 221 2005-12-29 16:05:58Z ka0ttic $

include $(top_builddir)/Makefile.am.common

SUBDIRS = progress

cc_sources = \
	string.cc \
	regex.cc \
	file.cc \
	misc.cc \
	vars.cc \
	glob.cc \
	timer.cc \
	getcols.cc

hh_sources = \
	container_base.hh \
	string.hh \
	regex.hh \
	file.hh \
	misc.hh \
	vars.hh \
	glob.hh \
	timer.hh \
	functional.hh \
	algorithm.hh \
	getcols.hh

noinst_LTLIBRARIES = libutil.la
libutil_la_SOURCES = $(cc_sources) $(hh_sources)
libutil_la_LIBADD = progress/libprogress.la @CURSES_LIBS@

library_includedir=$(includedir)/$(PACKAGE)-$(VERSION_MAJOR).$(VERSION_MINOR)/herdstat/util
library_include_HEADERS = $(hh_sources)

MAINTAINERCLEANFILES = Makefile.in *~ *.loT

srchtml: $(foreach f, $(libutil_la_SOURCES), $(f).html)

%.cc.html: %.cc
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat/util || \
		mkdir $(top_srcdir)/html/herdstat/util
	@source-highlight -c ../../src.css -s cpp -f html -t4 -n -i $? -o \
		$(top_srcdir)/html/herdstat/util/$@

%.hh.html: %.hh
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat/util || \
		mkdir $(top_srcdir)/html/herdstat/util
	@source-highlight -c ../../src.css -s cpp -f html -t4 -n -i $? -o \
		$(top_srcdir)/html/herdstat/util/$@

