"""
libcvautomation_funcs.py

This is a high-level wrapper intended to give you easy access to
libcvautomation, while staying flexible and powerful.
This wrapper was designed to be like the Bash wrapper of the
same name, but allows access to the advanced features of Python - 
for example, error handling.
Also, it becomes easy to integrate other systems like dogtail
into the same application test if you want to combine features.

To use:
import libcvautomation_funcs

If there are any questions, comments, concerns, or suggestions,
notify the developer at <bspeice@uncc.edu>"""

#-------------------------------------------------------------------------------
#  Import the libcvautomation library - this should have already been installed
#-------------------------------------------------------------------------------
import libcvautomation

#-------------------------------------------------------------------------------
#  Set up the logging options
#-------------------------------------------------------------------------------
from sys import _current_frames() #For getting the function that called us
import time

def get_caller():
	current_frame = sys._current_frames().values()[0] #Current frame
	caller_frame = current_frame.f_back.f_back #Go back two frames to make sure
											   #we don't get the name of the function that just called us.

	caller_name = caller_frame.f_globals['__name__'] #And get the name
	return caller_name

outfile = '/dev/null'
def out( message ):
	global outfile #Make sure we use the global outfile,
				   #that people can change it if need be

	#with open(outfile, 'a') as outfile_handle
	outfile_handle = open(outfile, 'a')
	outfile_handle.__enter__()
	try:
		#Logfile format:
		# <hour>:<minute>:<second> <function_name>: <message>
		outfile_handle.write(time.stftime('%I:%M:%S ')
		outfile_handle.write(get_caller + ' ')
		outfile_handle.write(message)
		outfile_handle.write('\n')
	finally:
		outfile_handle.__exit__()


#-------------------------------------------------------------------------------
#  Set up the Xlib handler functions
#-------------------------------------------------------------------------------

X11_display=None #NULL

def check_display():
	global X11_display

	if X11_display is None:
		out( 'Trying to call ' + get_caller() + ' with no open display!' )
		return False
	else:
		return True

def get_display(): #Intended to be unsafe -
				   #all wrapper functions should use check_display() explicitly
	global X11_display
	return X11_display

#-------------------------------------------------------------------------------
#  The following two functions are intended to be used on the front-end
#-------------------------------------------------------------------------------
	
def open_display( display_name='' ):
	global X11_display
	X11_display = libcvautomation.cvaOpenDisplay( display_name )
	out( 'Opened display with name: ' + display_name )

def close_display():
	global X11_display
	if X11_display is None:
		out( 'Trying to close a display that has already been closed.' )
	else:
		libcvautomation.cvaCloseDisplay( X11_display )
		X11_display=None


#-------------------------------------------------------------------------------
#  Set up the default values for libcv
#    This way, we can edit the defaults for all functions very easily
#-------------------------------------------------------------------------------

_search_method_default=0
_tolerance_default=2250000

#-------------------------------------------------------------------------------
#  Begin the actual wrapper functions
#-------------------------------------------------------------------------------

def mouse_down( mouse_button = 1 ): #Default left-click
	pass

def mouse_up( mouse_button = 1 ): #Default left-click
	pass

def mouse_click( mouse_button = 1 ): #Default left-click
	pass

def mouse_click_xy( x_coord, y_coord, mouse_button = 1 ):
	pass

def mouse_click_rxy( x_inc, y_inc, mouse_button = 1 ):
	pass

def mouse_click_image( [image_names] ):
	pass

def mouse_doubleclick( mouse_button = 1 ):
	pass

def mouse_doubleclick_xy( x_coord, y_coord, mouse_button = 1 ):
	pass

def mouse_doubleclick_rxy( x_inc, y_inc, mouse_button = 1 ):
	pass

def mouse_doubleclick_image( [image_names] ):
	pass

def mouse_hover_xy( x_coord, y_coord ):
	pass

def mouse_hover_rxy( x_inc, y_inc ):
	pass

def mouse_hover_image( [image_names] ):
	pass

def mouse_jiggle():
	pass

def mouse_scroll_up():
	pass

def mouse_scroll_down():
	pass

def mouse_drag_n_drop( drag_image, drag_to ):
	pass

def key_string( string ):
	pass

def key_down( key_name ):
	pass

def key_up( key_name ):
	pass

def key_click( key_name ):
	pass

def image_location( [image_names] ):
	pass

def waitfor( [image_names] ):
	pass

## \file libcvautomation_funcs.py
# \brief Libcvautomation wrapper for python
# \details This source file is designed to give high-level access to libcvautomation using Python. It was modeled after the Bash wrapper, but allows for access to all the extra features of Python.
# \author Bradlee Speice
