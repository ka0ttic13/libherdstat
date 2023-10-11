# $Id: Makefile.am 195 2005-12-13 12:53:23Z ka0ttic $
#
AUTOMAKE_OPTIONS = 1.8 dist-bzip2 no-dist-gzip

SUBDIRS = doc herdstat examples tests

MAINTAINERCLEANFILES = \
	INSTALL \
	COPYING \
	aclocal.m4 \
	configure \
	Makefile.in \
	config/* \
	config.h.in \
	stamp-h.in \
	html/*/*.html \
	*~

pc = $(PACKAGE)-$(VERSION_MAJOR).$(VERSION_MINOR).pc
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(pc)

DISTCLEANFILES = ChangeLog TODO $(pc)
EXTRA_DIST = \
	m4 \
	ChangeLog \
	Makefile.am.common \
	autogen.sh \
	.todo \
	libherdstat.pc.in

doxygen:
	$(MAKE) -C doc doxygen

srchtml:
	@test -d ${PWD}/html || mkdir ${PWD}/html ; \
	for x in herdstat ; do \
		if test -d ${PWD}/html/$${x} ; then \
			rm -fr ${PWD}/html/$${x}/* ; \
		else \
			mkdir ${PWD}/html/$${x} ; \
		fi ; \
		cd ${PWD}/$${x} && $(MAKE) $@ ; \
	done

TODO: .todo
	@test -x /usr/bin/devtodo && devtodo all --TODO

clitimestamp:
	@touch clitimestamp

ChangeLog: clitimestamp
	@if test -d $(top_srcdir)/.svn -a -x $(prefix)/bin/svn2cl ; then \
                svn up $(top_srcdir) ; \
                svn2cl --group-by-day --include-rev --stdout | \
                        @SED@ -e 's|\(ka0ttic\)|Aaron Walker <\1@gentoo.org>|' \
                        > $@; \
        else \
                touch ChangeLog; \
        fi
	@rm clitimestamp

$(pc):
	@@SED@   -e "s|\@prefix\@|$(prefix)|g" \
		-e "s|\@exec_prefix\@|$(exec_prefix)|g" \
		-e "s|\@libdir\@|$(libdir)|g" \
		-e "s|\@includedir\@|$(includedir)|g" \
		-e "s|\@VERSION\@|$(VERSION)|g" \
		-e "s|\@VERSION_MAJOR\@|$(VERSION_MAJOR)|g" \
		-e "s|\@VERSION_MINOR\@|$(VERSION_MINOR)|g" \
		libherdstat.pc.in > $@

distcheck-hook:
	@cp Makefile.am.common "$(PACKAGE)-$(VERSION)/_build/"

dist-hook: ChangeLog TODO

dist-sign: dist
	gpg --armour --detach-sign "$(PACKAGE)-$(VERSION).tar.bz2"

dist-upload: dist-sign
	echo -ne "user anonymous $(PACKAGE)\ncd incoming\nput $(PACKAGE)-$(VERSION).tar.bz2\nput $(PACKAGE)-$(VERSION).tar.bz2.asc\nbye" | \
		ftp -n ftp.berlios.de
