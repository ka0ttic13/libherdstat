# $Id: Makefile.am 204 2005-12-22 15:57:43Z ka0ttic $

include $(top_builddir)/Makefile.am.common

cc_sources = \
	exceptions.cc \
	util.cc \
	config.cc \
	version.cc \
	categories.cc \
	package.cc \
	package_list.cc \
	package_finder.cc \
	package_which.cc \
	package_directory.cc \
	archs.cc \
	keywords.cc \
	license.cc \
	ebuild.cc \
	gentoo_email_address.cc \
	developer.cc \
	herd.cc \
	project_xml.cc \
	herds_xml.cc \
	metadata.cc \
	metadata_xml.cc \
	devaway_xml.cc \
	userinfo_xml.cc
hh_sources = \
	exceptions.hh \
	util.hh \
	config.hh \
	categories.hh \
	package.hh \
	package_list.hh \
	package_finder.hh \
	package_which.hh \
	package_directory.hh \
	version.hh \
	archs.hh \
	keywords.hh \
	license.hh \
	ebuild.hh \
	gentoo_email_address.hh \
	developer.hh \
	herd.hh \
	functional.hh \
	data_source.hh \
	project_xml.hh \
	herds_xml.hh \
	metadata.hh \
	metadata_xml.hh \
	devaway_xml.hh \
	userinfo_xml.hh

noinst_LTLIBRARIES = libportage.la
libportage_la_SOURCES = $(hh_sources) $(cc_sources)

library_includedir=$(includedir)/$(PACKAGE)-$(VERSION_MAJOR).$(VERSION_MINOR)/herdstat/portage
library_include_HEADERS = $(hh_sources)

MAINTAINERCLEANFILES = Makefile.in *~ .loT

srchtml: $(foreach f, $(libportage_la_SOURCES), $(f).html)
%.cc.html: %.cc
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat/portage || \
		mkdir $(top_srcdir)/html/herdstat/portage
	@source-highlight -c ../../src.css -s cpp -f html -t4 -n -i $? \
		-o $(top_srcdir)/html/herdstat/portage/$@
%.hh.html: %.hh
	@echo Generating $@
	@test -d $(top_srcdir)/html/herdstat/portage || \
		mkdir $(top_srcdir)/html/herdstat/portage
	@source-highlight -c ../../src.css -s cpp -f html -t4 -n -i $? \
		-o $(top_srcdir)/html/herdstat/portage/$@
