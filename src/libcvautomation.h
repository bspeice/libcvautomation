/*
 * =====================================================================================
 *
 *       Filename:  libcvautomation.h
 *
 *    Description:  Include wrapper for libcvautomation subsections
 *
 *        Version:  1.0
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

#include <stdio.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

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

#endif /* LIBCVAUTOMATION_H */
