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

void usage ();

int main( int argc, char** argv )
{
	/* Start getopt */
	while (1)
	{
		static struct option long_options[] =
		{
				{"help",		no_argument,		0,	'h'},
				{"usage",		no_argument,		0,	'u'},
				/* Other valid values are "optional_argument"
				 * and "required_argument" */
				{0, 0, 0, 0}
		};

		int option_index = 0;
		opterr = 0;

		int c = getopt_long (argc, argv, "hu", /* Use a single colon for required_argument,
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

			case '?':
				/* Error routine */
				break;

			default:
				fprintf( stderr, "Unknown option..." );
				exit(0);
		};
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
<program_name> version <program_version>\n\
\n\
Put your usage or help text here.\n\
\n\
Usage: \n\
\n\
\t-h, --help:\t\tDisplay this usage message.\n\
\t-u, --usage:\t\tDisplay this usage message.\n\
\n\
If you have any questions, comments, concerns, email somebody else.\n" );

	exit (0);

}		/* -----  end of function usage  ----- */

