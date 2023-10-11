include $(top_builddir)/Makefile.am.common

test_headers = $(foreach f, $(tests), $(f)-test.hh)

noinst_PROGRAMS = run_lhs_test
run_lhs_test_SOURCES = run_lhs_test.cc test_handler.hh $(test_headers)
run_lhs_test_LDADD = $(top_builddir)/herdstat/libherdstat.la

MAINTAINERCLEANFILES = Makefile.in *~ .loT
EXTRA_DIST = mk_run_lhs_test.sh run_lhs_test.cc.in
CLEANFILES = run_lhs_test.cc

run_lhs_test.cc: run_lhs_test.cc.in $(test_headers)
	@$(srcdir)/mk_run_lhs_test.sh run_lhs_test.cc.in $(test_headers)
