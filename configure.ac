AC_INIT([mpegtest], [1.0])
AC_CONFIG_SRCDIR([src/mpegtest.cpp])
# to prevent passing VERSION to compiller options
# https://www.gnu.org/software/automake/manual/automake.html#List-of-Automake-options
AM_INIT_AUTOMAKE([no-define])
AC_PROG_CXX

CFLAGS=
LDFLAGS=
LIBS=
# This is a reusable macro for providing --with-libfoo functionality.
#
# REQUIRE_LIB(name,lib,testfn,description)
# name = The complete name of the library file without the extension.
# lib = The name of the library file without the 'lib' prefix and without the extension.
# testfn = One function included in the library that can be used for a test compilation.
# description = Human readable text to be displayed if the library can't be found or
# if there's a problem during the test compilation.
AC_DEFUN([REQUIRE_LIB], [ {
    AC_ARG_WITH([$1], AC_HELP_STRING([--with-$1=<path>],[Location where $4 is installed]),[],[with_$1=default])
    AS_IF( [test "x$with_$1" != xdefault],
    [
        LDFLAGS="$LDFLAGS -L${with_$1}/lib"
        CFLAGS="$CFLAGS -I${with_$1}/include"
    ])
        AC_CHECK_LIB($2,$3,[],
    [
        AC_MSG_ERROR([$4 was not found, try specifying --with-$1])
    ])
} ] )
# The list of libraries required by the source code that are external to
# our code.
#REQUIRE_LIB(libpcap,pcap,pcap_dump_open,[Libpcap packet capture library])

# AC_OUTPUT takes a space delimited list of where the Makefiles are to be created.
# You need to pass all directories where there is source code (including the base
# directory containing all of the source code (which won't need a path pre-pended
# to the 'Makefile' keyword).

AC_OUTPUT(Makefile src/Makefile)
