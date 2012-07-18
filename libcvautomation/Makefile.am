if USEOPENCV2
AM_CFLAGS = -Wall -Werror -O2 -I$(top_srcdir)/include/opencv2
else
AM_CFLAGS = -Wall -Werror -O2 -I$(top_srcdir)/include/opencv1
endif
AM_LDFLAGS =
AM_LIBS = -shared

#Lists the libraries to build
lib_LTLIBRARIES = libcvautomation.la
libcvautomation_la_SOURCES = libcvautomation-opencv.c libcvautomation-xlib.c libcvautomation-xtest.c
#libcvautomation_CFLAGS = -shared -I$(top_srcdir)/include -I$(top_srcdir)/libcvautomation -I$(top_srcdir)/include/libcvautomation

#Lists the headers to distribute
if USEOPENCV2
pkginclude_HEADERS = $(top_srcdir)/include/opencv2/libcvautomation/libcvautomation.h $(top_srcdir)/include/opencv2/libcvautomation/libcvautomation-opencv.h $(top_srcdir)/include/opencv2/libcvautomation/libcvautomation-xlib.h $(top_srcdir)/include/opencv2/libcvautomation/libcvautomation-xtest.h
else
pkginclude_HEADERS = $(top_srcdir)/include/opencv1/libcvautomation/libcvautomation.h $(top_srcdir)/include/opencv1/libcvautomation/libcvautomation-opencv.h $(top_srcdir)/include/opencv1/libcvautomation/libcvautomation-xlib.h $(top_srcdir)/include/opencv1/libcvautomation/libcvautomation-xtest.h
endif
