AC_INIT([mpegtest], [1.0])
AC_CONFIG_SRCDIR([src])
# to prevent passing VERSION to compiller options
# https://www.gnu.org/software/automake/manual/automake.html#List-of-Automake-options
AM_INIT_AUTOMAKE([no-define])
AC_PROG_CXX

CFLAGS = 
LDFLAGS =
LIBS = 

# AC_OUTPUT takes a space delimited list of where the Makefiles are to be created.
# You need to pass all directories where there is source code (including the base
# directory containing all of the source code (which won't need a path pre-pended
# to the 'Makefile' keyword).
AC_OUTPUT(Makefile src/Makefile)
