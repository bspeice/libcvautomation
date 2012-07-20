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
	$(Doxygen) Doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	rm -rf $(top_srcdir)/docs/man $(top_srcdir)/docs/html $(top_srcdir)/docs/latex

endif

if BUILD_MAN
directory = $(top_srcdir)/docs/man/man3

dist_man_MANS = $(directory)/cvaPoint.3 $(directory)/libcvautomation.h.3 $(directory)/libcvautomation-xlib.h.3 $(directory)/libcvautomation_search_methods.3 $(directory)/xtest_key_strings.3 $(directory)/cvautomationList.3 $(directory)/libcvautomation-opencv.h.3 $(directory)/libcvautomation-xtest.h.3 $(directory)/xtest_command_strings.3 $(directory)/libcvautomation.3 $(directory)/writing_app_tests.3 $(directory)/cva-match.3 $(directory)/cva-input.3

$(directory)/cvaPoint.3: doxyfile.stamp
$(directory)/libcvautomation.h.3: doxyfile.stamp
$(directory)/libcvautomation-xlib.h.3: doxyfile.stamp
$(directory)/libcvautomation_search_methods.3: doxyfile.stamp
$(directory)/xtest_key_strings.3: doxyfile.stamp
$(directory)/cvautomationList.3: doxyfile.stamp
$(directory)/libcvautomation-opencv.h.3: doxyfile.stamp
$(directory)/libcvautomation-xtest.h.3: doxyfile.stamp
$(directory)/xtest_command_strings.3: doxyfile.stamp
$(directory)/libcvautomation.3: doxyfile.stamp
$(directory)/writing_app_tests.3: doxyfile.stamp
$(directory)/cva-match.3: doxyfile.stamp
$(directory)/cva-input.3: doxyfile.stamp

endif

