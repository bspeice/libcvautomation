/*
 * =====================================================================================
 *
 *       Filename:  libcvautomation-xlib.h
 *
 *    Description:  Function definitions for X11 operations
 *
 *        Version:  1.0
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

/* It should be noted that the following are the macros for template matching:
 * 	CV_TM_SQDIFF (default)
 *  CV_TM_SQDIFF_NORMED
 *  CV_TM_CCORR
 *  CV_TM_CCORR_NORMED
 *  CV_TM_CCOEFF
 *  CV_TM_CCOEFF_NORMED
 */

/* Custom wrapper for XOpenDisplay function */
Display* cvaOpenDisplay ( char *displayName );

/* Custom wrapper for XCloseDisplay funtion */
void cvaCloseDisplay ( Display *displayLocation );

/* Match a sub image using the X11 root window as root */
CvPoint matchSubImage_X11( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance ); 

/* Match a sub image using the X11 root window as root, return the center */
CvPoint matchSubImage_X11_center( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance ); 

/* Match a sub image using X11 as root, from filename */
CvPoint matchSubImage_X11_location( Display *displayLocation, const char *subImage_location, int search_method, int tolerance ); 

/* Match a sub image using X11 as root, from filename, return the center */
CvPoint matchSubImage_X11_location_center( Display *displayLocation, const char *subImage_location, int search_method, int tolerance ); 

#endif /* LIBCVAUTOMATION_XLIB_H */
