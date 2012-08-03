if BUILD_DOXYGEN
SUBDIRS = libcvautomation examples docs
else
SUBDIRS = libcvautomation examples
endif

#And the BASH macros
dist_sysconf_DATA = libcvautomation_funcs

#And the pkg-config files
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libcvautomation.pc

DISTCLEANFILES = libcvautomation.pc

#Make sure to distribute some special files we need for building
#the libcvautomation.h header
EXTRA_DIST = include/opencv1_includes include/opencv2_includes
