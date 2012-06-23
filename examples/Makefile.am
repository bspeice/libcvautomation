#Need to include the -Ilibcvautomation so that libcvautomation.h can find everything that it needs
AM_CFLAGS = -Wall -O2 -I$(top_srcdir)/include #-I$(top_srcdir)/include/libcvautomation
if USEOPENCV2
AM_LDFLAGS = -L../libcvautomation/.libs -lcvautomation `pkg-config --libs x11` -lopencv_imgproc -lopencv_core -lopencv_highgui
else
AM_LDFLAGS = -L../libcvautomation/.libs -lcvautomation `pkg-config --libs x11` `pkg-config --libs opencv`
endif

#Build only if we're building the examples
bin_PROGRAMS = cva-match
cva_match_SOURCES = cva-match.c
