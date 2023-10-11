# $Id: Makefile.am 222 2006-01-04 02:42:48Z ka0ttic $

include $(top_builddir)/Makefile.am.common

SUBDIRS = util io fetcher xml portage
MAINTAINERCLEANFILES = Makefile.in *~ .loT libherdstat_version.hh
EXTRA_DIST = libherdstat_version.hh.in doxygen.hh

cc_sources = \
	exceptions.cc \
	email_address.cc
hh_sources = \
	exceptions.hh \
	noncopyable.hh \
	cachable.hh \
	fetchable.hh \
	parsable.hh \
	progressable.hh \
	email_address.hh \
	defs.hh

lib_LTLIBRARIES = libherdstat.la
libherdstat_la_LDFLAGS = -release $(VERSION_MAJOR).$(VERSION_MINOR) -version-info $(LIBRARY_VERSION)
libherdstat_la_LIBADD = util/libutil.la \
			io/libio.la \
			fetcher/libfetcher.la \
			xml/libxml.la \
			portage/libportage.la
libherdstat_la_SOURCES = $(hh_sources) $(cc_sources)

library_includedir=$(includedir)/$(PACKAGE)-$(VERSION_MAJOR).$(VERSION_MINOR)/herdstat
library_include_HEADERS = $(hh_sources) libherdstat_version.hh

srchtml: $(foreach f, $(libherdstat_la_SOURCES), $(f).html)
	@for x in $(SUBDIRS) ; do \
		$(MAKE) -C $${x} $@ ; \
	done

%.cc.html: %.cc
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat || mkdir $(top_srcdir)/html/herdstat
	@source-highlight -c ../src.css -s cpp -f html -t4 -n -i $? -o ../html/herdstat/$@

%.hh.html: %.hh
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat || mkdir $(top_srcdir)/html/herdstat
	@source-highlight -c ../src.css -s cpp -f html -t4 -n -i $? -o ../html/herdstat/$@
