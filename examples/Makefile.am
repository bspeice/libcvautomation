#Need to include the -Ilibcvautomation so that libcvautomation.h can find everything that it needs
if USEOPENCV2
AM_LDFLAGS = -L../libcvautomation/.libs -lcvautomation `pkg-config --libs x11` -lopencv_imgproc -lopencv_core -lopencv_highgui -lXtst
AM_CFLAGS = -Wall -Werror -O2 -I$(top_srcdir)/include/opencv2 #-I$(top_srcdir)/include/libcvautomation
else
AM_LDFLAGS = -L../libcvautomation/.libs -lcvautomation `pkg-config --libs x11` `pkg-config --libs opencv` -lXtst
AM_CFLAGS = -Wall -Werror -O2 -I$(top_srcdir)/include/opencv1 #-I$(top_srcdir)/include/libcvautomation
endif

#Build only if we're building the examples
bin_PROGRAMS = cva-match cva-input
cva_match_SOURCES = cva-match.c
cva_input_SOURCES = cva-input.c
