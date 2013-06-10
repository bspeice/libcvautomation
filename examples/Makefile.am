if BUILD_EXAMPLES
#Need to include the -Ilibcvautomation so that libcvautomation.h can find everything that it needs
AM_LDFLAGS = -L../libcvautomation/.libs -lcvautomation -lm @X11_LIBS@ @XTEST_LIBS@ @CV_LIBS@
AM_CFLAGS = -Wall -Werror -O2 -I$(top_srcdir)/include @X11_CFLAGS@ @XTEST_CFLAGS@ @CV_CFLAGS@

#Build only if we're building the examples
bin_PROGRAMS = cva-match cva-input
cva_match_SOURCES = cva-match.c
cva_input_SOURCES = cva-input.c
endif
