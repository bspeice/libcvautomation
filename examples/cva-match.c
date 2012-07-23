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

#include <libcvautomation/libcvautomation.h>

void usage ();

/// \cond
struct list {
	char *fileName;
	struct list *next;
};

typedef struct list basic_list; 
/// \endcond

int main( int argc, char** argv )
{
	cvaPoint result_point;
	result_point.x = result_point.y = 0;

	/* Set up everything for getopt */
	char *separator = ",";
	char *root_location = "root.png";
	char *sub_location = "sub.png";
	int tolerance = INT_MAX;
	int search_method = CV_TM_SQDIFF;
	int useX = 0; /* bool useX = false; */
	Bool useCenter = False;
	char *xDisplayLocation;
	Display *display = NULL;

	/* Set the default display */
	xDisplayLocation = "";

	/* Set up the linked list for slave images */
	basic_list *list_head, *list_curr, *list_prev;
	list_head = list_curr = list_prev = NULL;

	int returnCode = 1;

	/* Start getopt */
	while (1)
	{
		static struct option long_options[] =
		{
				{"help",		no_argument,		0,	'h'},
				{"usage",		no_argument,		0,	'u'},
				{"version",		no_argument,		0,	'v'},
				{"root-image",	required_argument,	0,	'r'},
				{"sub-image",	required_argument,	0,	's'},
				{"separator",	required_argument,	0,	'p'},
				{"search-method",required_argument,	0,	'm'},
				{"tolerance",	required_argument,	0,	't'},
				{"x-root",		optional_argument,	0,	'x'},
				{"center",		no_argument,		0,	'c'},
				{"sane-tolerance", required_argument, 0, 'o'},
				{0, 0, 0, 0}
		};

		int option_index = 0;
		opterr = 0;

		int c = getopt_long (argc, argv, "hur:s:p:m:t:x::c",
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

			case 'v':
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
				list_curr->next->fileName = NULL;
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
					xDisplayLocation = optarg;
					display = XOpenDisplay(xDisplayLocation);
				} else {
					useX = 1;
					xDisplayLocation = "";
					display = XOpenDisplay(xDisplayLocation);
				}
				break;

			case 'c':
				useCenter = True;
				break;

			case 'o':
				tolerance = atoi(optarg);
				/* Provide a more sane way to configure tolerance:
				 * --sane-tolerance=100 ~= INT_MAX */
				tolerance = pow(1.2397076, tolerance);
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

		if (useX && useCenter)
			result_point = matchSubImage_X11_location_center( display, sub_location, search_method, tolerance );
		else if (useX && !useCenter)
			result_point = matchSubImage_X11_location( display, sub_location, search_method, tolerance );
		else if (!useX && useCenter)
			result_point = matchSubImage_location_center( root_location, sub_location, search_method, tolerance );
		else /* if (!useX && !useCenter) */
			result_point = matchSubImage_location( root_location, sub_location, search_method, tolerance );

		if ( result_point.x != -1 && result_point.y != -1 )
		{
			/* Output the match location */
			printf ("%s%s%i%s%i\n", list_curr->fileName, separator,
					result_point.x, separator, result_point.y );
			returnCode = 0;
		}

		/* With the way we allocate the list, we ensure that we always
		 * have at least one element past the end of the list.
		 * Also, deconstruct the list as we go. */
		list_prev = list_curr;
		list_curr = list_curr->next;
		free(list_prev);

	} while ( list_curr->fileName != NULL );

	/* And free the final element */
 	free(list_curr);

	/* Clean up X */
	if (useX)
		XCloseDisplay(display);

	return returnCode;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  usage
 *  Description:  I really shouldn't need to write this
 * =====================================================================================
 */
void usage ( )
{
	fprintf( stderr, "\
Libcvautomation version: %s\n\
cva-match -r <root_image> -s <sub_image> \n\
cva-match -s <sub_image> -x \n\
\n\
This program uses OpenCV in order to recognize an image within an image.\n\
The return code is 0 for at least one successful match, and 1 otherwise.\n\
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
\t-c, --center:\t\tThe output points should be centered on the sub-image, rather\n\
\t\t\t\tthan the top-left corner.\n\
\t-o, --sane-tolerance:\tSet the tolerance using a scale of 1-100,\n\
\t\t\t\trather than INT_MIN to INT_MAX (100 ~= INT_MAX)\n\
\n\
If you have any questions, comments, concerns, email <%s>\n", LIBCVAUTOMATION_VERSION, LIBCVAUTOMATION_BUGREPORT );

	exit (0);

}		/* -----  end of function usage  ----- */

/* Doxygen Information */
/** \file cva-match.c
 * \brief The cva-input program to demonstrate Libcvautomation's XTest functionality
 * \author Bradlee Speice <bspeice@uncc.edu>
 */

/* The biggest purpose of documenting this code is to trick doxygen into making a man page for it. */
/** \page cva-match
 *
 * \author Bradlee Speice <bspeice@uncc.edu>
 * \section usage Usage:
 * This program uses OpenCV in order to recognize an image within an image. The return code is 0 for at least one successful match, and 1 otherwise.
 *
 * \section example Example Usage:
 * Match two images against the root X11 window:
 *
 * cva-match --x-root -s "<image_name>" -s "<image_name_2>"
 *
 * Match a root and sub image with a custom tolerance and search method
 *
 * cva-match -r "<root_image>" -s "<image_name>" -o 75 -m 1
 *
 * \section options Full Options:
 * -h, --help:  Display this usage message.
 *
 * -u, --usage:  Display this usage message.
 *
 * -r, --root-image: Location of the root image to compare against.
 *
 * -s, --sub-image: Location of the sub-image to find in root.
 *
 * -p, --separator: Separator of the X and Y coordinates.
 *
 * -t, --tolerance: Set how strict the match is - 100 is recommended lowest value.
 *
 * \note When using CCORR or CCOEFF tolerance works in opposite direction, so -50 is recommended highest value.
 *
 * -m, --search-method: Set which method is used to search for sub-images.
 *
 * \note Search Methods: CV_TM_SQDIFF = 0, CV_TM_SQDIFF_NORMED = 1, CV_TM_CCORR = 2, CV_TM_CCORR_NORMED = 3, CV_TM_CCOEFF = 4, CV_TM_COEFF_NORMED = 5
 *
 * -x, --x-root[=DISPLAY]: Set the root image to come from X11
 * 	
 * \note The DISPLAY variable is optional, not specifying it will cause X to use the default display (not specifically :0.0)
 *
 * -c, --center:  The output points should be centered on the sub-image, rather than the top-left corner.
 *
 * -o, --sane-tolerance: Set the tolerance using a scale of 1-100, rather than INT_MIN to INT_MAX (100 ~= INT_MAX)
 *
 *
 * \section contact Contact Information:
 * Questions? Comments? Concerns? Suggestions? Send all feedback to Bradlee Speice at <bspeice@uncc.edu>

 */
