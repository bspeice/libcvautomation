/*
 * =====================================================================================
 *
 *       Filename:  cva-input.c
 *
 *    Description:  This is an example program to demonstrate the XTest and XInput
 *    				functionality in libcvautomation
 *
 *        Version:  1.0
 *        Created:  06/26/2012 09:20:20 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Bradlee Speice (), bspeice.nc@gmail.com
 *   Organization:  
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

int main( int argc, char** argv )
{
	/* Set up for getopt */
	int mouseXMovement, mouseYMovement;
	/* Safe to say that nobody will ever need to move INT_MAX
	 * pixels. INT_MAX is used to signify an uninitialized value. */
	mouseXMovement = mouseYMovement = INT_MAX;
	cvaPoint currentLocation;
	char *mouseImage;
		mouseImage = NULL;
	Bool useMouseImage;
		useMouseImage = False;
	int mouseButton;
		mouseButton = 1;
	char *keypress;
		keypress = NULL;
	char *xDisplayLocation;
		xDisplayLocation = "";
	Display *display;
		display = NULL;
	Bool useCenter;
		useCenter = False;

	int searchMethod, tolerance;
	searchMethod = 0;
	tolerance = INT_MAX;

	/* Start getopt */
	while (1)
	{
		static struct option long_options[] =
		{
				{"help",		no_argument,		0,	'h'},
				{"usage",		no_argument,		0,	'u'},
				{"display",		required_argument,	0,	'd'},
				{"move-mousex",	required_argument,	0,	'x'},
				{"move-mousey", required_argument,	0,	'y'},
				{"mover-mousex",required_argument,	0,	'r'},
				{"mover-mousey",required_argument,	0,	's'},
				{"movei-mouse",	required_argument,	0,	'i'},
				{"keypress",	required_argument,	0,	'k'},
				{"search-method",required_argument,	0,	'm'},
				{"tolerance",	required_argument,	0,	't'},
				{"button",		required_argument,	0,	'b'},
				{"center",		no_argument,		0,	'c'},
				/* Other valid values are "optional_argument"
				 * and "required_argument" */
				{0, 0, 0, 0}
		};

		int option_index = 0;
		opterr = 0;

		int c = getopt_long (argc, argv, "hux:y:r:s:i:k:", /* Use a single colon for required_argument,
												* double colon for optional_argument */
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

			case 'd':
				xDisplayLocation = optarg;

			case 'x':
				if ( display == NULL )
					display = XOpenDisplay( xDisplayLocation );
				currentLocation = xte_pointerLocation( display );

				mouseXMovement = atoi(optarg) - currentLocation.x;

				break;

			case 'y':
				if ( display == NULL )
					display = XOpenDisplay( xDisplayLocation );
				currentLocation = xte_pointerLocation( display );

				mouseYMovement = atoi(optarg) - currentLocation.y;

				break;

			case 'r':
				mouseXMovement = atoi(optarg);
				break;

			case 's':
				mouseYMovement = atoi(optarg);
				break;

			case 'i':
				useMouseImage = True;
				mouseImage = optarg;
				break;

			case 'k':
				keypress = optarg;
				break;

			case 'm':
				searchMethod = atoi(optarg);
				break;

			case 't':
				tolerance = atoi(optarg);
				break;

			case 'b':
				mouseButton = atoi(optarg);
				break;

			case 'c':
				useCenter = True;
				break;

			case '?':
				/* Error routine */
				break;

			default:
				fprintf( stderr, "Unknown option..." );
				exit(0);
		};
	}

	/* If we haven't opened our display yet, do that now.
	 * Note that we will only ever open one display due to
	 * checks implemented in the optarg section. */
	if (display == NULL)
		display = XOpenDisplay( xDisplayLocation );

	if (! xte_XTestSupported( display ))
	{
		printf("The XTest extension is not supported! Aborting...");
		exit(255);
	}
	
	if (useMouseImage)
	{
		if (useCenter)
			xte_clickMouseImage_location( display, mouseImage, mouseButton, searchMethod, tolerance );
		else
			xte_clickMouseImage_location_center( display, mouseImage, mouseButton, searchMethod, tolerance );
	}

	else if (keypress != NULL)
		xte_clickKey( display, keypress );

	else 
	{
		if (mouseXMovement == INT_MAX)
			mouseXMovement = 0;
		if (mouseYMovement == INT_MAX)
			mouseYMovement = 0;

		printf("%i, %i\n", mouseXMovement, mouseYMovement);
		xte_clickMouseRXY( display, mouseXMovement, mouseYMovement, mouseButton );
	}


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
cva-input -i <image_file>\n\
cva-input -x <x_location> -y <y_location>\n\
cva-input -k <key>\n\
\n\
The cva-input program demonstrates the XTest section of libcvautomation.\n\
\n\
Usage: \n\
\n\
\t-h, --help:\t\tDisplay this usage message.\n\
\t-u, --usage:\t\tDisplay this usage message.\n\
\t-d, --display:\t\tSpecify the X display to use.\n\
\t-x, --move-mousex:\tSpecify the end location of the mouse (x-coordinate).\n\
\t-y, --move-mousey:\tSpecify the end location of the mouse (y-coordinate).\n\
\t-r, --mover-mousex:\tSpecify the distance in the X plane to move the mouse.\n\
\t-s, --mover-mousey:\tSpecify the distance in the Y plane to move the mouse.\n\
\t-i, --movei-mouse:\tSpecify an image to click.\n\
\t\t\t\tBy default, the program will click the top-left corner of the image.\n\
\t\t\t\tUse the \"-c\" switch to change this.\n\
\t-k, --keypress:\t\tSpecify a key to press.\n\
\t-m, --search-method:\tSpecify a method to search by. See \`cva-match --help\'\n\
\t\t\t\tfor more information on this.\n\
\t-t, --tolerance:\tSpecify how strict the match is.\n\
\t-b, --button:\t\tSpecify the mouse button to press (default 1).\n\
\t-c, --center:\t\tInstead of matching the top-left corner of an image,\n\
\t\t\t\tmatch the center of the image.\n\
\n\
If you have any questions, comments, concerns, email <bspeice@uncc.edu>.\n\n" );

	exit (0);

}		/* -----  end of function usage  ----- */

