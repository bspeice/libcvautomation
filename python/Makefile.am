EXTRA_DIST = libcvautomation.py

install-data-local: setup.py
	$(Python) setup.py install --prefix=$(DESTDIR)/$(prefix) --exec-prefix=$(DESTDIR)/$(exec_prefix)
    
##Unfortunately, we can't really uninstall the python file.
##The python dist-utils don't tell us where it got installed
##to, so we can't uninstall it.
##uninstall-local:

CLEANFILES = setup.py

all-local: libcvautomation.py
clean-local:
	rm -rf setup.py

