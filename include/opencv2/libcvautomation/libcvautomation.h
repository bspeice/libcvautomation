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

/** \struct cvautomationList
 * \brief Implements a structure to build an array for methods like matchSubImage_a()
 * \details This structure is a simple way to wrap up all needed information for matching sub images in one location.
 * \param cvaImage An image in IplImage format
 * \param fileName The file location of an image to be loaded
 * \param resultPoint Holder for a result - for example, storing where this sub image was located in its root image
 * \param searchMethod The search method to use when searching for this sub image in a root image
 * \param tolerance The tolerance to use when searching for this sub image in a root image
 * \see libcv_search_methods
 */

/** \struct cvaPoint
 * \brief Very simple structure to standardize how points are used in libcvautomation
 * \param x An X-coordinate
 * \param y A Y-coordinate */
