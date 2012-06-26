libcvautomation TODO list
-----------------------------------

###### Core functionality #######
Add support for a string of characters to input to X, not just one at a time.

Fix the libcvautomation.h header such that it doesn't need to rely on the build-time flag USEOPENCV2, which will not be present if anyone builds something on libcvautomation - i.e. hard-code a define in the header that lists some of the options used at build (USEOPENCV2, etc.)
	Alternately, research creating a pkg-config .pc file that will contain the needed cflags and library includes.

###### Looking ahead ######
Add Python bindings
Research XInput2 to see if this would be a good idea to pursue.
