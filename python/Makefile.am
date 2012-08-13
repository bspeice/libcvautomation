EXTRA_DIST = libcvautomation.py

install-data-local: setup.py
	$(Python) setup.py install
	
##Unfortunately, we can't really uninstall the python file.
##The python dist-utils don't tell us where it got installed
##to, so we can't uninstall it.
##uninstall-local:

CLEANFILES = setup.py

all-local: libcvautomation.py
clean-local:
	rm -rf setup.py

