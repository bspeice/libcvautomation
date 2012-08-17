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

## \file libcvautomation_funcs.py
# \brief Libcvautomation wrapper for python
# \details This source file is designed to give high-level access to libcvautomation using Python. It was modeled after the Bash wrapper, but allows for access to all the extra features of Python.
# \author Bradlee Speice

## \package libcvautomation_funcs
# \brief Namespace to contain all of the features needed to use the libcvautomation_funcs wrapper

#-------------------------------------------------------------------------------
#  Import the libcvautomation library - this should have already been installed
#-------------------------------------------------------------------------------
import libcvautomation

#-------------------------------------------------------------------------------
#  Set up the logging options
#-------------------------------------------------------------------------------

_use_frame_trace=None

try:
	from sys import _current_frames #For getting the function that called us
	_use_frame_trace = True
except:
	_use_frame_trace = False

import time

def _get_caller():
	if _use_frame_trace:
		current_frame = sys._current_frames().values()[0] #Current frame
		caller_frame = current_frame.f_back.f_back #Go back two frames to make sure
												   #we don't get the name of the function that just called us.

		caller_name = caller_frame.f_globals['__name__'] #And get the name
		return caller_name
	else:
		return '[frame trace disabled]'

outfile = '/dev/null'
def _log_output( message ):
	global outfile #Make sure we use the global outfile,
				   #that people can change it if need be

	#with open(outfile, 'a') as outfile_handle
	outfile_handle = open(outfile, 'a')
	#Logfile format:
	# <hour>:<minute>:<second> <function_name>: <message>
	outfile_handle.write(time.strftime('%I:%M:%S '))
	outfile_handle.write(_get_caller() + ' ')
	outfile_handle.write(message)
	outfile_handle.write('\n')


#-------------------------------------------------------------------------------
#  Set up the Xlib handler functions
#-------------------------------------------------------------------------------

X11_display=None #NULL

def _check_display():
	global X11_display

	if X11_display is None:
		_log_output( 'Trying to call ' + _get_caller() + ' with no open display!' )
		return False
	else:
		return True

def _get_display(): #Intended to be unsafe (and a bit faster)-
				   #all wrapper functions should use check_display() explicitly
	global X11_display
	return X11_display

#-------------------------------------------------------------------------------
#  The following two functions are intended to be used on the front-end
#-------------------------------------------------------------------------------

## \brief Open a display for use in the libcvautomation_funcs
# \details This opens a display that will be used for every other function in libcvautomation_funcs.py. If you need to open a different display, use \ref libcvautomation_funcs::close_display() and then open the new display that you want.
# \param display_name The name of the display to open. The default is to open the first available display, which may not specifically be \c :0.
# \warning You \em must use this function to open a display before any other functions can be used.
# \returns Return \c True if the display was successfully opened, \c False otherwise
def open_display( display_name='' ):
	global X11_display
	X11_display = libcvautomation.cvaOpenDisplay( display_name )
	if X11_display is None:
		return False
	else:
		_log_output('Opened display with name: ' + display_name )
		return True

## \brief Close a display currently in use by libcvautomation_funcs
# \details This closes the currently open display. All functions used after this will fail unless you open another display. Use \ref libcvautomation_funcs::open_display() to open the new display.
# \returns None
def close_display():
	global X11_display
	if X11_display is None:
		_log_output('Trying to close a display that has already been closed.' )
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
_mouse_button_default=1 #Left click
_libcvautomation_error_location = libcvautomation.cvaPoint
_libcvautomation_error_location.x = _libcvautomation_error_location.y = -1

#-------------------------------------------------------------------------------
#  Begin the actual wrapper functions
#-------------------------------------------------------------------------------

## \brief Press a mouse button down
# \param mouse_button The number of the mouse button to press
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def mouse_down( mouse_button = _mouse_button_default ):
	if _check_display():
		_log_output( 'Mouse button down: ' + mouse_button )
		libcvautomation.xte_mouseDown(_get_display(), mouse_button )
		return True
	else:
		#Display not open
		return False

## \brief Release a mouse button
# \param mouse_button The number of the mouse button to release
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def mouse_up( mouse_button = _mouse_button_default ):
	if _check_display():
		_log_output( 'Mouse button up: ' + mouse_button )
		libcvautomation.xte_mouseUp(_get_display(), mouse_button )

		return True
	else:
		#Display not open
		return False

## \brief Press and release a mouse button
# \param mouse_button The number of the mouse button to click
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def mouse_click( mouse_button = _mouse_button_default ):
	if _check_display():
		_log_output( 'Mouse button click: ' + mouse_button )
		libcvautomation.xte_clickMouse(_get_display(), mouse_button )
		return True
	else:
		#Display not open
		return False

## \brief Click a mouse button at an absolute location
# \details Move the mouse to a location given by an x and y coordinate before clicking
# \param x_coord The X-coordinate to move the mouse to
# \param y_coord The Y-coordinate to move the mouse to
# \param mouse_button The mouse button to click after moving
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def mouse_click_xy( x_coord, y_coord, mouse_button = _mouse_button_default ):
	if _check_display():
		_log_output( 'Mouse button xy click: x=' + str(x_coord) + ' y=' + str(y_coord) + ' mouse_button=' + mouse_button )
		current_location = libcvautomation.xte_mouseLocation(_get_display() )
		x_increment = x_coord - current_location.x
		y_increment = y_coord - current_location.y

		libcvautomation.xte_hoverMouseRXY(_get_display(), x_increment, y_increment )
		libcvautomation.xte_clickMouse(_get_display(), mouse_button )

		return True
	else:
		#Display not open
		return False

## \brief Click a mouse button at a relative location
# \details Move the mouse horizontally and vertically by an increment, and then click the mouse
# \param x_inc The increment to move the mouse horizontally
# \note A positive increment moves the mouse right, a negative increment moves the mouse left
# \param y_inc The increment to move the mouse vertically
# \note A positive increment moves the mouse down, a negative increment moves the mouse up
# \param mouse_button The mouse button to click after moving
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def mouse_click_rxy( x_inc, y_inc, mouse_button = _mouse_button_default ):
	if _check_display():
		_log_output( 'Mouse button rxy click: x=' + str(x_inc) + ' y=' + str(y_inc) + ' mouse_button=' + mouse_button )
		libcvautomation.xte_hoverMouseRXY(_get_display(), x_inc, y_inc )
		libcvautomation.xte_clickMouse(_get_display(), mouse_button )

		return True
	else:
		#Display not open
		return False

## \brief Click a mouse button on an image inside the root X11 window
# \details For each image in \c image_names, search for it inside the root X11 window. Return once a match has been found, or the timeout value has been exceeded
# \param image_names List of image names to search for
# \param search_method The search method to use when finding each \c image. See \ref libcvautomation_search_methods for more information on how to use the search methods.
# \param tolerance The tolerance to use when finding each \c image. See \ref libcvautomation_search_methods for more information on how to use tolerance.
# \param timeout Wait for \c timeout seconds before giving up the search for \c image_names in the root X11 window.
# \note \c use_wait must be set to \c True for this parameter to have any effect
# \param mouse_button The mouse button to click after finding an image
# \param use_wait Set to \c True to make this function wait \c timeout seconds before giving up finding an image.
# \note If set to \c False, this function will go through the list of \c image_names once before giving up.
# \returns Return \c False if the X11 display was not opened before execution or there were no images found, and \c True otherwise
def mouse_click_image( image_names, search_method = _search_method_default,
						tolerance = _tolerance_default, timeout = _timeout_default,
						mouse_button = _mouse_button_default, use_wait = True):
	if _check_display():
		_log_output( 'Mouse button click on image: Images=' + image_names + 
				' search_method=' + search_method + ' tolerance=' + tolerance +
				' timeout=' + _timeout_default + ' mouse_button=' +
				' use_wait=' + use_wait + ' use_center=' + use_center)

		if use_wait:
			#Loop through all images 'timeout' times, and click on the first match
			loop_check = 0
			while loop_check < timeout:
				for image in image_names:
					if use_center:
						image_location = libcvautomation.xte_clickMouseImage_location_center(_get_display(),
											image, mouse_button, search_method, tolerance )
					else:
						image_location = libcvautomation.xte_clickMouseImage_location(_get_display(),
											image, mouse_button, search_method, tolerance )

					if image_location != _libcvautomation_error_location:
						#We've found our image, break out of the for loop and while loop
						return True

				loop_check += 1
		else:
			#Just cycle through the images once
			for image in image_names:
				if use_center:
					image_location = libcvautomation.xte_clickMouseImage_location_center(_get_display(),
											image, mouse_button, search_method, tolerance )
				else:
					image_location = libcvautomation.xte_clickMouseImage_location(_get_display(),
											image, mouse_button, search_method, tolerance )

				if image_location != _libcvautomation_error_location:
					#We've found our image, break out of the for loop
					return True
	else:
		#Display not open or no image found
		return False


## \brief Press and release a mouse button twice
# \param mouse_button The number of the mouse button to click twice
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def mouse_doubleclick( mouse_button = _mouse_button_default ):
	if _check_display():
		_log_output( 'Mouse button doubleclick: ' + mouse_button )
		libcvautomation.xte_clickMouse(_get_display(), mouse_button )

		return True
	else:
		#Display not open
		return False


## \brief Click a mouse button twice at an absolute location
# \details Move the mouse to a location given by an x and y coordinate before clicking twice
# \param x_coord The X-coordinate to move the mouse to
# \param y_coord The Y-coordinate to move the mouse to
# \param mouse_button The mouse button to click after moving
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def mouse_doubleclick_xy( x_coord, y_coord, mouse_button = _mouse_button_default ):
	if _check_display():
		_log_output( 'Mouse button xy doubleclick: x=' + str(x_coord) + ' y=' + str(y_coord) + ' mouse_button=' + mouse_button )
		current_location = libcvautomation.xte_mouseLocation(_get_display() )
		x_increment = x_coord - current_location.x
		y_increment = y_coord - current_location.y

		libcvautomation.xte_hoverMouseRXY(_get_display(), x_increment, y_increment )
		libcvautomation.xte_clickMouse(_get_display(), mouse_button )
		libcvautomation.xte_clickMouse(_get_display(), mouse_button )

		return True
	else:
		#Display not open
		return False

## \brief Click a mouse button twice at a relative location
# \details Move the mouse horizontally and vertically by an increment, and then click the mouse twice
# \param x_inc The increment to move the mouse horizontally
# \note A positive increment moves the mouse right, a negative increment moves the mouse left
# \param y_inc The increment to move the mouse vertically
# \note A positive increment moves the mouse down, a negative increment moves the mouse up
# \param mouse_button The mouse button to click after moving
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def mouse_doubleclick_rxy( x_inc, y_inc, mouse_button = _mouse_button_default ):
	if _check_display():
		_log_output( 'Mouse button relative xy doubleclick: x=' + str(x_inc) + ' y=' + str(y_inc) + ' mouse_button=' + mouse_button )
		libcvautomation.xte_hoverMouseRXY(_get_display(), x_inc, y_inc )
		libcvautomation.xte_clickMouse(_get_display(), mouse_button )
		libcvautomation.xte_clickMouse(_get_display(), mouse_button )

		return True
	else:
		#Display not open
		return False

## \brief Click a mouse button twice on an image inside the root X11 window
# \details For each image in \c image_names, search for it inside the root X11 window. Return once a match has been found, or the timeout value has been exceeded
# \param image_names List of image names to search for
# \param search_method The search method to use when finding each \c image. See \ref libcvautomation_search_methods for more information on how to use the search methods.
# \param tolerance The tolerance to use when finding each \c image. See \ref libcvautomation_search_methods for more information on how to use tolerance.
# \param timeout Wait for \c timeout seconds before giving up the search for \c image_names in the root X11 window.
# \note \c use_wait must be set to \c True for this parameter to have any effect
# \param mouse_button The mouse button to click after finding an image
# \param use_wait Set to \c True to make this function wait \c timeout seconds before giving up finding an image.
# \param use_center Set to \c True to make this function return the center coordinate of the matched image. Setting to \c False will use the top-left corner.
# \note If set to \c False, this function will go through the list of \c image_names once before giving up.
# \returns Return \c False if the X11 display was not opened before execution or no images were found, and \c True otherwise
def mouse_doubleclick_image( image_names, search_method = _search_method_default,
						tolerance = _tolerance_default, timeout = _timeout_default,
						mouse_button = _mouse_button_default, use_wait = True,
						use_center = True ):
	if _check_display():
		_log_output( 'Mouse button doubleclick on image: Images=' + image_names + 
				' search_method=' + search_method + ' tolerance=' + tolerance +
				' timeout=' + _timeout_default + ' mouse_button=' +
				' use_wait=' + use_wait + ' use_center=' + use_center)

		if use_wait:
			#Loop through all images 'timeout' times, and click on the first match
			loop_check = 0
			while loop_check < timeout:
				for image in image_names:
					if use_center:
						image_location = libcvautomation.xte_clickMouseImage_location_center(_get_display(),
											image, mouse_button, search_method, tolerance )
					else:
						image_location = libcvautomation.xte_clickMouseImage_location(_get_display(),
											image, mouse_button, search_method, tolerance )

					if image_location != _libcvautomation_error_location:
						#Make sure to click twice once we've found the image
						#Technically assumes that the system mouse timeout is less than
						#the time it takes to do two boolean compares - I think this is pretty safe
						libcvautomation.xte_clickMouse(_get_display(), mouse_button )
						#We've found our image, break out of the for loop and while loop
						return True

				loop_check += 1
		else:
			#Just cycle through the images once
			for image in image_names:
				if use_center:
					image_location = libcvautomation.xte_clickMouseImage_location_center(_get_display(),
											image, mouse_button, search_method, tolerance )
				else:
					image_location = libcvautomation.xte_clickMouseImage_location(_get_display(),
											image, mouse_button, search_method, tolerance )

				if image_location != _libcvautomation_error_location:
					#We've found our image, break out of the for loop
					return True

	else:
		#Display not open, or no image found
		return False

## \brief Move the mouse to a given coordinate, and leave it there
# \param x_coord The X-coordinate to move the mouse to
# \param y_coord The Y-coordinate to move the mouse to
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def mouse_hover_xy( x_coord, y_coord ):
	if _check_display():
		_log_output( 'Mouse button hover xy: x=' + str(x_coord) + ' y=' + str(y_coord) + ' mouse_button=' + mouse_button )
		current_location = libcvautomation.xte_mouseLocation(_get_display() )
		x_increment = x_coord - current_location.x
		y_increment = y_coord - current_location.y

		libcvautomation.xte_hoverMouseRXY(_get_display(), x_increment, y_increment )

		return True
	else:
		#Display not open
		return False

## \brief Move the mouse by a given increment, and leave it there
# \param x_inc The increment to move the mouse horizontally
# \note A positive increment moves the mouse right, a negative increment moves the mouse left
# \param y_inc The increment to move the mouse vertically
# \note A positive increment moves the mouse down, a negative increment moves the mouse up
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def mouse_hover_rxy( x_inc, y_inc ):
	if _check_display():
		_log_output( 'Mouse button hover relative xy: x=' + str(x_inc) + ' y=' + str(y_inc) )
		libcvautomation.xte_hoverMouseRXY(_get_display(), x_inc, y_inc )

		return True
	else:
		#Display not open
		return False

## \brief Move the mouse to an image inside the root X11 window
# \details For each image in \c image_names, search for it inside the root X11 window. Return once a match has been found, or the timeout value has been exceeded
# \param image_names List of image names to search for
# \param search_method The search method to use when finding each \c image. See \ref libcvautomation_search_methods for more information on how to use the search methods.
# \param tolerance The tolerance to use when finding each \c image. See \ref libcvautomation_search_methods for more information on how to use tolerance.
# \param timeout Wait for \c timeout seconds before giving up the search for \c image_names in the root X11 window.
# \note \c use_wait must be set to \c True for this parameter to have any effect
# \param use_wait Set to \c True to make this function wait \c timeout seconds before giving up finding an image.
# \note If set to \c False, this function will go through the list of \c image_names once before giving up.
# \param use_center Set to \c True to make this function return the center coordinate of the matched image. Setting to \c False will use the top-left corner.
# \returns Return \c False if the X11 display was not opened before execution or no images were found, and \c True otherwise
def mouse_hover_image( image_names, search_method = _search_method_default,
						tolerance = _tolerance_default, timeout = _timeout_default,
						use_wait = True, use_center = True ):
	if _check_display():
		_log_output( 'Mouse button click on image: Images=' + image_names + 
				' search_method=' + search_method + ' tolerance=' + tolerance +
				' timeout=' + _timeout_default + ' use_wait=' + use_wait + 
				' use_center=' + use_center)

		if use_wait:
			#Loop through all images 'timeout' times, and click on the first match
			loop_check = 0
			while loop_check < timeout:
				for image in image_names:
					if use_center:
						image_location = libcvautomation.xte_hoverMouseImage_location_center(_get_display(),
											image, mouse_button, search_method, tolerance )
					else:
						image_location = libcvautomation.xte_hoverMouseImage_location(_get_display(),
											image, mouse_button, search_method, tolerance )

					if image_location != _libcvautomation_error_location:
						#We've found our image, break out of the for loop and while loop
						return True

				loop_check += 1
		else:
			#Just cycle through the images once
			for image in image_names:
				if use_center:
					image_location = libcvautomation.xte_hoverMouseImage_location_center(_get_display(),
											image, mouse_button, search_method, tolerance )
				else:
					image_location = libcvautomation.xte_hoverMouseImage_location(_get_display(),
											image, mouse_button, search_method, tolerance )

				if image_location != _libcvautomation_error_location:
					#We've found our image, break out of the for loop
					return True
	else:
		#Display not open or no image found
		return False

## \brief Jiggle the mouse in place
# \details Move the mouse right and down 1 pixel, and back. Useful for activating menu entries, etc.
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def mouse_jiggle():
	"""Jiggle the mouse in place"""
	if _check_display():
		_log_output( 'Mouse button jiggle' )
		libcvautomation.xte_mouseJiggle(_get_display() )
		return True
	else:
		#Display not open
		return False

## \brief Scroll the mouse wheel up
# \details This is the same as pressing mouse button 4
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def mouse_scroll_up():
	if _check_display():
		_log_output( 'Mouse scroll up' )
		libcvautomation.xte_mouseScrollUp(_get_display() )
		return True
	else:
		#Display not open
		return False

## \brief Scroll the mouse wheel down
# \details This is the same as pressing mouse button 5
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def mouse_scroll_down():
	if _check_display():
		_log_output( 'Mouse scroll down' )
		libcvautomation.xte_mouseScrollDown(_get_display() )
		return True
	else:
		#Display not open
		return False

## \brief Drag and drop one image to another
# \param drag_image The image to drag from
# \param drag_to The image giving the location to drag to
# \param use_center Drag and drop the image using the center of the image as the location where the mouse will click and drag to
# \returns Return \c False if the X11 display was not opened before execution or an image was not found, and \c True otherwise
def mouse_drag_n_drop( drag_image, drag_to, use_center = True ):
	if _check_display():
		_log_output( 'Mouse drag and drop: dragging from=' + drag_image +
			' dragging to=' + drag_to )
		successful_hover = mouse_hover_image( drag_image, use_center=use_center )
		if successful_hover:
			mouse_down( mouse_button=1 )
			successful_hover = mouse_hover_image( drag_to )
			mouse_up( mouse_button=1 )

		#Return True if both hovers are successful, False otherwise
		return successful_hover
	else:
		#Display not open
		return False

## \brief Enter a string of text on the keyboard
# \details This function will simulate pressing the keys exactly as they are entered - unlike libcvautomation_funcs::key_down, libcvautomation_funcs::key_up, and libcvautomation_funcs::key_click, this function will display exactly what you entered: A string of \c '!' will produce a \c ! as a keypress.
# \param string The string of text to enter on the keyboard
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def key_string( string ):
	if _check_display():
		_log_output( 'Key string enter: string=' + string )
		libcvautomation.xte_clickKeyStr(_get_display(), string )
		return True
	else:
		#Display not open
		return False

## \brief Press a key down on the keyboard, and leave it down
# \param key_name The name of the key to press down. Unlike libcvautomation_funcs::key_string, this command will press a single key corresponding to the string you give it - for example, \c 'a', \c 'b', or something fancy like \c 'space'.
# \note See \ref xtest_key_strings for a full list of accepted key strings.
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def key_down( key_name ):
	if _check_display():
		_log_output( 'Key button down: key_name=' + key_name )
		libcvautomation.xte_keyDown(_get_display(), key_name )
		return True
	else:
		#Display not open
		return False

## \brief Release a key on the keyboard
# \param key_name The name of the key to release. Unlike libcvautomation_funcs::key_string, this command will press a single key corresponding to the string you give it - for example, \c 'a', \c 'b', or something fancy like \c 'space'.
# \note See \ref xtest_key_strings for a full list of accepted key strings.
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def key_up( key_name ):
	if _check_display():
		_log_output( 'Key button up: key_name=' + key_name )
		libcvautomation.xte_keyUp(_get_display(), key_name )
		return True
	else:
		#Display not open
		return False

## \brief Press and release a key on the keyboard
# \param key_name The name of the key to click. Unlike libcvautomation_funcs::key_string, this command will press a single key corresponding to the string you give it - for example, \c 'a', \c 'b', or something fancy like \c 'space'.
# \note See \ref xtest_key_strings for a full list of accepted key strings.
# \returns Return \c False if the X11 display was not opened before execution, and \c True otherwise
def key_click( key_name ):
	if _check_display():
		_log_output( 'Key button click: key_name=' + key_name )
		libcvautomation.xte_keyDown(_get_display(), key_name )
		return True
	else:
		#Display not open
		return False

## \brief Get the location of an image on the screen
# \param image_names List of image names to search for in the root X11 window
# \param search_method The search method to use when matching images. See \ref libcvautomation_search_methods for more information on using the \c search_method parameter
# \param tolerance The tolerance to use when matching images. See \ref libcvautomation_search_methods for more informatino on using the \c tolerance parameter
# \param use_center Set to \c True to return the center coordinate of an image. Set to \c False to use the top-left corner of an image
# \warning Unlike libcvautomation_funcs::wait_for(), this method will not wait for an image to show up before looking for it.
# \returns A dictionary pairing each image name with a cvaPoint class indicating the location it was found at (a point of (-1, -1) indicates the image was not found), or an empty dictionary if the X11 display was not opened before execution.
def image_location( image_names, search_method = _search_method_default,
						tolerance = _tolerance_default,	use_center = True ):
	if _check_display():
		location_array = {}
		_log_output( 'Locate image (image_location): image_names=' + image_names )
		if use_center:
			for image in image_names:
				image_location = libcvautomation.matchSubImage_X11_center(_get_display(), image,
									search_method, tolerance )
				location_array += [image, image_location]
		else:
			for image in image_names:
				image_location = libcvautomation.matchSubImage_X11(_get_display(), image,
									search_method, tolerance )
				location_array += [image, image_location]

		return location_array
	else:
		#Display not open, but return the same type
		return {}

## \brief Get the location of an image on the screen, waiting for it to show up
# \param image_names List of image names to search for in the root X11 window
# \param search_method The search method to use when matching images. See \ref libcvautomation_search_methods for more information on using the \c search_method parameter
# \param tolerance The tolerance to use when matching images. See \ref libcvautomation_search_methods for more informatino on using the \c tolerance parameter
# \param timeout The time (in seconds) to wait when searching for an image on the root X11 window
# \param use_center Set to \c True to return the center coordinate of an image. Set to \c False to use the top-left corner of an image
# \returns A dictionary pairing each image name with a cvaPoint class indicating the location it was found at (a point of (-1, -1) indicates the image was not found), or an empty dictionary if the X11 display was not opened before execution.
def wait_for( image_names, search_method = _search_method_default,
				tolerance = _tolerance_default, timeout = _timeout_default,
				use_center = True ):
	if _check_display():
		location_array = {}
		_log_output( 'Locate image (wait_for): image_names=' + image_names )
		if use_center:
			for image in image_names:
				image_location = libcvautomation.waitForImage_location(_get_display(), image,
										search_method, tolerance, timeout )
				location_array += [image, image_location]
		else:
			for image in image_names:
				image_location = libcvautomation.waitForImage_location_center(_get_display(), image,
										search_method, tolerance, timeout )
				location_array += [image, image_location]
		
		return location_array
	else:
		#Display not open, but return the same type
		return {}

## \brief Execute a libcvautomation command based on a string
# \details This is a handler for the xte_commandString() function. 
# \note Not all commands need all the parameters specified. See \ref xtest_command_strings for more information on how to use this function.
# \param string The command string to execute
# \param mouse_button The mouse button to click, if applicable
# \param search_method The search method to use, if applicable. See \ref libcvautomation_search_methods for more information on how to use the \c search_method parameter
# \param tolerance The tolerance to use, if applicable. See \ref libcvautomation_search_methods for more information on how to use the \c tolerance parameter
# \param timeout The timeout (in seconds) to use, if applicable
# \returns A cvaPoint class with the following points:<br>(0, 0) or up indicates a success.<br>(-1, -1) indicates either the command was not successful, or that the command was not recognized.<br>(-2, -2) indicates that the command did not need to return anything - For example, commands like \ref mousejiggle don't normally return a value.
def command_string( string, mouse_button = _mouse_button_default, search_method = _search_method_default,
					tolerance = _tolerance_default, timeout = _timeout_default):

	#The return for this function bears a bit of talking about:
	#	A return of (0, 0) or up is a success
	#	A return of (-1, -1) is an error that either the command wasn't successful, or the command wasn't recognized
	#	A return of (-2, -2) indicates that the command didn't need to return anything -
	#		This helps differentiate between errors and functions like key_click that
	#		don't really use a point

	if _check_display():
		_log_output( 'Command string: string=' + string + ' search_method=' + str(search_method) +
				' tolerance=' + str(tolerance) + ' timeout=' + str(timeout) )
		result_point = libcvautomation.xte_commandString(_get_display(), string,
							mouse_button, search_method,
							tolerance, timeout )
		return result_point
	else:
		#Display not open, return an error point
		return _libcvautomation_error_location
