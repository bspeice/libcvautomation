/*
 * =====================================================================================
 *
 *       Filename:  libcvautomation-xlib.h
 *
 *    Description:  Function definitions for X11 operations
 *
 *        Created:  06/21/2012 08:34:21 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Bradlee Speice, bspeice@uncc.edu
 *   Organization:  MOSAIC at University of North Carolina at Charlotte
 *
 * =====================================================================================
 */

#ifndef LIBCVAUTOMATION_XLIB_H
#define LIBCVAUTOMATION_XLIB_H

#include <libcvautomation/libcvautomation.h>

/* Custom wrapper for XOpenDisplay function */
Display* cvaOpenDisplay ( char *displayName );

/* Custom wrapper for XCloseDisplay funtion */
void cvaCloseDisplay ( Display *displayLocation );

/* Match a sub image using the X11 root window as root */
cvaPoint matchSubImage_X11( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance ); 

/* Match a sub image using the X11 root window as root, return the center */
cvaPoint matchSubImage_X11_center( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance ); 

/* Match a sub image using X11 as root, from filename */
cvaPoint matchSubImage_X11_location( Display *displayLocation, const char *subImage_location, int search_method, int tolerance ); 

/* Match a sub image using X11 as root, from filename, return the center */
cvaPoint matchSubImage_X11_location_center( Display *displayLocation, const char *subImage_location, int search_method, int tolerance ); 

#endif /* LIBCVAUTOMATION_XLIB_H */

/* Doxygen information */
/** \file libcvautomation-xlib.h
 * \brief The source code to access Xlib from inside libcvautomation
 * \details This source file builds in the necessary functionality to use xlib functions inside libcvautomation.
 * \author Bradlee Speice
 */

/** \fn Display* cvaOpenDisplay ( char *displayName );
 * \brief Simple wrapper for XOpenDisplay
 * \details Currently this function literally just passes off to XOpenDisplay, but is designed to be used in the future if extra functionality is needed.
 * \param displayName The name of the display to open - '' is a valid name
 * \returns Pointer to the opened X11 Display
 * \warning You must open a display to use any functions.
 * \warning The program using this library is responsible to close the display as well.
 */

/** \fn void cvaCloseDisplay ( Display *displayLocation );
 * \brief Simple wrapper for XCloseDisplay
 * \details Currently this function literally just passes off to XCloseDisplay, but is designed to be used in the future if extra functionality is needed.
 * \param displayLocation Pointer to the display to close
 * \returns Nothing
 */

/** \fn cvaPoint matchSubImage_X11( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance ); 
 * \brief Return the location of a sub image in the X11 root window
 * \details This function wraps grabbing the X11 root window, converting it to IplImage format, and then giving this to matchSubImage()
 * \param displayLocation Pointer to the currently open X11 Display
 * \param subImage The sub image (in IplImage format) to search for in the root X11 window
 * \param searchMethod The search method to use when searching for \c subImage in the root X11 window
 * \param tolerance The tolerance to use when searching for \c subImage in the root X11 window
 * \see \ref libcvautomation_search_methods
 * \returns The location of the sub image in root X11 window
 */

/** \fn cvaPoint matchSubImage_X11_center( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance ); 
 * \brief Return the center of a sub image in root X11 window, rather than the top-left corner
 * \details This function wraps grabbing the X11 root window, converting it to IplImage format, and then giving this to matchSubImage_center()
 * \param displayLocation Pointer to the currently open X11 Display
 * \param subImage The sub image (in IplImage format) to search for in the root X11 window
 * \param searchMethod The search method to use when searching for \c subImage in the root X11 window
 * \param tolerance The tolerance to use when searching for \c subImage in the root X11 window
 * \see \ref libcvautomation_search_methods
 * \returns The center location of the sub image in the root X11 window
 */

/** \fn cvaPoint matchSubImage_X11_location( Display *displayLocation, const char *subImage_location, int searchMethod, int tolerance ); 
 * \brief Return the location of a sub image in the X11 root window
 * \details This function wraps grabbing the X11 root window, converting it to IplImage format, and then giving this to matchSubImage_location()
 * \param displayLocation Pointer to the currently open X11 Display
 * \param subImage_location The location of the sub image to search for in the root X11 window
 * \param searchMethod The search method to use when searching for \c subImage in the root X11 window
 * \param tolerance The tolerance to use when searching for \c subImage in the root X11 window
 * \see \ref libcvautomation_search_methods
 * \returns The center location of the sub image in the root X11 window
 */

/** \fn cvaPoint matchSubImage_X11_location_center( Display *displayLocation, const char *subImage_location, int searchMethod, int tolerance ); 
 * \brief Return the center of a sub image in the root X11 window, rather than the top-left corner
 * \details This function wraps grabbing the X11 root window, converting it to IplImage format, and then giving this to matchSubImage_location_center()
 * \param displayLocation Pointer to the currently open X11 Display
 * \param subImage_location The location of the sub image to search for in the root X11 window
 * \param searchMethod The search method to use when searching for \c subImage in the root X11 window
 * \param tolerance The tolerance to use when searching for \c subImage in the root X11 window
 * \see \ref libcvautomation_search_methods
 * \returns The center location of the sub image in the root X11 window
 */

