/*
 * =====================================================================================
 *
 *       Filename:  libcvautomation-x11.h
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

#ifndef LIBCVAUTOMATION_X11_H
#define LIBCVAUTOMATION_X11_H

#include <libcvautomation/libcvautomation.h>

/* It should be noted that the following are the macros for template matching:
 * 	CV_TM_SQDIFF (default)
 *  CV_TM_SQDIFF_NORMED
 *  CV_TM_CCORR
 *  CV_TM_CCORR_NORMED
 *  CV_TM_CCOEFF
 *  CV_TM_CCOEFF_NORMED
 */

CvPoint matchSubImage_X11( char *displayLocation, IplImage *subImage, int searchMethod, int tolerance ); /* Match a sub image using the X11 root window as root */
CvPoint matchSubImage_X11_location( char *displayLocation, const char *rootImage_location, int search_method, int tolerance ); /* Match a sub image using X11 as root, from filename */

#endif /* LIBCVAUTOMATION_X11_H */
