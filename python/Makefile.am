pyexec_LTLIBRARIES = _libcvautomation.la
_libcvautomation_la_SOURCES = libcvautomation-swig.c
_libcvautomation_la_LDFLAGS = -avoid-version -module $(PYTHON_LDFLAGS)
_libcvautomation_la_LIBADD = -lcvautomation
_libcvautomation_la_CFLAGS = $(PYTHON_CPPFLAGS) -I$(top_srcdir)/include

python_PYTHON = libcvautomation.py libcvautomation_funcs.py

EXTRA_DIST = libcvautomation.swig

libcvautomation-swig.c: libcvautomation.swig
	$(Swig) -I$(top_srcdir)/include -python -o libcvautomation-swig.c -outdir . libcvautomation.swig
