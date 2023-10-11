# $Id: Makefile.am 170 2005-12-03 12:30:41Z ka0ttic $

SUBDIRS = src

export tests := \
	binaryio \
	string \
	file \
	vars \
	container_base \
	glob \
	regex \
	algo \
	version \
	keyword \
	license \
	ebuild \
	email \
	package_list \
	package_finder \
	package_which \
	package_directory \
	herds.xml \
	devaway.xml \
	userinfo.xml \
	metadata.xml

TESTS = $(foreach f, $(tests), $(f)-test.sh)
TESTS_ENVIRONMENT = TEST_DATA=$(TEST_DATA) PORTDIR=$(TEST_DATA)/portdir PORTDIR_OVERLAY=''

CLEANFILES = actual/*

MAINTAINERCLEANFILES = Makefile.in *~
EXTRA_DIST = $(TESTS) common.sh expected
