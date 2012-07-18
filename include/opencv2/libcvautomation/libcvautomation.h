/*
 * =====================================================================================
 *
 *       Filename:  libcvautomation.h
 *
 *    Description:  Include wrapper for libcvautomation subsections
 *
 *        Created:  06/21/2012 12:20:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Bradlee Speice (), bspeice.nc@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef LIBCVAUTOMATION_H
#define LIBCVAUTOMATION_H

#define LIBCVAUTOMATION_VERSION "1.2"
#define LIBCVAUTOMATION_BUGREPORT "bspeice@uncc.edu"

/* C includes */
#include <stdio.h>
#include <string.h>

/* OpenCV2 includes - some filenames are different
 * from the OpenCV1 counterparts */
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc_c.h>


/* X11 includes */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

/* Define a basic structure to help us with using multiple-picture arguments
 * Yes, it's a hackish implementation, nobody said you had to use this one. */
typedef struct {
	/* Use one or the other of fileName or cvaImage - cvaImage takes priority */
	IplImage *cvaImage;
	char *fileName;

	CvPoint resultPoint;
	int searchMethod;
	int tolerance;

} cvautomationList;

/* Define another basic structure for points */
typedef struct {
	int x, y;
} cvaPoint;

/* Project component includes */
/* The includes come here to make sure all function prototypes have access
 * to the cvautomationList struct */
#include <libcvautomation/libcvautomation-opencv.h>
#include <libcvautomation/libcvautomation-xlib.h>
#include <libcvautomation/libcvautomation-xtest.h>

#endif /* LIBCVAUTOMATION_H */
/* Doxygen information */
/** \file libcvautomation.h
 * \brief The top-level include for all projects involving libcvautomation
 * \details This source file includes all other files needed for libcvautomation projects, and also defines the cvautomationList and cvaPoint structs to be used among libcvautomation functions. Please note that while the opencv2 version is being documented, there is no actual difference in usage for opencv version 1.
 * \author Bradlee Speice
 * \date 6/21/2012
 */

/** \mainpage Libcvautomation
 * \author Bradlee Speice <<a href="mailto:bspeice@uncc.edu">bspeice@uncc.edu</a>>
 * \date 7/11/2012
 * \section intro Introduction
 * Welcome to Libcvautomation!
 * Libcvautomation is a GUI automation and testing tool based on image recognition and response. This program was designed as a direct replacement for <a href="http://sikuli.org">Sikuli</a> and <a href="https://wiki.ubuntu.com/Xpresser">Xpresser</a>. I was having incredible difficulty getting either of these solutions to work - Sikuli would crash whenever I tried to take a screenshot, and Xpresser was both too new for our Prominent North American Enterprise Linux systems, but also didn't work or \c import correctly. I really liked the way each of these programs approached GUI automation, but they simply didn't work. Additionally, I wanted to create a simple solution - it does what you want it to, and that's it.
 * \section how_it_works How Libcvautomation Works
 * Libcvautomation represents two software products coming together - <a href="http://opencv.willowgarage.com/wiki/">OpenCV</a> and the <a href="http://www.x.org/docs/Xext/xtest.pdf">XTest extension</a> to the X11 server. OpenCV is used for image recognition, and XTest is used to actually drive the X server. You can dig into \ref libcvautomation-xtest.h to get an idea of what all this library is capable of. <br>
 * Basically what happens is that for whenever you need to do image recognition, OpenCV is used to find the images, and XTest is used to generate any events needed. Libcvautomation is mostly a wrapper to integrate both of these products, but also adds some functions like matchSubImage_X11() that allow you to match an image against the X11 root window in place. This means no more <tt>'xwd | convert "<out_name>"'</tt>.
 * \section main_using Using Libcvautomation And Writing Application Tests
 * So how does one go about using libcvautomation? <br>
 * I'm so glad you asked! I've provided a few reference programs - \c cva-match and \c cva-input - that can be used to demonstrate most of libcvautomation's capabilities. I've even provided a BASH wrapper to make it incredibly easy to use BASH with libcvautomation as well (requires that cva-match and cva-input are installed). Python bindings are on their way too. <br>
 * Finally, if you want to know how to write your own application tests, please see \ref writing_app_tests for more information on that. I've provided code to give you a basic idea of how they work.
 * \section questions Questions? Comments? Concerns?
 * Please send any feedback to <<a href="mailto:bspeice@uncc.edu">bspeice@uncc.edu</a>>. Pull requests can be submitted to <a href="https://github.com/DjBushido/cvautomation">my github repository</a>.*/

/** \page writing_app_tests Writing Application Tests
 * \author Bradlee Speice <<a href="mailto:bspeice@uncc.edu">bspeice@uncc.edu</a>>
 * \date 7/11/2012
 * \section audience Audience
 * <ul>
 * <li>This document was written for people with some intermediate knowledge of BASH.
 * <li>Screenshot experience is required - being able to create screenshots of windows using <a href="http://www.gimp.org/">GIMP</a>, the \c import command from <a href="http://www.imagemagick.org/script/index.php">ImageMagick</a>, or something similar. <br>
 * <li>Required for working with libcvautomation internals (not needed strictly for writing application testing):
 * 		<ul>
 * 		<li>Intermediate-level C knowledge required for interfacing with libcvautomation. There isn't much complicated going on with libcvautomation itself, but you need to know to use cvaOpenDisplay() for grabbing a display and then cvaCloseDisplay() for closing it later for example.
 * 		<li>C++ is available, but currently only as <tt>extern "C"</tt> style bindings.
 * 		<li>Python bindings are in progress as of time-of-writing
 * 		</ul>
 * </ul>
 *
 * \section purpose Purpose
 * <ul>
 * <li>This document is intended to outline the libcvautomation testing library for GUI applications and its two reference programs \c cva-match and \c cva-input
 * <li>These programs allow you to automate mouse and keyboard events in response to what appears on screen - for example, clicking a button based on an image of that button on screen.
 * </ul>
 *
 * \section using Using Libcvautomation
 * <ul>
 * <li>Since libcvautomation is a shared-object library intended to bundle a lot of functionality in one area, we must use external programs to agin access to the functions of libcvautomation.
 * <li>Two reference programs have been included to make this easy - \c cva-match and \c cva-input
 * <li>The reference programs are fairly full-featured, and expose most of libcvautomation:
 * 		<ul>
 * 		<li>\c cva-match allows you to match multiple image files against a root image providing very fine control over how specific the match is
 * 		<li>\c cva-input allows you to drive the X11 server using the XTest extension - for example, clicking on a button from image, clicking a key on the keyboard, and more.
 * 		</ul>
 * <li>These two programs should implement all functionality needed for GUI automation. Please contact <a href="mailto:bspeice@uncc.edu">bspeice@uncc.edu</a> if you have suggestions for extra functionality, patches, comments, etc.
 * <li>Finally, if you want to write your own programs using libcvautomation, the headers are located on your system. Use:
 * \code #include <libcvautomation/libcvautomation.h> \endcode
 * to include all necessary header files. See the "Files" tab above to get an idea of what functionality exists.
 * \note Intermediate C or C++ knowledge is required for programming with libcvautomation. C++ is currently only supported through <tt>extern "C"</tt>, and full C++ bindings are not currently planned. Libcvautomation itself is incredibly simple, but interfaces with a few API's (Xlib, libcv) that it is helpful to have an idea of how to use.
 *
 * \section testing Application Testing
 * Now we get into the good stuff. The basic process for application testing is as follows:
 * <ul>
 * <li>Create a sequence of screenshots for all mouse-clicks
 * <li>Create a testing wrapper in BASH for automating the application
 * <li>Test the wrapper and tune any necessary options
 * </ul>
 * \subsection screenshot_sequence Creating the Screenshot Sequence
 * <ul>
 * <li>This process creates a set of screenshots by which libcvautomation can drive the X11 server
 * <li>The process is simple - create a screenshot of all buttons you would like to click in an application test, or location where you would like to move the mouse, etc.
 * <li>This can be accomplished a number of different ways - using GIMP, the \c import command, or any other screenshot program. Additionally, libcvautomation will support any image format that OpenCV does. At the time of writing, these are:
 * 		<ul>
 * 		<li>Windows bitmaps - <tt>*.bmp</tt>, <tt>*.dib</tt>
 * 		<li>JPEG files - <tt>*.jpeg</tt>, <tt>*.jpg</tt>, <tt>*.jpe</tt>
 * 		<li>JPEG 2000 files - <tt>*.jp2</tt>
 * 		<li>Portable Network Graphics - <tt>*.png</tt>
 * 		<li>Portable image format - <tt>*.pbm</tt>, <tt>*.pgm</tt>, <tt>*.ppm</tt>
 * 		<li>Sun rasters - <tt>*.sr</tt>, <tt>*.ras</tt>
 * 		<li>TIFF files - <tt>*.tiff</tt>, <tt>*.tif</tt>
 * 		</ul>
 * <br>
 * <li>Some tips on creating screenshots:
 *		<ul>
 *		<li>Use as distinct an image as possible in a screenshot. For example, the following images look very similar, but can do very different things:
 *	 	\image html print-printbutton1.png 
 *	 	<br>
 *	 	\image html print-helpbutton.png
 *		<ul>
 *			<li>The large amount of grey-space in each of the images can be very confusing. While the text itself is different, the overwhelming amount of grey space can result in a false positive. Limiting the space of the screenshot can be useful:
 *			\image html print-printbutton2.png
 *			<br>
 *			\image html print-helpbutton.png
 *			<li>Limiting the button size in this case helps the program identify what button you want to click, but in general you want to include as much detail as possible.
 *		</ul>
 *		<br>
 *		<li>Be careful of where an image may appear multiple times in a screenshot. For example, a "Help" button on a dialog may get confused with the "Help" menu at the top of the screen.
 * </ul>
 *
 * \subsection testing_wrapper Create a Testing Wrapper
 * <ul>
 * <li>This is where the BASH knowledge comes into play. We are going to write a script that will run your application test, to make sure that the GUI is functioning correctly.
 * <li>The following is the (strongly) recommended process, but is not strictly necessary to follow this. The way I'm going to explain this is by giving an example test I wrote, and explain what is going on:
 * \code
 * #!/bin/bash
 * #This is an application test involving libcvautomation and libreoffice
 * . /usr/local/etc/libcvautomation_funcs
 *
 * #Changing any wrapper parameters should go here
 *
 *
 * start_libreoffice_writer ()
 * {
 *	click_i "screens/gnome-1_menu.png" "screens/kde-1_menu.png" && sleep 1
 *	click_i "screens/gnome-2_officeMenu.png" "screens/kde-2_officeMenu.png" && sleep 1
 *	hover_i "screens/gnome-3_LibreOfficeWriter.png" "screens/kde-3_LibreOfficeWriter.png"
 *	jiggle_mouse
 *	click
 *	sleep 30
 * }
 *
 * close_libreoffice_writer()
 * {
 * 	click_i "screens/gnome-4_fileMenu.png" "screens/kde-4_fileMenu.png" && sleep 1
 * 	click_i "screens/gnome-5_fileExit.png" "screens/kde-5_fileExit.png" && sleep 1
 * 	click_i "screens/gnome-6_discard.png" "screens/kde-6_discard.png" && sleep 1
 * }
 *
 * start_libreoffice_writer
 * close_libreoffice_writer
 * \endcode
 * <br>
 * \code
 * #!/bin/bash
 * #This is an application test involving libcvautomation and libreoffice
 * . /usr/local/etc/libcvautomation_funcs
 * #Changing any wrapper parameters should go here
 * \endcode
 * <li>The purpose of these lines is just the standard BASH header. Additionally, we import a wrapper created for libcvautomation to make our job easier. Please note that this is the default directory for the wrapper, your installation may be different. Use the command <tt>locate libcvautomation_funcs</tt> to find it on your computer. The wrapper itself is a handful of macros used to make our job easy.
 * <li>Changing any wrapper parameters should go after sourcing the wrapper functions. See below on \ref testing_test_wrapper for more information.
 * <br><br>
 * \code
 * start_libreoffice_writer ()
 * {
 *	click_i "screens/gnome-1_menu.png" "screens/kde-1_menu.png" && sleep 1
 *	click_i "screens/gnome-2_officeMenu.png" "screens/kde-2_officeMenu.png" && sleep 1
 *	hover_i "screens/gnome-3_LibreOfficeWriter.png" "screens/kde-3_LibreOfficeWriter.png"
 *	jiggle_mouse
 *	click
 *	sleep 30
 * }
 * \endcode
 * <li>This is the actual body of work done by libcvautomation
 * <li>\c click_i is a function to click the mouse at an image - in this case, the gnome or kde menu.
 * 		<ul>
 *		<li>Because of how the cva-input program is designed, you can give it multiple images, and it will only select the one currently available. See \ref testing_test_wrapper for more information on how to use this (TOLERANCE specifically)
 * 		<li>By using the function \c click_i, we make things a bit more readable - the full command line is <tt>cva-input -s 'icmouseclick <filename>'</tt>
 * 		<li>See \ref wrapper_functions for a list of all functions available in the wrapper.
 * 		</ul>
 * <li>\c hover_i is a function to move the mouse to an image - in this case, move it over the LibreOffice menu item.
 * <li>Then we jiggle the mouse to make sure that the item activates, click, and wait for the program to start up.
 * <br><br>
 * \code
 * close_libreoffice_writer()
 * {
 * 	click_i "screens/gnome-4_fileMenu.png" "screens/kde-4_fileMenu.png" && sleep 1
 * 	click_i "screens/gnome-5_fileExit.png" "screens/kde-5_fileExit.png" && sleep 1
 * 	click_i "screens/gnome-6_discard.png" "screens/kde-6_discard.png" && sleep 1
 * }
 * \endcode
 * <li>Use the \c click_i function to close down LibreOffice writer - Find the "File" menu, click "Exit", and then make sure to discard all changes.
 * <br><br>
 * \code
 * start_libreoffice_writer
 * close_libreoffice_writer
 * \endcode
 * <li>Actually run the functions given.
 * <br><br>
 * <li>Please note that this is a fairly trivial example. The full list of commands available in the wrapper is given in \ref wrapper_functions
 * </ul>
 *
 * \subsection testing_test_wrapper Testing the Testing Wrapper
 * <ul>
 * <li>First things first, run through the testing wrapper to make sure that everything is O.K.
 * <li>If you need to, some things you can do to tune the application test are as follows:
 * 		<ul>
 * 		<li>Set the \c SEARCH_METHOD
 * 			<ul>
 * 			<li>This value adjusts how libcvautomation searches for sub-images. See \ref libcv_search_methods for more information on accepted values, and how each works.
 * 			</ul>
 * 		<li>Set the \c TOLERANCE
 * 			<ul>
 * 			<li>This value adjusts how strict libcvautomation is when trying to find a sub-image. See \ref libcv_search_methods for more information on how to control how libcvautomation searches for images.
 * 			</ul>
 * 		<li>Set \c USE_SANE_TOLERANCE
 * 			<ul>
 * 			<li>This value implements a more sane way of setting the tolerance value - Where normally the tolerance ranges from \c INT_MIN to \c INT_MAX, the sane tolerance accepts values of 1 - 100 (\f$ 1 \approx 0 \f$, and \f$ 100 \approx \c INT_MAX \f$)
 * 			<li>To enable sane tolerance, set: \code USE_SANE_TOLERANCE="<any_value>" \endcode
 * 			<li>To disable sane tolerance (the default) set: \code USE_SANE_TOLERANCE="" \endcode
 * 		<li>Set \c USE_CENTER
 * 			<ul>
 * 			<li>By default, the wrapper will use the center of an image as opposed to the upper-left corner to click on. To disable this behavior, set: \code USE_CENTER="" \endcode
 * 			<li>To set the behavior back to using center-based matching, set: \code USE_CENTER="<any_value>" \endcode
 * 			</ul>
 * 		<li>Set the \c OUTFILE and \c ERRFILE
 * 			<ul>
 * 			<li>The application wrapper logs a whole lot of information about what it does to make debugging easy. However, to make sure that you're not overwhelmed by the output, the wrapper also directs the output to <tt>/dev/null</tt> by default.
 * 			<li>To redirect the output of \c OUTFILE and \c ERRFILE, set them to any file you want. For example, the following code will create a temporary file for OUTFILE and ERRFILE, and notify you of what they are:
 * \code
 * OUTFILE=`mktemp`
 * ERRFILE=`mktemp`
 * echo "OUTFILE location: $OUTFILE"
 * echo "ERRFILE location: $ERRFILE"
 * \endcode
 *			</ul>
 *		</ul>
 *	<li>A full list of commands provided by the wrapper is available at \ref wrapper_functions
 *	</ul>
 *
 * \note These options are controlled using the testing script as demonstrated above. Any modifications to the following values should be done at the line: \code #Changing any wrapper parameters should go here \endcode
 * </ul>
 * \section wrapping_up Wrapping Up
 * <ul>
 * <li>At this point you should have all the information you need to write your own application tests. The libcvautomation library and reference programs were designed to be simple and powerful, but if you invest the time to learn them and some expert BASH scripting, you can do some very complex things. 
 * 		<ul>
 * 		<li>For example, integrating a <a href="http://testanything.org/wiki/index.php/Tap-functions">Test Anything Protocol</a> wrapper into your scripts as well.
 * 		</ul>
 * <li>If you have questions, comments, concerns, suggestions, or feedback in general, feel free to let me know at <a href="mailto:bspeice@uncc.edu">bspeice@uncc.edu</a>.
 * </ul>
 */
/** \page wrapper_functions Appendix of Wrapper Functions
 * \section appendix_click Click the mouse
 * \code click \endcode
 * Click the mouse where it is currently located
 * <br><br>
 *
 * \code click_xy <x-coordinate> <y-coordinate> \endcode
 * Click the mouse on an absolute point on screen
 * 	\note The actual process is to move the mouse to the given location, then click there.
 * <br><br>
 *
 * \code clickr_xy <x-increment> <y-increment> \endcode
 * Click the mouse on the screen relative to where the mouse is at
 *  \note The actual process is to move the mouse the given distance, then click there.
 *  \note Also, note that a positive \c x-increment moves the mouse to the right, and a positive \c y-increment moves the mouse down.
 * <br><br>
 *
 * \code click_i <filename> \endcode
 * Click the mouse on a screenshot from \c filename
 * 	\note This is affected by the \c CENTER, \c TOLERANCE, and \c SEARCH_METHOD variables. See \ref testing_test_wrapper for more information on these.
 * <br><br>
 *
 * \section appendix_move Move the mouse
 * \code hover_xy <x-coordinate> <y-increment> \endcode
 * Move the mouse to a location on screen using absolute positioning
 * <br><br>
 *
 * \code hoverr_xy <x-increment> <y-increment> \endcode
 * Move the mouse to a location on screen using relative positioning
 *  \note Note that a positive \c x-increment moves the mouse to the right, and a positive \c y-increment moves the mouse down.
 * <br><br>
 *
 * \code hover_i <filename> \endcode
 * Move the mouse to a location on screen based on screenshot
 * 	\note This is affected by the \c CENTER, \c TOLERANCE, and \c SEARCH_METHOD variables. See \ref testing_test_wrapper for more information on these.
 * <br><br>
 *
 * \code mouse_scrollu \endcode
 * Scroll the mouse wheel up one
 *
 * \code mouse_scrolld \endcode
 * Scroll the mouse wheel down one
 *
 * \section appendix_find Find an Image
 * \code image_location <filename> \endcode
 * Get the location of an image on screen
 * 	\note This is affected by the \c CENTER, \c TOLERANCE, and \c SEARCH_METHOD variables. See \ref testing_test_wrapper for more information on these.
 * <br><br>
 *
 * \section appendix_keyboard Click the keyboard
 * \code key_str "<string>" \endcode
 * Enter a string of characters on the keyboard rather than a single character at a time.
 *  \warning This function <b>does not</b> accept key strings like "Space" as \c key_down, \c key_up, and \c key_click do. If you pass in "Space", that is exactly what will be typed.
 * <br><br>
 *
 * \code key_down "<key-name>" \endcode
 * Press a key down and leave it down
 *  \note This function accepts special keys like "Space" - see \ref XTest_key_strings for a full list of characters allowed.
 * <br><br>
 *
 * \code key_up "<key-name>" \endcode
 * Release a key
 *  \note This function accepts special keys like "Space" - see \ref XTest_key_strings for a full list of characters allowed.
 * <br><br>
 *
 * \code key_click "<key-name>" \endcode
 * Press a key down and then release it immediately after
 *  \note This function accepts special keys like "Space" - see \ref XTest_key_strings for a full list of characters allowed.
 * <br><br>
 *
 * \section appendix_utilities Useful extras
 * \code run_process "<process-name>" \endcode
 * Start a process on the system, background it, and return the PID of the created process.
 * <br><br>
 *
 * \code is_running "<process-name>" \endcode
 * \code is_running "<process-id>" \endcode
 * Check if a program name or PID is currently running
 *
 * \code notify "<string_to_display>" \endcode
 * Display a notification to the user, and wait for a response
 * \warning Uses \c zenity - if \c zenity isn't available, will return an error without pausing, and will not display anything.
 */

/** \def LIBCVAUTOMATION_VERSION
 * \brief Define what version of Libcvautomation we are using
 * \details This define provides access to what version of Libcvautomation we're using. All times that you need to know what it is should use this.
 */
/** \def LIBCVAUTOMATION_BUGREPORT
 * \brief Define who to send bug reports to for Libcvautomation
 * \details This define provides access to who should be emailed in case of a Libcvautomation bug. All times that you need to know what it is should use this.*/

/** \struct cvautomationList
 * \brief Implements a structure to build an array for methods like matchSubImage_a()
 * \details This structure is a simple way to wrap up all needed information for matching sub images in one location.
 * \param cvaImage An image in IplImage format
 * \param fileName The file location of an image to be loaded
 * \param resultPoint Holder for a result - for example, storing where this sub image was located in its root image
 * \param searchMethod The search method to use when searching for this sub image in a root image
 * \param tolerance The tolerance to use when searching for this sub image in a root image
 * \see \ref libcv_search_methods
 */

/** \struct cvaPoint
 * \brief Very simple structure to standardize how points are used in libcvautomation
 * \param x An X-coordinate
 * \param y A Y-coordinate */
