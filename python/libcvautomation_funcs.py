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

def get_display(): #Intended to be unsafe (and a bit faster)-
				   #all wrapper functions should use check_display() explicitly
	global X11_display
	return X11_display

#-------------------------------------------------------------------------------
#  The following two functions are intended to be used on the front-end
#-------------------------------------------------------------------------------
	
def open_display( display_name='' ):
	global X11_display
	X11_display = libcvautomation.cvaOpenDisplay( display_name )
	if X11_display not is Nothing:
		out( 'Opened display with name: ' + display_name )
		return True
	else:
		return False

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
_tolerance_default=2250000 #Acceptable values are INT_MIN to INT_MAX
_timeout_default=5
_libcvautomation_error_location = libcvautomation.cvaPoint
_libcvautomation_error_location.x = _libcvautomation_error_location.y = -1

#-------------------------------------------------------------------------------
#  Begin the actual wrapper functions
#-------------------------------------------------------------------------------

def mouse_down( mouse_button = 1 ): #Default left-click
	"""Press a mouse button down, and leave it down."""
	if check_display():
		out( 'Mouse button down: ' + mouse_button )
		libcvautomation.xte_mouseDown( get_display(), mouse_button )
		return True
	else:
		#Display not open
		return False

def mouse_up( mouse_button = 1 ): #Default left-click
	"""Release a mouse button."""
	if check_display():
		out( 'Mouse button up: ' + mouse_button )
		libcvautomation.xte_mouseUp( get_display(), mouse_button )

		return True
	else:
		#Display not open
		return False

def mouse_click( mouse_button = 1 ): #Default left-click
	"""Click a mouse button where the mouse is currently located"""
	if check_display()
		out( 'Mouse button click: ' + mouse_button )
		libcvautomation.xte_clickMouse( get_display(), mouse_button )
		return True
	else:
		#Display not open
		return False

def mouse_click_xy( x_coord, y_coord, mouse_button = 1 ):
	"""Click a mouse button at an absolute coordinate"""
	if check_display():
		out( 'Mouse button xy click: x=' + str(x_coord) + ' y=' + str(y_coord) + ' mouse_button=' + mouse_button )
		current_location = libcvautomation.xte_mouseLocation( get_display() )
		x_increment = x_coord - current_location.x
		y_increment = y_coord - current_location.y

		libcvautomation.xte_hoverMouseRXY( get_display(), x_increment, y_increment )
		libcvautomation.xte_clickMouse( get_display(), mouse_button )

		return True
	else:
		#Display not open
		return False

def mouse_click_rxy( x_inc, y_inc, mouse_button = 1 ):
	"""Click a mouse button at a location relative to where it currently is at"""
	if check_display():
		out( 'Mouse button rxy click: x=' + str(x_inc) + ' y=' + str(y_inc) + ' mouse_button=' + mouse_button )
		libcvautomation.xte_hoverMouseRXY( get_display(), x_inc, y_inc )
		libcvautomation.xte_clickMouse( get_display(), mouse_button )

		return True
	else:
		#Display not open
		return False

def mouse_click_image( [image_names], search_method = _search_method_default,
						tolerance = _tolerance_default, timeout = _timeout_default,
						mouse_button = 1, use_wait = True,
						use_center = True ):
	"""Click a mouse button on an image inside the root X11 window"""
	if check_display():
		out( 'Mouse button click on image: Images=' + image_names + 
				' search_method=' + search_method + ' tolerance=' + tolerance +
				' timeout=' + _timeout_default + ' mouse_button=' +
				' use_wait=' + use_wait + ' use_center=' + use_center)

		if use_wait:
			#Loop through all images 'timeout' times, and click on the first match
			loop_check = 0
			while loop_check < timeout:
				for image in image_names:
					if use_center:
						image_location = libcvautomation.xte_clickMouseImage_location_center( get_display(),
											image, mouse_button, search_method, tolerance )
					else:
						image_location = libcvautomation.xte_clickMouseImage_location( get_display(),
											image, mouse_button, search_method, tolerance )

					if image_location != _libcvautomation_error_location
						#We've found our image, break out of the for loop and while loop
						return True

				loop_check += 1
		else:
			#Just cycle through the images once
			for image in image_names:
				if use_center:
					image_location = libcvautomation.xte_clickMouseImage_location_center( get_display(),
											image, mouse_button, search_method, tolerance )
				else:
					image_location = libcvautomation.xte_clickMouseImage_location( get_display(),
											image, mouse_button, search_method, tolerance )

				if image_location != _libcvautomation_error_location
					#We've found our image, break out of the for loop
					return True
	else:
		#Display not open or no image found
		return False


def mouse_doubleclick( mouse_button = 1 ):
	"""Click a mouse button twice where the mouse is currently located"""
	if check_display()
		out( 'Mouse button doubleclick: ' + mouse_button )
		libcvautomation.xte_clickMouse( get_display(), mouse_button )

		return True
	else:
		#Display not open
		return False


def mouse_doubleclick_xy( x_coord, y_coord, mouse_button = 1 ):
	"""Click a mouse button twice at an absolute coordinate"""
	if check_display():
		out( 'Mouse button xy doubleclick: x=' + str(x_coord) + ' y=' + str(y_coord) + ' mouse_button=' + mouse_button )
		current_location = libcvautomation.xte_mouseLocation( get_display() )
		x_increment = x_coord - current_location.x
		y_increment = y_coord - current_location.y

		libcvautomation.xte_hoverMouseRXY( get_display(), x_increment, y_increment )
		libcvautomation.xte_clickMouse( get_display(), mouse_button )
		libcvautomation.xte_clickMouse( get_display(), mouse_button )

		return True
	else:
		#Display not open
		return False

def mouse_doubleclick_rxy( x_inc, y_inc, mouse_button = 1 ):
	"""Click a mouse button twice at a location relative to where it currently is at"""
	if check_display():
		out( 'Mouse button relative xy doubleclick: x=' + str(x_inc) + ' y=' + str(y_inc) + ' mouse_button=' + mouse_button )
		libcvautomation.xte_hoverMouseRXY( get_display(), x_inc, y_inc )
		libcvautomation.xte_clickMouse( get_display(), mouse_button )
		libcvautomation.xte_clickMouse( get_display(), mouse_button )

		return True
	else:
		#Display not open
		return False

def mouse_doubleclick_image( [image_names], search_method = _search_method_default,
						tolerance = _tolerance_default, timeout = _timeout_default,
						mouse_button = 1, use_wait = True,
						use_center = True ):
	"""Click a mouse button twice on an image inside the root X11 window"""
	if check_display():
		out( 'Mouse button doubleclick on image: Images=' + image_names + 
				' search_method=' + search_method + ' tolerance=' + tolerance +
				' timeout=' + _timeout_default + ' mouse_button=' +
				' use_wait=' + use_wait + ' use_center=' + use_center)

		if use_wait:
			#Loop through all images 'timeout' times, and click on the first match
			loop_check = 0
			while loop_check < timeout:
				for image in image_names:
					if use_center:
						image_location = libcvautomation.xte_clickMouseImage_location_center( get_display(),
											image, mouse_button, search_method, tolerance )
					else:
						image_location = libcvautomation.xte_clickMouseImage_location( get_display(),
											image, mouse_button, search_method, tolerance )

					if image_location != _libcvautomation_error_location
						#Make sure to click twice once we've found the image
						#Technically assumes that the system mouse timeout is less than
						#the time it takes to do two boolean compares - I think this is pretty safe
						libcvautomation.xte_clickMouse( get_display(), mouse_button )
						#We've found our image, break out of the for loop and while loop
						return True

				loop_check += 1
		else:
			#Just cycle through the images once
			for image in image_names:
				if use_center:
					image_location = libcvautomation.xte_clickMouseImage_location_center( get_display(),
											image, mouse_button, search_method, tolerance )
				else:
					image_location = libcvautomation.xte_clickMouseImage_location( get_display(),
											image, mouse_button, search_method, tolerance )

				if image_location != _libcvautomation_error_location
					#We've found our image, break out of the for loop
					return True

	else:
		#Display not open, or no image found
		return False

def mouse_hover_xy( x_coord, y_coord ):
	"""Move the mouse to an absolute coordinate"""
	if check_display():
		out( 'Mouse button hover xy: x=' + str(x_coord) + ' y=' + str(y_coord) + ' mouse_button=' + mouse_button )
		current_location = libcvautomation.xte_mouseLocation( get_display() )
		x_increment = x_coord - current_location.x
		y_increment = y_coord - current_location.y

		libcvautomation.xte_hoverMouseRXY( get_display(), x_increment, y_increment )

		return True
	else:
		#Display not open
		return False


def mouse_hover_rxy( x_inc, y_inc ):
	"""Move the mouse to a location relative to where it currently is at"""
	if check_display():
		out( 'Mouse button hover relative xy: x=': + str(x_inc) + ' y=' + str(y_inc) )
		libcvautomation.xte_hoverMouseRXY( get_display(), x_inc, y_inc )

		return True
	else:
		#Display not open
		return False

def mouse_hover_image( [image_names], search_method = _search_method_default,
						tolerance = _tolerance_default, timeout = _timeout_default,
						mouse_button = 1, use_wait = True,
						use_center = True ):
	"""Move the mouse to an image inside the root X11 window"""
	if check_display():
		out( 'Mouse button click on image: Images=' + image_names + 
				' search_method=' + search_method + ' tolerance=' + tolerance +
				' timeout=' + _timeout_default + ' mouse_button=' +
				' use_wait=' + use_wait + ' use_center=' + use_center)

		if use_wait:
			#Loop through all images 'timeout' times, and click on the first match
			loop_check = 0
			while loop_check < timeout:
				for image in image_names:
					if use_center:
						image_location = libcvautomation.xte_hoverMouseImage_location_center( get_display(),
											image, mouse_button, search_method, tolerance )
					else:
						image_location = libcvautomation.xte_hoverMouseImage_location( get_display(),
											image, mouse_button, search_method, tolerance )

					if image_location != _libcvautomation_error_location
						#We've found our image, break out of the for loop and while loop
						return True

				loop_check += 1
		else:
			#Just cycle through the images once
			for image in image_names:
				if use_center:
					image_location = libcvautomation.xte_hoverMouseImage_location_center( get_display(),
											image, mouse_button, search_method, tolerance )
				else:
					image_location = libcvautomation.xte_hoverMouseImage_location( get_display(),
											image, mouse_button, search_method, tolerance )

				if image_location != _libcvautomation_error_location
					#We've found our image, break out of the for loop
					return True
	else:
		#Display not open or no image found
		return False


def mouse_jiggle():
	"""Jiggle the mouse in place"""
	if check_display():
		out( 'Mouse button jiggle' )
		libcvautomation.xte_mouseJiggle( get_display() )
		return True
	else:
		#Display not open
		return False


def mouse_scroll_up():
	"""Scroll the mouse wheel up"""
	if check_display():
		out( 'Mouse scroll up' )
		libcvautomation.xte_mouseScrollUp( get_display() )
		return True
	else:
		#Display not open
		return False

def mouse_scroll_down():
	"""Scroll the mouse wheel down"""
	if check_display():
		out( 'Mouse scroll down' )
		libcvautomation.xte_mouseScrollDown( get_display() )
		return True
	else:
		#Display not open
		return False

def mouse_drag_n_drop( drag_image, drag_to ):
	"""Drag and drop from one location to another"""
	if check_display():
		out( 'Mouse drag and drop: dragging from=' + drag_image +
			' dragging to=' + drag_to )
		successful_hover = mouse_hover_image( drag_image )
		if successful_hover:
			mouse_down( mouse_button=1 )
			successful_hover = mouse_hover_image( drag_to )
			mouse_up( mouse_button=1 )

		#Return True if both hovers are successful, False otherwise
		return successful_hover
	else:
		#Display not open
		return False


def key_string( string ):
	"""Enter a string of text on the keyboard"""
	if check_display():
		out( 'Key string enter: string=' + string )
		libcvautomation.xte_clickKeyStr( get_display(), string )
		return True
	else:
		#Display not open
		return False


def key_down( key_name ):
	"""Press a key down on the keyboard"""
	if check_display():
		out( 'Key button down: key_name=' + key_name )
		libcvautomation.xte_keyDown( get_display(), key_name )
		return True
	else:
		#Display not open
		return False

def key_up( key_name ):
	"""Press a key down on the keyboard"""
	if check_display():
		out( 'Key button up: key_name=' + key_name )
		libcvautomation.xte_keyUp( get_display(), key_name )
		return True
	else:
		#Display not open
		return False

def key_click( key_name ):
	"""Press a key down on the keyboard and release it"""
	if check_display():
		out( 'Key button click: key_name=' + key_name )
		libcvautomation.xte_keyDown( get_display(), key_name )
		return True
	else:
		#Display not open
		return False

def image_location( [image_names], search_method = _search_method_default,
						tolerance = _tolerance_default,	use_center = True ):
	"""Find the location of an image on screen (don't wait for it to show up)"""
	if check_display():
		location_array = {}
		out( 'Locate image (image_location): image_names=' + image_names )
		if use_center:
			for image in image_names:
				image_location = libcvautomation.matchSubImage_X11_center( get_display(), image,
									search_method, tolerance )
				location_array += [image, image_location]
		else:
			for image in image_names:
				image_location = libcvautomation.matchSubImage_X11( get_display(), image,
									search_method, tolerance )
				location_array += [image, image_location]

		return location_array
	else:
		#Display not open, but return the same type
		return {}



def wait_for( [image_names], search_method = _search_method_default,
				tolerance = _tolerance_default, timeout = _timeout_default,
				use_wait = True, use_center = True ):
	"""Find the location of an image on screen (wait for it to show up if it's not immediately available)"""
	if check_display():
		location_array = {}
		out( 'Locate image (waitfor): image_names=' + image_names )
		if use_center:
			for image in image_names:
				image_location = libcvautomation.waitForImage_location( get_display(), image,
										search_method, tolerance, timeout )
				location_array += [image, image_location]
		else:
			for image in image_names:
				image_location = libcvautomation.waitForImage_location_center( get_display(), image,
										search_method, tolerance, timeout )
				location_array += [image, image_location]
		
		return location_array
	else:
		#Display not open, but return the same type
		return {}

## \file libcvautomation_funcs.py
# \brief Libcvautomation wrapper for python
# \details This source file is designed to give high-level access to libcvautomation using Python. It was modeled after the Bash wrapper, but allows for access to all the extra features of Python.
# \author Bradlee Speice
