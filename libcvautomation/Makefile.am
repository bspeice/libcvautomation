AM_CFLAGS = -Wall -Werror -O2 -I$(top_srcdir)/include/
AM_LDFLAGS =
AM_LIBS = -shared

#Lists the libraries to build
lib_LTLIBRARIES = libcvautomation.la
libcvautomation_la_SOURCES = libcvautomation-opencv.c libcvautomation-xlib.c libcvautomation-xtest.c
#libcvautomation_CFLAGS = -shared -I$(top_srcdir)/include -I$(top_srcdir)/libcvautomation -I$(top_srcdir)/include/libcvautomation

#Lists the headers to distribute
pkginclude_HEADERS = $(top_srcdir)/include/libcvautomation/libcvautomation.h $(top_srcdir)/include/libcvautomation/libcvautomation-opencv.h $(top_srcdir)/include/libcvautomation/libcvautomation-xlib.h $(top_srcdir)/include/libcvautomation/libcvautomation-xtest.h $(top_srcdir)/include/libcvautomation/xautomation_kbd.h $(top_srcdir)/include/libcvautomation/xautomation_keysym_map.h $(top_srcdir)/include/libcvautomation/xautomation_multikey_map.h
