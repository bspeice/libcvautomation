AM_CFLAGS =
AM_LDFLAGS = 
AM_LIBS = -shared

#Lists the libraries to build
lib_LTLIBRARIES = libcvautomation.la
libcvautomation_la_SOURCES = libcvautomation-opencv.c libcvautomation-xlib.c libcvautomation-xtest.c
libcvautomation_la_LDFLAGS = -version-info @LIBTOOL_VERSION@ @X11_LIBS@ @XTEST_LIBS@ @CV_LIBS@
libcvautomation_la_CFLAGS = -shared -Wall -Werror -O2 -I$(top_srcdir)/include @X11_CFLAGS@ @XTEST_CFLAGS@ @CV_CFLAGS@

#Lists the headers to distribute
pkginclude_HEADERS = $(top_srcdir)/include/libcvautomation/libcvautomation.h $(top_srcdir)/include/libcvautomation/libcvautomation-opencv.h $(top_srcdir)/include/libcvautomation/libcvautomation-xlib.h $(top_srcdir)/include/libcvautomation/libcvautomation-xtest.h $(top_srcdir)/include/libcvautomation/xautomation_kbd.h $(top_srcdir)/include/libcvautomation/xautomation_keysym_map.h $(top_srcdir)/include/libcvautomation/xautomation_multikey_map.h
