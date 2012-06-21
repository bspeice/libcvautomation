/*
 * =====================================================================================
 *
 *       Filename:  libcvautomation-x11.c
 *
 *    Description:  
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

#include "libcvautomation-x11.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  matchSubImage_X11
 *  Description:  Match a sub image using the X11 root window as root
 * =====================================================================================
 */
CvPoint matchSubImage_X11( char *displayLocation, IplImage *subImage, int searchMethod, int threshold )
{
	/* First things first, grab the root X window and convert it to
	 * the IplImage format.
	 * Much of this code was ripped lovingly from:
	 * 	http://opencv.willowgarage.com/wiki/ximage2opencvimage */
	IplImage *X_IPL;
	CvSize imageSize;
	CvPoint resultPoint;

	XImage *rootImage;
	XColor color;
	Display *display;
	Screen *screen;
	unsigned long rmask, gmask, bmask;
	unsigned long rshift, rbits,
					gshift, gbits,
					bshift, bbits;
	unsigned char colorChannel[3];

	int startX = 0, startY = 0;
	unsigned int width, height;

	/* Setting up the X screengrab is the first order of business */
	display = XOpenDisplay(displayLocation);
	screen = DefaultScreenOfDisplay(display);
	
	width = screen->width;
	height = screen->height;

	rootImage = XGetImage( display, DefaultRootWindow(display),
							startX, startY, width, height,
							AllPlanes, ZPixmap );

	/* Make sure that we're good to go before going any farther */
	if ( rootImage == NULL || display == NULL || screen == NULL )
	{
		fprintf( stderr, "Couldn't grab the root window!" );
		resultPoint.x = -1;
		resultPoint.y = -1;
		return resultPoint;
	}

	/* Set up the OpenCV Image */
	imageSize.width = rootImage->width;
	imageSize.height = rootImage->height;
	X_IPL = cvCreateImage( imageSize, IPL_DEPTH_8U, 3 ); /* 3 channels - RGB */

	/* This if block converts the X root window to an IPL image. See you on the other side! */
	unsigned int x, y; /* To be used later */

	if ( screen->depths->depth == 24 )
	{
		/* Actually convert the XImage to Ipl */
		rmask = screen->root_visual->red_mask;
		gmask = screen->root_visual->green_mask;
		bmask = screen->root_visual->blue_mask;

		/* I honestly have no clue how most of the below code works */
		/* TODO: Figure out how this code works and document it */
		rshift = 0; rbits = 0;
		while ( !(rmask & 1) ){
			rshift++;
			rmask >>= 1; /* Right bitshift by 1 */
		}
		while (rmask & 1) {
			rbits++;
			rmask >>= 1; /* Right bitshift by 1 */
		}
		if (rbits > 8) {
			rshift += rbits - 8;
			rbits = 8;
		}

		gshift = 0; gbits = 0;
		while ( !(gmask & 1) ){
			gshift++;
			gmask >>= 1; /* Right bitshift by 1 */
		}
		while (gmask & 1) {
			gbits++;
			gmask >>= 1; /* Right bitshift by 1 */
		}
		if (gbits > 8) {
			gshift += gbits - 8;
			gbits = 8;
		}

		bshift = 0; bbits = 0;
		while ( !(bmask & 1) ){
			bshift++;
			bmask >>= 1; /* Right bitshift by 1 */
		}
		while (bmask & 1) {
			bbits++;
			bmask >>= 1; /* Right bitshift by 1 */
		}
		if (bbits > 8) {
			bshift += bbits - 8;
			bbits = 8;
		}

		for ( x = 0; x < rootImage->width; x++) {
			for ( y = 0; y < rootImage->height; y++) {
				color.pixel = XGetPixel ( rootImage, x, y );
				colorChannel[0] = ((color.pixel >> bshift) & ((1 << bbits) - 1)) << (8 - bbits);
				colorChannel[1] = ((color.pixel >> gshift) & ((1 << gbits) - 1)) << (8 - gbits);
				colorChannel[2] = ((color.pixel >> rshift) & ((1 << rbits) - 1)) << (8 - rbits);
				CV_IMAGE_ELEM(X_IPL, uchar, y, x * X_IPL->nChannels) = colorChannel[0];
				CV_IMAGE_ELEM(X_IPL, uchar, y, x * X_IPL->nChannels + 1) = colorChannel[1];
				CV_IMAGE_ELEM(X_IPL, uchar, y, x * X_IPL->nChannels + 2) = colorChannel[2];
			}
		}
	}
	else
	{
		/* Slow alternative for non-24-bit-depth images */
		/* I don't know how this works either. */
		/* TODO: Figure out how this code works and document it */
		Colormap colormap = DefaultColormap( &display, DefaultScreen ( &display ));
		for ( x = 0; x < rootImage->width; x++ ) {
			for ( y = 0; y < rootImage->height; y++ ) {
				color.pixel = XGetPixel ( rootImage, x, y );
				XQueryColor( display, colormap, &color );
				CV_IMAGE_ELEM(X_IPL, uchar, y, x * X_IPL->nChannels) = color.blue;
				CV_IMAGE_ELEM(X_IPL, uchar, y, x * X_IPL->nChannels + 1) = color.green;
				CV_IMAGE_ELEM(X_IPL, uchar, y, x * X_IPL->nChannels + 2) = color.red;
			}
		}
	}

	/* Now that we've got the image we want as X_IPL, time to actually do the comparison.
	 * However, we don't want to do any more work than we have to - send our images off
	 * to matchSubImage in libopencvautomation-opencv. */

	resultPoint = matchSubImage ( X_IPL, subImage, searchMethod, threshold );

	/* Clean up the CV image we created, as well as all X resources */
	XDestroyImage( rootImage );
	XCloseDisplay( display );
	cvReleaseImage( &X_IPL );

	/* Return and be done */
	return resultPoint;

}		/* -----  end of function matchSubImage_X11  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  matchSubImage_X11
 *  Description:  Match a sub image using the X11 root window as root, from filename
 * =====================================================================================
 */
CvPoint matchSubImage_X11_location( char *displayLocation, char *subImage_location, int searchMethod, int threshold )
{
	/* This is basically a wrapper for matchSubImage_X11( char *display, IplImage )
	 * All we do is load the sub-image from the given filename, and then
	 * pass off the result to the above-named function */

	IplImage *subImage;
	subImage = cvLoadImage( subImage_location, CV_LOAD_IMAGE_COLOR );

	CvPoint return_point;

	/* Make sure we have a good image */
	if ( subImage == 0 )
	{
		/* Return error */
		return return_point;
	}

	return_point = matchSubImage_X11( displayLocation, subImage, searchMethod, threshold );

	/* Free up the memory we created */
	cvReleaseImage( &subImage );

	/* Our return_point will already be bad if there's no match,
	 * we don't need to worry about setting it. */
	return return_point;

}		/* -----  end of function matchSubImage_X11_location  ----- */
