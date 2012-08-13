if BUILD_DOXYGEN
  DOCS_ENABLE = docs
endif

if BUILD_PYTHON
  PYTHON_ENABLE = python
endif

if BUILD_EXAMPLES
  EXAMPLES_ENABLE = examples
endif

SUBDIRS = libcvautomation $(EXAMPLES_ENABLE) $(PYTHON_ENABLE) $(DOCS_ENABLE)

#And the BASH macros
dist_sysconf_DATA = libcvautomation_funcs

#And the pkg-config files
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libcvautomation.pc

DISTCLEANFILES = libcvautomation.pc

#Make sure to distribute some special files we need for building
#the libcvautomation.h header
EXTRA_DIST = include/opencv1_includes include/opencv2_includes
