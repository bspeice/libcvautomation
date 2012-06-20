/*
 * TemplateMatching 1.0
 *
 * @author 	  Nashruddin Amin <me@nashruddin.com>
 * @version   1.0
 * @website	  http://www.nashruddin.com
 */

#include <stdio.h>
#include "cv.h"
#include "highgui.h"

int main( int argc, char** argv )
{
	IplImage	*img;
	IplImage	*tpl;
	IplImage	*res;
	CvPoint		minloc, maxloc;
	double		minval, maxval;
	int			img_width, img_height;
	int			tpl_width, tpl_height;
	int			res_width, res_height;

	/* check for arguments */
	if( argc < 3 ) {
		fprintf( stderr, "Usage: template_match <reference> <template>\n" );
		return 1;
	}

	/* load reference image */
	img = cvLoadImage( argv[1], CV_LOAD_IMAGE_COLOR );

	/* always check */
	if( img == 0 ) {
		fprintf( stderr, "Cannot load file %s!\n", argv[1] );
		return 1; 
	}

	/* load template image */
	tpl = cvLoadImage( argv[2], CV_LOAD_IMAGE_COLOR );

	/* always check */
	if( tpl == 0 ) {
		fprintf( stderr, "Cannot load file %s!\n", argv[2] );
		return 1;
	}

	/* get image's properties */
	img_width  = img->width;
	img_height = img->height;
	tpl_width  = tpl->width;
	tpl_height = tpl->height;
	res_width  = img_width - tpl_width + 1;
	res_height = img_height - tpl_height + 1;

	/* create new image for template matching computation */
	res = cvCreateImage( cvSize( res_width, res_height ), IPL_DEPTH_32F, 1 );

	/* choose template matching method to be used */
	cvMatchTemplate( img, tpl, res, CV_TM_SQDIFF );
	/*cvMatchTemplate( img, tpl, res, CV_TM_SQDIFF_NORMED );
	cvMatchTemplate( img, tpl, res, CV_TM_CCORR );
	cvMatchTemplate( img, tpl, res, CV_TM_CCORR_NORMED );
	cvMatchTemplate( img, tpl, res, CV_TM_CCOEFF );
	cvMatchTemplate( img, tpl, res, CV_TM_CCOEFF_NORMED );*/

	cvMinMaxLoc( res, &minval, &maxval, &minloc, &maxloc, 0 );

	/* draw red rectangle */
	cvRectangle( img, 
				 cvPoint( minloc.x, minloc.y ), 
				 cvPoint( minloc.x + tpl_width, minloc.y + tpl_height ),
				 cvScalar( 0, 0, 255, 0 ), 1, 0, 0 );	

	/* display images */
	cvNamedWindow( "reference", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "template", CV_WINDOW_AUTOSIZE );
	cvShowImage( "reference", img );
	cvShowImage( "template", tpl );

	/* wait until user press a key to exit */
	cvWaitKey( 0 );

	/* free memory */
	cvDestroyWindow( "reference" );
	cvDestroyWindow( "template" );
	cvReleaseImage( &img );
	cvReleaseImage( &tpl );
	cvReleaseImage( &res );

	return 0;
}

