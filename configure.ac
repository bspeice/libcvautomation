#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(libcvautomation, 2.1, bspeice@uncc.edu)
AC_SUBST(PATCHLEVEL, 1)
AC_SUBST(LIBTOOL_VERSION, 2:1)
#AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

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
AC_SUBST_FILE([cv_headers])
if test "$use_opencv2" == "true"; then
	#Let doxygen know where our headers are at
	AC_SUBST(CV_VERSION, "opencv2")
	cv_headers=$srcdir/include/opencv2_includes
	AC_SUBST(CV_CFLAGS, [`pkg-config --cflags opencv`])
	AC_SUBST(CV_LIBS, ["-lopencv_core -lopencv_imgproc -lopencv_highgui"])
else
	echo "could not find OpenCV version 2.0.0 or higher, checking for 1.0.0 or higher..."
	PKG_CHECK_MODULES([OpenCV], [opencv >= 1.0.0])
	#Update doxygen on where our headers are at
	AC_SUBST(CV_VERSION, "opencv1")
	cv_headers=$srcdir/include/opencv1_includes
	AC_SUBST(CV_CFLAGS, [`pkg-config --cflags opencv`])
	AC_SUBST(CV_LIBS, [`pkg-config --libs opencv`])
fi

PKG_CHECK_MODULES([X11], [x11 >= 1.0.3])
AC_SUBST(X11_CFLAGS, [`pkg-config --cflags x11`])
AC_SUBST(X11_LIBS, [`pkg-config --libs x11`])

PKG_CHECK_MODULES([XTest], [xtst >= 0.21])
AC_SUBST(XTEST_CFLAGS, [`pkg-config --cflags xtst`])
AC_SUBST(XTEST_LIBS, [`pkg-config --libs xtst`])

AC_ARG_WITH(examples, [  --with-examples         build example programs @<:@default=yes@:>@])

AM_CONDITIONAL(BUILD_EXAMPLES, [test "$with_examples" != "no"])
if test "$with_examples" != "no"; then
	#Headers needed for cva-match
	AC_CHECK_HEADERS([limits.h stdlib.h unistd.h])
fi

# Check for doxygen
AC_ARG_WITH(docs, [  --with-docs             build documentation for libcvautomation @<:@default=yes@:>@])
AC_ARG_ENABLE(man, [  --enable-man            enable building the 'man' pages for libcvautomation
                            only works if --with-docs is enabled @<:@default=enable@:>@])
AC_ARG_ENABLE(tex, [  --enable-tex            enable building the 'latex' pages for libcvautomation
                            only works if --with-docs is enabled @<:@default=disable@:>@])

if test "$with_docs" != "no"; then
	AC_CHECK_PROGS([Doxygen], [doxygen], [missing])

	if test "$Doxygen" == "missing"; then
		AC_MSG_WARN([Doxygen not found - continuing without building documentation.])
		AM_CONDITIONAL(BUILD_DOXYGEN, [test "$Doxygen" != "missing"]) #false
		enable_man="no"
		enable_tex="no"
	else
		AM_CONDITIONAL(BUILD_DOXYGEN, [test "$with_docs" != "no"])
		AC_CONFIG_FILES([docs/Doxyfile_library] [docs/Doxyfile_example] [docs/Makefile])
	fi
else
	AM_CONDITIONAL(BUILD_DOXYGEN, [test "$with_docs" != "no"]) #false
	enable_man="no"
	enable_tex="no"
fi

#Check if we should generate man pages
if test "$enable_man" != "no"; then
	AC_SUBST(ENABLE_MAN, YES)
	AM_CONDITIONAL(BUILD_MAN, [test "$enable_man" != "no"])
else
	AC_SUBST(ENABLE_MAN, NO)
	AM_CONDITIONAL(BUILD_MAN, [test "$enable_man" != "no"]) #false
fi

#Check if we should build Tex pages
if test "$enable_tex" == "yes"; then
	AC_SUBST(ENABLE_TEX, YES)
	AM_CONDITIONAL(BUILD_TEX, [test "$enable_tex" == "yes"])
else
	AC_SUBST(ENABLE_TEX, NO)
	AM_CONDITIONAL(BUILD_TEX, [test "$enable_tex" == "yes"]) #false
fi

AC_ARG_WITH(python, [  --with-python           Install python support for libcvautomation])
#Check if we should distribute Python
if test "$with_python" != "no"; then
	AC_CHECK_PROGS([Python], [python], [missing])
	AC_CHECK_PROGS([Swig], [swig], [missing])
	AM_PATH_PYTHON([2.4])
	m4_include([m4/m4_ax_python_devel.m4])
	AX_PYTHON_DEVEL([>= '2.4'])
fi
if test "$Python" == "missing"; then
	echo "Could not find a suitable Python program. Disabling building python support..."
	with_python="no"
fi
if test "$Swig" == "missing"; then
	echo "Could not find a suitable SWIG program. Disabling building python support..."
	with_python="no"
fi

AM_CONDITIONAL(BUILD_PYTHON, [test "$with_python" != "no"]) #true unless --without-python

if test "$with_python" != "no"; then
	#Only generate the config if both python and swig are available
	AC_CONFIG_FILES([python/Makefile])
fi

# Checks for library functions.
AC_FUNC_MALLOC

AC_SUBST_FILE(rpm_changelog)
rpm_changelog=$srcdir/ChangeLog
AC_SUBST_FILE(deb_changelog)
deb_changelog=$srcdir/ChangeLog
AC_SUBST_FILE(deb_copyright)
deb_copyright=$srcdir/COPYING

AC_OUTPUT(
[Makefile]
[libcvautomation/Makefile]
[examples/Makefile]
[libcvautomation.pc]
[include/libcvautomation/libcvautomation.h]
[rpm/libcvautomation.spec]
[debian/copyright]
[debian/changelog]
)
