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

/* C includes */
#include <stdio.h>

#ifdef USEOPENCV2
/* OpenCV2 includes - some filenames are different */
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc_c.h>

#else
/* OpenCV includes */
#include <opencv/cv.h>
#include <opencv/highgui.h>

#endif /* #ifdef OPENCV2 */

/* X11 includes */
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

/* Project component includes */
/* The includes come here to make sure all function prototypes have access
 * to the cvautomationList struct */
#include <libcvautomation/libcvautomation-opencv.h>
#include <libcvautomation/libcvautomation-x11.h>

#endif /* LIBCVAUTOMATION_H */
