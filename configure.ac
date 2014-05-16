# Autoconf Settings
# Copyright (C) 2007-2014 kaoru
# $Id$

#### General ####
AC_PREREQ([2.67])
AC_INIT([bobura], [0.0.0], [kaorut@mc.pikara.ne.jp])
AM_INIT_AUTOMAKE([gnu dist-bzip2 dist-zip])
AC_CONFIG_SRCDIR([bobura_config.h-original])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
    bobura/Makefile
    bobura/include/Makefile
    bobura/include/bobura/Makefile
    bobura/res/Makefile
    bobura/src/Makefile
    bobura/test/Makefile
    bobura_model/Makefile
    bobura_model/include/Makefile
    bobura_model/include/bobura/Makefile
    bobura_model/test/Makefile
    docsrc/Makefile
    iconsrc/Makefile
    installer_bobura/Makefile
    precompiled/Makefile
    samples/Makefile
    setup/Makefile
    setup/include/Makefile
    setup/include/setup/Makefile
    setup/res/Makefile
    setup/src/Makefile
    tools/Makefile
    vsprops/Makefile
])

AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

AC_ARG_ENABLE(
    precompilation,
    AS_HELP_STRING(
        [--enable-precompilation],
        [enables precompilation.]
    ),
    PRECOMPILE_CPPFLAGS=" -I\$(top_srcdir)/precompiled -include precompiled.h";
    PRECOMPILE_BUILT_SOURCES="\$(top_srcdir)/precompiled/precompiled.h.gch"
)
AC_SUBST([PRECOMPILE_CPPFLAGS])
AC_SUBST([PRECOMPILE_BUILT_SOURCES])

#### Checks for programs ####
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_RANLIB
AC_ARG_WITH(
    doxygen,
    AS_HELP_STRING(
        [--with-doxygen=DIR],
        [
            Specify the directory of Doxygen. If set, ``$DIR/doxygen'' is
            used. Otherwise, ``doxygen'' is used.
        ]
    ),
    DOXYGEN=$withval/doxygen
)
AC_CHECK_PROG(DOXYGEN, doxygen, doxygen)
test -z $DOXYGEN && \
    AC_MSG_WARN([You cannot generate documentation for lack of Doxygen.])

#### Checks for libraries ####
AX_BOOST_BASE([1.55.0])
AX_BOOST_CHRONO
AX_BOOST_DATE_TIME
AX_BOOST_FILESYSTEM
AX_BOOST_IOSTREAMS
AX_BOOST_PROGRAM_OPTIONS
AX_BOOST_SYSTEM
AX_BOOST_THREAD
AX_BOOST_UNIT_TEST_FRAMEWORK
AC_CHECK_LIB(bz2, BZ2_bzCompressInit)
AC_SUBST([LDFLAGS], "$LDFLAGS $BOOST_LDFLAGS")
AC_SUBST([LIBS], "-lpthread $LIBS")
AC_SUBST([LIBS], "$BOOST_CHRONO_LIB $LIBS")
AC_SUBST([LIBS], "$BOOST_DATE_TIME_LIB $LIBS")
AC_SUBST([LIBS], "$BOOST_FILESYSTEM_LIB $LIBS")
AC_SUBST([LIBS], "$BOOST_IOSTREAMS_LIB $LIBS")
AC_SUBST([LIBS], "$BOOST_PROGRAM_OPTIONS_LIB $LIBS")
AC_SUBST([LIBS], "$BOOST_SYSTEM_LIB $LIBS")
AC_SUBST([LIBS], "$BOOST_THREAD_LIB $LIBS")
AC_SUBST([UNITTEST_LIBS], "$BOOST_UNIT_TEST_FRAMEWORK_LIB")
AC_ARG_WITH(
    tetengo2,
    AS_HELP_STRING(
        [--with-tetengo2=DIR],
        [
            Specify the base directory of the Tetengo2.
            When DIR is equal to "SUBMODULE", Tetengo2 as a Git submodule
            ($(top_srcdir)/lib/tetengo2) is used.
        ]
    ),
    TETENGO2=$withval
)
AC_ARG_WITH(
    tetengo2-includedir,
    AS_HELP_STRING(
        [--with-tetengo2-includedir=DIR],
        [Specify the directory for the Tetengo2 header files.]
    ),
    TETENGO2_INCLUDE=$withval,
    if test "x$TETENGO2" = "xSUBMODULE";
    then
        TETENGO2_INCLUDE="\$(top_srcdir)/lib/tetengo2/tetengo2/include";
    elif -n "$TETENGO2";
    then
        TETENGO2_INCLUDE="$TETENGO2/include";
    fi
)
AC_SUBST([TETENGO2_INCLUDE])
AC_ARG_WITH(
    tetengo2-libdir,
    AS_HELP_STRING(
        [--with-tetengo2-libdir=DIR],
        [Specify the directory for the Tetengo2 library files.]
    ),
    TETENGO2_LIB=$withval,
    if test "x$TETENGO2" = "xSUBMODULE";
    then
        TETENGO2_LIB="\$(top_srcdir)/lib/tetengo2/tetengo2/src";
    elif -n "$TETENGO2";
    then
        TETENGO2_LIB="$TETENGO2/include"
    fi
)
AC_SUBST([TETENGO2_LIB])
AC_ARG_WITH(
    tetengo2-detail-includedir,
    AS_HELP_STRING(
        [--with-tetengo2-detail-includedir=DIR],
        [Specify the directory for the Tetengo2-detail header files.]
    ),
    TETENGO2_DETAIL_INCLUDE=$withval,
    if test "x$TETENGO2" = "xSUBMODULE";
    then
        TETENGO2_DETAIL_INCLUDE="\$(top_srcdir)/lib/tetengo2/tetengo2_detail/include";
    elif -n "$TETENGO2";
    then
        TETENGO2_DETAIL_INCLUDE="$TETENGO2/include"
    fi
)
AC_SUBST([TETENGO2_DETAIL_INCLUDE])
AC_ARG_WITH(
    tetengo2-gui-includedir,
    AS_HELP_STRING(
        [--with-tetengo2-gui-includedir=DIR],
        [Specify the directory for the Tetengo2-gui header files.]
    ),
    TETENGO2_GUI_INCLUDE=$withval,
    if test "x$TETENGO2" = "xSUBMODULE";
    then
        TETENGO2_GUI_INCLUDE="\$(top_srcdir)/lib/tetengo2/tetengo2_gui/include";
    elif -n "$TETENGO2";
    then
        TETENGO2_GUI_INCLUDE="$TETENGO2/include"
    fi
)
AC_SUBST([TETENGO2_GUI_INCLUDE])

#### Checks for header files ####
AC_CXX_HAVE_STD
AC_CXX_HAVE_STL
AC_HEADER_STDC
AC_SUBST([CPPFLAGS], "$CPPFLAGS $PRECOMPILE_CPPFLAGS")
AC_SUBST([CPPFLAGS], "$CPPFLAGS $BOOST_CPPFLAGS")

#### Checks for typedefs, structures, and compiler characteristics ####
AC_SUBST([CXXFLAGS], "$CXXFLAGS -Werror -Wall -Wextra -pedantic-errors")

#### Checks for library functions ####

#### Output ####
AC_OUTPUT
