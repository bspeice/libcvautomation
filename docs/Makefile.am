if BUILD_DOXYGEN

EXTRA_DIST = html
install-data-local:
	$(mkdir_p) $(DESTDIR)$(datadir)/$(PACKAGE)/html
	for f in html/*; do \
		$(INSTALL_DATA) $(srcdir)/$$f \
		$(DESTDIR)$(datadir)/$(PACKAGE)/html; done

uninstall-local:
	rm $(DESTDIR)$(datadir)/$(PACKAGE)/html/*
	-rmdir $(DESTDIR)$(datadir)/$(PACKAGE)/html

doxyfile.stamp:
	$(Doxygen) Doxyfile_library
	$(Doxygen) Doxyfile_example
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	rm -rf $(top_srcdir)/docs/man $(top_srcdir)/docs/html $(top_srcdir)/docs/latex

endif

if BUILD_MAN
directory_1 = $(top_srcdir)/docs/man/man1
directory_3 = $(top_srcdir)/docs/man/man3

dist_man_MANS = $(directory_3)/cvaPoint.3 $(directory_3)/libcvautomation.h.3 $(directory_3)/libcvautomation-xlib.h.3 $(directory_3)/libcvautomation_search_methods.3 $(directory_3)/xtest_key_strings.3 $(directory_3)/cvautomationList.3 $(directory_3)/libcvautomation-opencv.h.3 $(directory_3)/libcvautomation-xtest.h.3 $(directory_3)/xtest_command_strings.3 $(directory_3)/libcvautomation.3 $(directory_3)/writing_app_tests.3 $(directory_1)/cva-match.1 $(directory_1)/cva-input.1

$(directory_3)/cvaPoint.3: doxyfile.stamp
$(directory_3)/libcvautomation.h.3: doxyfile.stamp
$(directory_3)/libcvautomation-xlib.h.3: doxyfile.stamp
$(directory_3)/libcvautomation_search_methods.3: doxyfile.stamp
$(directory_3)/xtest_key_strings.3: doxyfile.stamp
$(directory_3)/cvautomationList.3: doxyfile.stamp
$(directory_3)/libcvautomation-opencv.h.3: doxyfile.stamp
$(directory_3)/libcvautomation-xtest.h.3: doxyfile.stamp
$(directory_3)/xtest_command_strings.3: doxyfile.stamp
$(directory_3)/libcvautomation.3: doxyfile.stamp
$(directory_3)/writing_app_tests.3: doxyfile.stamp
$(directory_1)/cva-match.1: doxyfile.stamp
$(directory_1)/cva-input.1: doxyfile.stamp

endif

