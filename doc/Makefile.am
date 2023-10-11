CLEANFILES = *~ html/* man/*/* html man
MAINTAINERCLEANFILES = Makefile.in Doxyfile
EXTRA_DIST = Doxyfile.in header.html footer.html doxygen.css

doxygen: Doxyfile doxygen.css header.html footer.html \
		$(top_srcdir)/herdstat/*.hh $(top_srcdir)/herdstat/util/*.hh \
		$(top_srcdir)/herdstat/fetcher/*.hh $(top_srcdir)/herdstat/io/*.hh \
		$(top_srcdir)/herdstat/portage/*.hh $(top_srcdir)/herdstat/xml/*.hh
	@rm -fr html man
	@doxygen
	@rm -f $(VERSION)/man/man3/_*
