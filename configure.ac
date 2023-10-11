# Process this file with autoconf to produce a configure script.
# $Id: configure.ac 246 2005-04-26 12:03:53Z ka0ttic $

AC_PREREQ(2.59)
AC_INIT(libherdstat, [0.2.0], [ka0ttic@gentoo.org])
AC_CONFIG_SRCDIR([herdstat/exceptions.hh])
AC_CONFIG_AUX_DIR(config)

# release versioning
VERSION_MAJOR=0
VERSION_MINOR=2
VERSION_MICRO=0
VERSION_SUFFIX=
VERSION_SUFFIX_VERSION=
VERSION_FULL="$VERSION_MAJOR.$VERSION_MINOR.$VERSION_MICRO"

if ! test -z "$VERSION_SUFFIX" ; then
    VERSION_FULL="$VERSION_FULL"_"$VERSION_SUFFIX""$VERSION_SUFFIX_VERSION"
fi

VERSION="$VERSION_FULL"

AC_SUBST(VERSION_MAJOR)
AC_SUBST(VERSION_MINOR)
AC_SUBST(VERSION_MICRO)
AC_SUBST(VERSION_SUFFIX)
AC_SUBST(VERSION_SUFFIX_VERSION)
AC_SUBST(VERSION_FULL)

# shared lib versioning
LIBRARY_VERSION=1:0:0
#               | | |
#        +------+ | +---+
#        |        |     |
#        current:revision:age
#        |        |     |
#        |        |     +- increment if interfaces have been added
#        |        |        set to zero if interfaces have been removed
#                          or changed
#        |        +- increment if source code has changed
#        |           set to zero if current is incremented
#        +- increment if interfaces have been added, removed or changed
AC_SUBST(LIBRARY_VERSION)

AM_INIT_AUTOMAKE(libherdstat, [$VERSION_FULL])

test x$localstatedir = "xNONE" && localstatedir="$ac_default_localstatedir"
test x$sysconfdir = "xNONE" && sysconfdir="$ac_default_sysconfdir"
AC_DEFINE_UNQUOTED(LOCALSTATEDIR, "$localstatedir/herdstat", [Local state directory])
AC_DEFINE_UNQUOTED(SYSCONFDIR, "$sysconfdir", [System configuration directory])

dnl --with-test-data
AC_ARG_WITH(test-data,
    AC_HELP_STRING([--with-test-data],[Directory where test data is located]),
    [TEST_DATA=$withval],[TEST_DATA=foo])
if test x"$TEST_DATA" = "xfoo" ; then
    TEST_DATA="${PWD}/../test-data"
fi
AC_SUBST(TEST_DATA)

dnl --enable-examples
AC_MSG_CHECKING([whether to build examples])
AC_ARG_ENABLE(examples,
    AC_HELP_STRING([--enable-examples],[Build examples]),
    [enable_examples=$enableval],[enable_examples=yes])
AC_MSG_RESULT([$enable_examples])
AM_CONDITIONAL(BUILD_EXAMPLES, test x$enable_examples != "xno")

dnl --enable-debug
AC_MSG_CHECKING([whether to enable debugging code/flags])
AC_ARG_ENABLE(debug,
    AC_HELP_STRING([--enable-debug],[Enable debugging code/flags]),
    [enable_debug=$enableval],[enable_debug=no])
AC_MSG_RESULT([$enable_debug])
AM_CONDITIONAL(DEBUG, test x$enable_debug != "xno")

AC_PATH_PROGS(_WGET, wget)
if test x$_WGET = "x"; then
    AC_MSG_ERROR([wget is required])
fi
AC_DEFINE_UNQUOTED(WGET, "$_WGET", [wget location])

AC_LANG([C++])
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_LN_S

dnl hack to disable damn f77 libtool checks (stolen from sandbox's configure.in)
m4_undefine([AC_PROG_F77])
m4_defun([AC_PROG_F77],[])
AC_PROG_LIBTOOL

LIBTOOL="${LIBTOOL} --silent"
AC_SUBST(LIBTOOL)

dnl SED is defined by the LT_AC_PROG_SED ran by AC_PROG_LIBTOOL
AC_SUBST(SED)

AC_MSG_CHECKING([g++ version])
gxxver=`${CXX} -dumpversion | cut -f1 -d.`
AC_MSG_RESULT([$gxxver])
if test x$gxxver = "x4" ; then
    AC_DEFINE_UNQUOTED(HAVE_GCC4, 1, [GCC Version 4])
fi

LHS_CHECK_CXXFLAG([-pedantic])
LHS_CHECK_CXXFLAG([-ansi])
LHS_CHECK_CXXFLAG([-W])
LHS_CHECK_CXXFLAG([-Wextra])
LHS_CHECK_CXXFLAG([-Wall])
LHS_CHECK_CXXFLAG([-Wold-style-cast])
LHS_CHECK_CXXFLAG([-Woverloaded-virtual])
LHS_CHECK_CXXFLAG([-Wredundant-decls])

if test x$enable_debug != "xno" ; then
    LHS_CHECK_CXXFLAG([-ggdb3])
    AC_DEFINE(DEBUG, 1, [Enable debugging code])
fi

dnl Required headers
AC_HEADER_TIME(,
    [AC_MSG_ERROR([sys/time.h is required])])
AC_HEADER_DIRENT(,
    [AC_MSG_ERROR([dirent.h is required])])
AC_CHECK_HEADERS(regex.h,,
    [AC_MSG_ERROR([regex.h is required])])
AC_CHECK_HEADERS(glob.h,,
    [AC_MSG_ERROR([glob.h is required])])
AC_CHECK_HEADERS(fnmatch.h,,
    [AC_MSG_ERROR([fnmatch.h is required])])
AC_CHECK_HEADERS(libebt/libebt.hh,,
    AC_MSG_ERROR([libebt/libebt.hh is required]))

dnl Required functions
AC_CHECK_FUNCS(gettimeofday,,
    [AC_MSG_ERROR([gettimeofday is required])])
AC_CHECK_FUNCS(regcomp,,
    [AC_MSG_ERROR([regcomp is required])])
AC_CHECK_FUNCS(regexec,,
    [AC_MSG_ERROR([regexec is required])])
AC_CHECK_FUNCS(regfree,,
    [AC_MSG_ERROR([regfree is required])])
AC_CHECK_FUNCS(regerror,,
    [AC_MSG_ERROR([regerror is required])])
AC_CHECK_FUNCS(glob,,
    [AC_MSG_ERROR([glob is required])])
AC_CHECK_FUNCS(fnmatch,,
    [AC_MSG_ERROR([fnmatch is required])])
AC_CHECK_FUNCS(vasprintf,,
    [AC_MSG_ERROR(vasprintf is required)])

dnl Optional functions

dnl Optional libs
AC_MSG_CHECKING([whether to build the libcurl fetcher interface])
AC_ARG_WITH(curl,
    AC_HELP_STRING([--with-curl],[Build libcurl fetcher interface]),
    [WITH_CURL=$withval],[WITH_CURL=yes])
AC_MSG_RESULT([$WITH_CURL])

if test "$WITH_CURL" = "yes" ; then
    AC_CHECK_LIB(curl, curl_easy_init, [CURL_LIBS="-lcurl"],
	AC_MSG_ERROR([curl support enabled but libcurl not found]))
    AC_CHECK_HEADERS([curl/curl.h],,
	AC_MSG_ERROR([curl support enabled but curl/curl.h not found]))
    AC_DEFINE_UNQUOTED(HAVE_LIBCURL, 1, [Build libcurl interface])
fi
AC_SUBST(CURL_LIBS)

dnl Required libs

AC_CHECK_HEADERS([curses.h term.h],,
    AC_MSG_ERROR([ncurses headers required]))
AC_CHECK_LIB(ncurses, tgetent, [CURSES_LIBS="-lncurses"],
    AC_MSG_ERROR([ncurses is required]))
AC_SUBST(CURSES_LIBS)

PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES(xmlwrapp, xmlwrapp >= 0.5.0,
    [xmlwrapp_LIBS="-lxmlwrapp -lxslt -lxml2 -lz -lm"],
    [AC_MSG_ERROR([xmlwrapp is required])])
AC_SUBST(xmlwrapp_LIBS)

AM_CONFIG_HEADER(config.h)
AC_OUTPUT(Makefile
	  doc/Makefile
          doc/Doxyfile
	  examples/Makefile
	  examples/fetcher/Makefile
	  examples/fetcherimp/Makefile
	  examples/fetcher_options/Makefile
	  examples/fetchable/Makefile
	  examples/herds.xml/Makefile
	  examples/vars/Makefile
	  examples/cachable/Makefile
	  examples/package_finder/Makefile
	  examples/versions/Makefile
	  examples/version_components/Makefile
	  examples/progress/Makefile
	  herdstat/Makefile
	  herdstat/libherdstat_version.hh
	  herdstat/util/Makefile
	  herdstat/util/progress/Makefile
	  herdstat/io/Makefile
	  herdstat/fetcher/Makefile
	  herdstat/xml/Makefile
	  herdstat/portage/Makefile
	  tests/Makefile
	  tests/src/Makefile)
