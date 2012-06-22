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
#include <limits.h>

#include "libcvautomation.h"

void usage ();

struct list {
	char *fileName;
	struct list *next;
};

typedef struct list basic_list; 

int main( int argc, char** argv )
{
	CvPoint result_point;
	result_point.x = result_point.y = 0;

	/* Set up everything for getopt */
	char *separator = ",";
	char *root_location = "root.png";
	char *sub_location = "sub.png";
	int tolerance = INT_MAX;
	int search_method = CV_TM_SQDIFF;
	int useX = 0; /* bool useX = false; */
	char *xDisplay;

	/* Set up the linked list for slave images */
	basic_list *list_head = NULL, *list_curr = NULL, *list_prev = NULL;

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
				{"search-method",required_argument,	0,	'm'},
				{"tolerance",	required_argument,	0,	't'},
				{"x-root",		optional_argument,	0,	'x'},
				{0, 0, 0, 0}
		};

		int option_index = 0;
		opterr = 0;

		int c = getopt_long (argc, argv, "hur:s:p:m:t:x::",
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
				if ( list_head == NULL )
				{
					list_head = (basic_list *) malloc (sizeof(basic_list));
					list_curr = list_head;
				}
				list_curr->fileName = optarg;
				list_curr->next = (basic_list *) malloc (sizeof(basic_list));
				list_curr = list_curr->next;
				break;

			case 'p':
				separator = optarg;
				break;

			case 'm':
				search_method = atoi(optarg);
				break;

			case 't':
				tolerance = atoi(optarg);
				break;

			case 'x':
				if ( optarg != NULL ) {
					useX = 1;
					xDisplay = optarg;
				} else {
					useX = 1;
					xDisplay = "";
				}
				break;


			case '?':
				/* Error routine */
				break;

			default:
				fprintf( stderr, "Unknown option..." );
				exit(0);
		};
	}

	/* Make sure we have a linked list, 
	 * and reset the linked list to go back through from the top */
	if ( list_head == NULL )
		return 1;
	else
		list_curr = list_head;

	do
	{
		sub_location = list_curr->fileName;

		if (useX)
			result_point = matchSubImage_X11_location( xDisplay, sub_location, search_method, tolerance );
		else
			result_point = matchSubImage_location( root_location, sub_location, search_method, tolerance );

		if ( result_point.x != -1 && result_point.y != -1 )
			/* Output the match location */
			printf ("%s%s%i%s%i\n", list_curr->fileName, separator,
					result_point.x, separator, result_point.y );

		/* With the way we allocate the list, we ensure that we always
		 * have at least one element past the end of the list.
		 * Also, deconstruct the list as we go. */
		list_prev = list_curr;
		list_curr = list_curr->next;
		free(list_prev);

	} while ( list_curr->fileName != NULL );

	/* And free the final element */
	free(list_curr);

	return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  usage
 *  Description:  I really shouldn't need to write this
 * =====================================================================================
 */
void usage ( )
{
	fprintf( stderr, "\n\
cva-match -r <root_image> -s <sub_image> \n\
cva-match -s <sub_image> -x \n\
\n\
This program uses OpenCV in order to recognize an image within an image.\n\
The return code is how many matches were found - return 0 for no matches,\n\
1 for one match, etc.\n\
\n\
Usage: \n\
\n\
\t-h, --help:\t\tDisplay this usage message.\n\
\t-u, --usage:\t\tDisplay this usage message.\n\
\t-r, --root-image:\tLocation of the root image to compare against.\n\
\t-s, --sub-image:\tLocation of the sub-image to find in root.\n\
\t-p, --separator:\tSeparator of the X and Y coordinates.\n\
\t-t, --tolerance:\tSet how strict the match is - 100 is recommended lowest value.\n\
\t\t\t\tNote: When using CCORR or CCOEFF tolerance works in opposite direction,\n\
\t\t\t\tso -50 is recommended highest value.\n\
\t-m, --search-method:\tSet which method is used to search for sub-images.\n\
\t\t\t\tMethods:\n\
\t\t\t\t\tCV_TM_SQDIFF = 0\n\
\t\t\t\t\tCV_TM_SQDIFF_NORMED = 1\n\
\t\t\t\t\tCV_TM_CCORR = 2\n\
\t\t\t\t\tCV_TM_CCORR_NORMED = 3\n\
\t\t\t\t\tCV_TM_CCOEFF = 4\n\
\t\t\t\t\tCV_TM_COEFF_NORMED = 5\n\
\t-x, --x-root[=DISPLAY]:\tSet the root image to come from X11\n\
\t\t\t\tThe DISPLAY variable is optional, not specifying it will cause X\n\
\t\t\t\tto use the default display (not specifically :0.0)\n\
\t\t\t\tPlease note also that the '-x' must come at the end\n\
\t\t\t\tsince it is an optional argument.\n\
\n\
If you have any questions, comments, concerns, email bspeice@uncc.edu\n" );

	exit (0);

}		/* -----  end of function usage  ----- */

