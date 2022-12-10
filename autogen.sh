#! /bin/sh
# This script is used to automate the process of running some of the autotools
# against their input files (configure.in, Makefile.am) after _any_ of them have
# been updated. 
# libtoolize --force
aclocal
automake --add-missing --force-missing
autoconf
