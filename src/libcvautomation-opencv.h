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

#include <opencv/cv.h>
#include <opencv/highgui.h>

/* It should be noted that the following are the macros for template matching:
 * 	CV_TM_SQDIFF (default)
 *  CV_TM_SQDIFF_NORMED
 *  CV_TM_CCORR
 *  CV_TM_CCORR_NORMED
 *  CV_TM_CCOEFF
 *  CV_TM_CCOEFF_NORMED
 */

/* Match a root image and sub image */
CvPoint matchSubImage ( IplImage *rootImage, IplImage *subImage, int searchMethod, double threshold );

/* Match a root image and sub image from filename */
CvPoint matchSubImage_location ( char *rootImage_location, char *subImage_location, int searchMethod, double threshold );

#endif /* LIBCVAUTOMATION_OPENCV_H */
