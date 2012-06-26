#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(libcvautomation, 0.1, bspeice@uncc.edu)
AM_INIT_AUTOMAKE

#AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SUBDIRS([libcvautomation/] [examples/])

#path intelc110		/opt/coe/intelc110
# Checks for programs.
AC_PROG_CC

AC_PROG_LIBTOOL
AM_PROG_LIBTOOL

# Checks for libraries.
#AC_CHECK_LIB(cv, cvMatchTemplate)
#AC_CHECK_LIB(cv, cvMinMaxLoc)
#AC_CHECK_LIB(X11, XGetImage)

# Checks for header files.
AC_PATH_X
#Headers needed for libcvautomation
#AC_CHECK_HEADER(stdio.h)
#AC_CHECK_HEADER(opencv/cv.h)
#AC_CHECK_HEADER(opencv/highgui.h)
#AC_CHECK_HEADER(X11/Xlib.h)
#AC_CHECK_HEADER(X11/Xutil.h)

#Configure OpenCV - version 2+ breaks a lot of things
PKG_CHECK_MODULES([OpenCV], [opencv >= 2.0.0], [use_opencv2=true], [use_opencv1=true])
AM_CONDITIONAL(USEOPENCV2, [test "$use_opencv2" != ""])
if test "$use_opencv2" != ""; then
	AC_DEFINE(USEOPENCV2)
fi
if test "$use_opencv1" != ""; then
	echo "could not find OpenCV version 2.0.0 or higher, checking for 1.0.0 or higher..."
	PKG_CHECK_MODULES([OpenCV], [opencv >= 1.0.0])
fi

PKG_CHECK_MODULES([X11], [x11 >= 1.0.3])
PKG_CHECK_MODULES([XTest], [xtst >= 0.21])

AC_ARG_WITH(examples, [  --with-examples         build example programs '['default=yes']'])

AM_CONDITIONAL(BUILD_EXAMPLES, [test "$with_examples" != "no"])
if test "$with_examples" != "no"; then
	#Headers needed for cva-match
	echo building examples
	AC_CHECK_HEADERS([limits.h stdlib.h unistd.h])
fi

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC

AC_OUTPUT([Makefile] [libcvautomation/Makefile] [examples/Makefile])
