# Autoconf Settings
# Copyright (C) 2007-2017 kaoru
# $Id$

#### General ####
AC_PREREQ([2.69])
AC_INIT([bobura], [0.0.0], [kaorut@mc.pikara.ne.jp])
AM_INIT_AUTOMAKE([gnu dist-bzip2 dist-zip])
AC_CONFIG_SRCDIR([bobura_config.h-original])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
    bobura/Makefile
    bobura/include/Makefile
    bobura/res/Makefile
    bobura/src/Makefile
    bobura_core/Makefile
    bobura_core/include/Makefile
    bobura_core/include/bobura/Makefile
    bobura_core/res.test/Makefile
    bobura_core/src/Makefile
    bobura_core/test/Makefile
    bobura_model/Makefile
    bobura_model/include/Makefile
    bobura_model/include/bobura/Makefile
    bobura_model/src/Makefile
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
        [--enable-precompilation=EXT],
        [
            enables precompilation.
            When EXT given, it will be used for the extension of the precompiled header file.
            Otherwise, ``gch'' is used for the extension of the precompiled header file.
        ]
    ),
    test "X$enableval" = "Xyes" && PRECOMPILE_EXT="gch";
    test "X$enableval" = "Xyes" || PRECOMPILE_EXT=$enableval;
    PRECOMPILE_CPPFLAGS=" -I\$(top_builddir)/precompiled -I\$(top_srcdir)/precompiled -include precompiled.h";
    PRECOMPILE_BUILT_SOURCES="\$(top_builddir)/precompiled/precompiled.h.$PRECOMPILE_EXT"
)
AC_SUBST([PRECOMPILE_EXT])
AC_SUBST([PRECOMPILE_CPPFLAGS])
AC_SUBST([PRECOMPILE_BUILT_SOURCES])

#### Checks for programs ####
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_RANLIB
AC_ARG_WITH(
    iwyu,
    AS_HELP_STRING(
        [--with-iwyu=COMMAND], [Specify the include-what-you-use command. Or uses `include-what-you-use'.]
    ),
    IWYU=$withval
)
AC_CHECK_PROG(IWYU, include-what-you-use, include-what-you-use)
test -z $IWYU && \
    AC_MSG_WARN([You cannot check the includes for lack of include-what-you-use.])
AC_SUBST([IWYU_OPTS], "-Xiwyu --max_line_length=1024 -x c++ -std=c++11")
AC_SUBST([IWYU_IMP_PATH], "tools/iwyu_mappings.imp")
AC_ARG_WITH(
    doxygen,
    AS_HELP_STRING([--with-doxygen=COMMAND], [Specify the Doxygen command. Or uses `doxygen'.]),
    DOXYGEN=$withval
)
AC_CHECK_PROG(DOXYGEN, doxygen, doxygen)
test -z $DOXYGEN && \
    AC_MSG_WARN([You cannot generate documents for lack of Doxygen.])

#### Checks for libraries ####
AC_CHECK_FUNC(sem_open, , [AC_CHECK_LIB(rt, sem_open)])
AC_CHECK_LIB(pthread, pthread_cancel)
AC_CHECK_LIB(bz2, BZ2_bzCompressInit)
AC_CHECK_FUNC(iconv, , [AC_CHECK_LIB(iconv, libiconv)])

AX_BOOST_BASE([1.65.1])
AX_BOOST_CHRONO
AX_BOOST_DATE_TIME
AX_BOOST_FILESYSTEM
AX_BOOST_IOSTREAMS
AX_BOOST_PROGRAM_OPTIONS
AX_BOOST_SYSTEM
AX_BOOST_THREAD
AX_BOOST_UNIT_TEST_FRAMEWORK
AC_SUBST([LDFLAGS], "$LDFLAGS $BOOST_LDFLAGS")
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
    elif test -n "$TETENGO2";
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
    elif test -n "$TETENGO2";
    then
        TETENGO2_LIB="$TETENGO2/lib"
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
    elif test -n "$TETENGO2";
    then
        TETENGO2_DETAIL_INCLUDE="$TETENGO2/include"
    fi
)
AC_SUBST([TETENGO2_DETAIL_INCLUDE])
AC_ARG_WITH(
    tetengo2-detail-libdir,
    AS_HELP_STRING(
        [--with-tetengo2-detail-libdir=DIR],
        [Specify the directory for the Tetengo2-detail library files.]
    ),
    TETENGO2_DETAIL_LIB=$withval,
    if test "x$TETENGO2" = "xSUBMODULE";
    then
        TETENGO2_DETAIL_LIB="\$(top_srcdir)/lib/tetengo2/tetengo2_detail/src";
    elif test -n "$TETENGO2";
    then
        TETENGO2_DETAIL_LIB="$TETENGO2/lib"
    fi
)
AC_SUBST([TETENGO2_DETAIL_LIB])
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
    elif test -n "$TETENGO2";
    then
        TETENGO2_GUI_INCLUDE="$TETENGO2/include"
    fi
)
AC_SUBST([TETENGO2_GUI_INCLUDE])
AC_ARG_WITH(
    tetengo2-gui-libdir,
    AS_HELP_STRING(
        [--with-tetengo2-gui-libdir=DIR],
        [Specify the directory for the Tetengo2-gui library files.]
    ),
    TETENGO2_GUI_LIB=$withval,
    if test "x$TETENGO2" = "xSUBMODULE";
    then
        TETENGO2_GUI_LIB="\$(top_srcdir)/lib/tetengo2/tetengo2_gui/src";
    elif test -n "$TETENGO2";
    then
        TETENGO2_GUI_LIB="$TETENGO2/lib"
    fi
)
AC_SUBST([TETENGO2_GUI_LIB])

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
