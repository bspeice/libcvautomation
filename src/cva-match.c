/*
 * =====================================================================================
 *
 *       Filename:  cva-match.c
 *
 *    Description:  Match an image to its parent image, and return the coordinates
 *
 *        Version:  0.1
 *        Created:  06/20/2012
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Bradlee Speice, bspeice@uncc.edu
 *   Organization:  MOSAIC at University of North Carolina at Charlotte
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

#include "cv.h"
#include "highgui.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  usage
 *  Description:  
 * =====================================================================================
 */
void usage ( )
{
	fprintf( stderr,
	"cva-match -r <root_image> -s <sub_image> \n\
\n\
This program uses OpenCV in order to recognize an image within an image.\n\
The return code is how many matches were found - return 0 for no matches,\n\
1 for one match, etc.\n\
\n\
Usage: \n\
\n\
\t-h, --help:\tDisplay this usage message.\n\
\t-u, --usage:\tDisplay this usage message.\n\
\t-r, --root-image:\tLocation of the root image to compare against.\n\
\t-s, --sub-image:\tLocation of the sub-image to find in root.\n\
\t-p, --separator:\tSeparator of the X and Y coordinates.\n\
\n\
If you have any questions, comments, concerns, email bspeice@uncc.edu\n" );

	exit (0);

}		/* -----  end of function usage  ----- */

int main( int argc, char** argv )
{
	IplImage	*root; /* The root image */
	IplImage	*sub; /* The sub-image */
	IplImage	*res;
	CvPoint		minloc, maxloc; /* The location of our match */
	double		minval, maxval;
	int			root_width, root_height;
	int			sub_width, sub_height;
	int			res_width, res_height;

	/* Set up everything for getopt */
	char *separator = ",";
	char *root_location = "root.png";
	char *sub_location = "sub.png";

	/* Start getopt */
	while (1)
	{
		static struct option long_options[] =
		{
				{"help",		no_argument,		0,	'h'},
				{"usage",		no_argument,		0,	'u'},
				{"root-image",	required_argument,	0,	'r'},
				{"sub-image",	required_argument,	0,	's'},
				{"separator",	required_argument,	0,	'p'},
				{0, 0, 0, 0}
		};

		int option_index = 0;
		opterr = 0;

		int c = getopt_long (argc, argv, "hur:s:p:",
							long_options, &option_index);

		/* We're done with parsing options */
		if (c == -1)
			break;

		switch (c)
		{
			case 0:
				break;

			case 'h':
				usage();
				break;

			case 'u':
				usage();
				break;

			case 'r':
				root_location = optarg;
				break;

			case 's':
				sub_location = optarg;
				break;

			case 'p':
				separator = optarg;
				break;

			case '?':
				/* Error routine */
				break;

			default:
				fprintf( stderr, "Unknown option..." );
				exit(0);
		};
	}


	/* load reference image */
	root = cvLoadImage( root_location, CV_LOAD_IMAGE_COLOR );

	/* always check */
	if( root == 0 ) {
		fprintf( stderr, "Cannot load the root image %s!\n", root_location );
		return 0; 
	}

	/* load sub image */
	sub = cvLoadImage( sub_location, CV_LOAD_IMAGE_COLOR );

	/* always check */
	if( sub == 0 ) {
		fprintf( stderr, "Cannot load the sub-image %s!\n", sub_location );
		return 0;
	}

	/* get image's properties */
	root_width  = root->width;
	root_height = root->height;
	sub_width  = sub->width;
	sub_height = sub->height;
	res_width  = root_width - sub_width + 1;
	res_height = root_height - sub_height + 1;

	/* create new image for template matching computation */
	res = cvCreateImage( cvSize( res_width, res_height ), IPL_DEPTH_32F, 1 );

	/* choose template matching method to be used */
	cvMatchTemplate( root, sub, res, CV_TM_SQDIFF );
	/*cvMatchTemplate( root, sub, res, CV_TM_SQDIFF_NORMED );
	cvMatchTemplate( root, sub, res, CV_TM_CCORR );
	cvMatchTemplate( root, sub, res, CV_TM_CCORR_NORMED );
	cvMatchTemplate( root, sub, res, CV_TM_CCOEFF );
	cvMatchTemplate( root, sub, res, CV_TM_CCOEFF_NORMED );*/

	cvMinMaxLoc( res, &minval, &maxval, &minloc, &maxloc, 0 );

	/* Output the match location */
	printf ("%i%s%i\n", minloc.x, separator, minloc.y );

	/* free memory */
	cvReleaseImage( &root );
	cvReleaseImage( &sub );
	cvReleaseImage( &res );

	return 0;
}

