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
void checkXTEEnabled ();

int main( int argc, char** argv )
{
	/* Set up for getopt */
	Bool useMouseImage;
		useMouseImage = False;
	int mouseButton;
		mouseButton = 1;
	char *separator;
		separator = ",";
	char *xDisplayLocation;
		xDisplayLocation = "";
	Display *display;
		display = NULL;

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
				{"search-method",required_argument,	0,	'm'},
				{"tolerance",	required_argument,	0,	't'},
				{"button",		required_argument,	0,	'b'},
				{"string",		required_argument,	0,	's'},
				{"print-format",required_argument,	0,	'p'},
				/* Other valid values are "optional_argument"
				 * and "required_argument" */
				{0, 0, 0, 0}
		};

		int option_index = 0;
		opterr = 0;

		int c = getopt_long (argc, argv, "hud:m:t:b:cs:", /* Use a single colon for required_argument,
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
				if (display == NULL)
					display = XOpenDisplay( optarg );
				else
				{
					XCloseDisplay( display );
					XOpenDisplay( optarg );
				}

			case 'm':
				searchMethod = atoi(optarg);
				break;

			case 't':
				tolerance = atoi(optarg);
				break;

			case 'b':
				mouseButton = atoi(optarg);
				break;

			case 's':
				if (display == NULL)
					display = XOpenDisplay( xDisplayLocation );
				cvaPoint returnPoint;
				returnPoint = xte_commandString( display, optarg, mouseButton, searchMethod, tolerance );

				if (returnPoint.x != -1 && returnPoint.y != -1)
					printf("%s%s%i%s%i\n", optarg, separator, returnPoint.x, separator, returnPoint.y);
				else
					printf("%s\n", optarg);
				break;
	
			case '?':
				/* Error routine */
				break;

			default:
				fprintf( stderr, "Unknown option..." );
				exit(0);
		};
	}

	if ( display != NULL )
		XCloseDisplay( display );

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
\t-m, --search-method:\tSpecify a method to search by. See `cva-match --help\'\n\
\t\t\t\tfor more information on this.\n\
\t-t, --tolerance:\tSpecify how strict the match is.\n\
\t-b, --button:\t\tSpecify the mouse button to press (default 1).\n\
\t-c, --center:\t\tInstead of matching the top-left corner of an image,\n\
\t\t\t\tmatch the center of the image.\n\
\t-s, --string:\t\tCommand string - see below.\n\
\n\
This program works kind of like a mini-language. All options\n\
are parsed left-to-right, and executed right there. Thus, specifying \"--display\"\n\
at different places in the options will cause this program to use the most recent\n\
given display.\n\
Available commands:\n\
\tmouseclick:\tClick the mouse in-place.\n\
\timouseclick:\tClick the mouse at an image's top-left corner.\n\
\ticmouseclick:\tClick the mouse at an image's center.\n\
\tmousexy:\tMove the mouse to the given coordinate.\n\
\tmouserxy:\tMove the mouse by the given x and y values (relative motion).\n\
\tmouseimage:\tMove the mouse to an image's top-left corner.\n\
\tcmouseimage:\tMove the mouse to an image's center.\n\
\tmousedown:\tPush and leave down a mouse button.\n\
\tmouseup:\tRelease a mouse button.\n\
\tmousejiggle:\tJiggle the mouse (helps to activate some widgets).\n\
\tkeyclick:\tClick a keyboard button.\n\
\tkeydown:\tPush and leave down a keyboard button.\n\
\tkeyup:\tRelease a keyboard button.\n\
\tkeystring:\tInput a string of keys to X11.\n\
\n\
If you have any questions, comments, concerns, email <bspeice@uncc.edu>.\n\n" );

	exit (0);

}		/* -----  end of function usage  ----- */

void checkXTEEnabled ( Display *display )
{
	/* Make sure we have the XTest Extensions enabled.
	 * This is a quick wrapper. */
	if (! xte_XTestSupported( display ))
	{
		printf("The XTest extension is not supported! Aborting...");
		exit(255);
	}
}
