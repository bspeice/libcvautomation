AM_CFLAGS = -Wall -O2 -I$(top_srcdir)/include
AM_LDFLAGS =
AM_LIBS = -shared

#Lists the libraries to build
lib_LTLIBRARIES = libcvautomation.la
libcvautomation_la_SOURCES = libcvautomation-opencv.c libcvautomation-opencv.h libcvautomation-xlib.c libcvautomation-xlib.h libcvautomation.h libcvautomation-xtest.c libcvautomation-xtest.h
#libcvautomation_CFLAGS = -shared -I$(top_srcdir)/include -I$(top_srcdir)/libcvautomation -I$(top_srcdir)/include/libcvautomation

#Lists the headers to distribute
pkginclude_HEADERS = $(top_srcdir)/include/libcvautomation/libcvautomation.h $(top_srcdir)/include/libcvautomation/libcvautomation-opencv.h $(top_srcdir)/include/libcvautomation/libcvautomation-xlib.h $(top_srcdir)/include/libcvautomation/libcvautomation-xtest.h
