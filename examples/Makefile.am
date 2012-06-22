#Need to include the -Ilibcvautomation so that libcvautomation.h can find everything that it needs
AM_CFLAGS = -Wall -O2 -I$(top_srcdir)/include -I$(top_srcdir)/libcvautomation
AM_LDFLAGS = -L$(top_srcdir)/libcvautomation/.libs -lcvautomation `pkg-config --libs x11` `pkg-config --libs opencv`

#Build only if we're building the examples
bin_PROGRAMS = cva-match
cva_match_SOURCES = cva-match.c
