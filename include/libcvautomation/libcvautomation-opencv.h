/*
 * =====================================================================================
 *
 *       Filename:  libcvautomation-opencv.h
 *
 *    Description:  Function definitions for opencv functionality
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
#ifndef LIBCVAUTOMATION_OPENCV_H
#define LIBCVAUTOMATION_OPENCV_H

#include <libcvautomation/libcvautomation.h>

/* It should be noted that the following are the macros for template matching:
 * 	CV_TM_SQDIFF (default)
 *  CV_TM_SQDIFF_NORMED
 *  CV_TM_CCORR
 *  CV_TM_CCORR_NORMED
 *  CV_TM_CCOEFF
 *  CV_TM_CCOEFF_NORMED
 */

/* Match a root image and sub image */
CvPoint matchSubImage ( IplImage *rootImage, IplImage *subImage, int searchMethod, double tolerance );

/* Match a root image and sub image, return the center */
CvPoint matchSubImage_center ( IplImage *rootImage, IplImage *subImage, int searchMethod, double tolerance );

/* Match a root image and sub image from filename */
CvPoint matchSubImage_location ( const char *rootImage_location, const char *subImage_location, int searchMethod, double tolerance );

/* Match a root image and sub image from filename, return the center */
CvPoint matchSubImage_location_center ( const char *rootImage_location, const char *subImage_location, int searchMethod, double tolerance );

/* Match a root image and sub images from an array of images */
void matchSubImage_a ( IplImage *rootImage, cvautomationList *subImageArray, int listSize );

/* Match a root image and sub images from an array of images, return the center */
void matchSubImage_a_center ( IplImage *rootImage, cvautomationList *subImageArray, int listSize );

/* Match a root image and sub images from an array of images */
void matchSubImage_a_location ( const char *rootImageFileName, cvautomationList *subImageArray, int listSize );

/* Match a root image and sub images from an array of images, return the center */
void matchSubImage_a_location_center ( const char *rootImageFileName, cvautomationList *subImageArray, int listSize );

#endif /* LIBCVAUTOMATION_OPENCV_H */
