#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(libcvautomation, 1.0, bspeice@uncc.edu)
#AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE


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
#Let doxygen know where our headers are at
AC_SUBST(INPUT_PATH, "../include/opencv2 ../examples")
if test "$use_opencv1" != ""; then
	echo "could not find OpenCV version 2.0.0 or higher, checking for 1.0.0 or higher..."
	PKG_CHECK_MODULES([OpenCV], [opencv >= 1.0.0])
	#Update doxygen on where our headers are at
	AC_SUBST(INPUT_PATH, "../include/opencv1 ../examples")
fi

PKG_CHECK_MODULES([X11], [x11 >= 1.0.3])
PKG_CHECK_MODULES([XTest], [xtst >= 0.21])

AC_ARG_WITH(examples, [  --with-examples         build example programs @<:@default=yes@:>@])

AM_CONDITIONAL(BUILD_EXAMPLES, [test "$with_examples" != "no"])
if test "$with_examples" != "no"; then
	#Headers needed for cva-match
	AC_CHECK_HEADERS([limits.h stdlib.h unistd.h])
fi

# Check for doxygen
AC_ARG_WITH(docs, [  --with-documentation    build documentation for libcvautomation @<:@default=yes@:>@])
AC_ARG_ENABLE(man, [  --enable-man            enable building the 'man' pages for libcvautomation @<:@default=enable@:>@])
AC_ARG_ENABLE(tex, [  --enable-tex            enable building the 'latex' pages for libcvautomation @<:@default=enable@:>@])
if test "$with_docs" != "no"; then
	AC_CHECK_PROGS([Doxygen], [doxygen])
	if test -z "$Doxygen"; then
		AC_MSG_WARN([Doxygen not found - continuing without building documentation.])
	fi

	AM_CONDITIONAL(BUILD_DOXYGEN, [test "$with_docs" != "no"])
	AM_COND_IF(BUILD_DOXYGEN, [AC_CONFIG_FILES([docs/Doxyfile])])

	#Check if we should generate man pages
	if test "$enable_man" != "no"; then
		AC_SUBST(ENABLE_MAN, YES)
		AM_CONDITIONAL(BUILD_MAN, [test "$enable_man" != "no"])
	fi

	#Check if we should build Tex pages
	if test "$enable_tex" != "no"; then
		AC_SUBST(ENABLE_TEX, YES)
		AM_CONDITIONAL(BUILD_TEX, [test "$enable_tex" != "no"])
	fi
fi

# Checks for library functions.
AC_FUNC_MALLOC

AC_OUTPUT([Makefile] [libcvautomation/Makefile] [examples/Makefile] [docs/Makefile])
