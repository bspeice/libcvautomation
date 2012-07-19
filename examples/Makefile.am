if BUILD_EXAMPLES
#Need to include the -Ilibcvautomation so that libcvautomation.h can find everything that it needs
AM_LDFLAGS = -L../libcvautomation/.libs -lcvautomation `pkg-config --libs x11` `pkg-config --libs opencv` `pkg-config --libs xtst`
AM_CFLAGS = -Wall -Werror -O2 -I$(top_srcdir)/include

#Build only if we're building the examples
bin_PROGRAMS = cva-match cva-input
cva_match_SOURCES = cva-match.c
cva_input_SOURCES = cva-input.c
endif
