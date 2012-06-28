/*
 * =====================================================================================
 *
 *       Filename:  libcvautomation-xinput.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/26/2012 09:09:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Bradlee Speice (), bspeice.nc@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <libcvautomation/libcvautomation-xtest.h>

#define IS_CMD( x, y ) strncmp( x, y, strlen( y ) ) == 0
#define COMMAND_STR_LEN 512

/* Note: The XLib documentation says that we shouldn't need to XFlush,
 * but I've found in testing that events don't get done correctly unless
 * we do. I've included the XFlush() calls. */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_xTestSupported
 *  Description:  Make sure that the XTest extension is supported.
 *  				If it's not, return 0 (false)
 * =====================================================================================
 */
Bool xte_XTestSupported ( Display *displayLocation )
{
	int event_basep, error_basep, majorp, minorp;
	return XTestQueryExtension( displayLocation, &event_basep, &error_basep, &majorp, &minorp );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_pointerLocation
 *  Description:  Return the current location of the pointer
 * =====================================================================================
 */
cvaPoint xte_pointerLocation ( Display *displayLocation )
{
	/* The next few variables we discard, but need them for the function call */
	Window root, child;
	int rootX, rootY;
	unsigned int mask_return;
	/* End the discarded variables. We're using the ones that follow */
	int pointerX, pointerY;

	XQueryPointer( displayLocation, DefaultRootWindow( displayLocation ),
					&root, &child, &rootX, &rootY,
					/* And then the stuff we actually care about */
					&pointerX, &pointerY,
					/* And more stuff we don't */
					&mask_return );

	cvaPoint returnPoint;

	returnPoint.x = pointerX;
	returnPoint.y = pointerY;

	return returnPoint;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickMouse
 *  Description:  Click the mouse where it is currently at
 * =====================================================================================
 */
void xte_clickMouse ( Display *displayLocation, int mouseButton )
{
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );

	XFlush( displayLocation );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickMouseXY
 *  Description:  Click the mouse on a screen location
 * =====================================================================================
 */
void xte_clickMouseXY ( Display *displayLocation, int xLocation, int yLocation, int mouseButton )
{
	/* To avoid specifying the screen number we're using, calculate the pointer's
	 * current location, and move to the new wanted location using relative motion */
	cvaPoint pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = xLocation - pointerLocation.x;
	yIncrement = yLocation - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime ); 
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );

	XFlush( displayLocation );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickMouseRXY
 *  Description:  Click the mouse on a screen location relative to where it currently is
 * =====================================================================================
 */
void xte_clickMouseRXY ( Display *displayLocation, int xIncrement, int yIncrement, int mouseButton )
{
	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );

	XFlush( displayLocation );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickMouseImage
 *  Description:  Click the mouse at the top-left corner of an image on the specified display
 * =====================================================================================
 */
cvaPoint xte_clickMouseImage ( Display *displayLocation, IplImage *subImage, int mouseButton, int searchMethod, int tolerance )
{
	/* This one is a bit more in-depth -
	 * 	Find where the image is at
	 * 	Find where the cursor is currently at
	 * 	Move the cursor to the given point using relative motion - 
	 * 		This method is screen-agnostic */
	CvPoint resultPoint;

	resultPoint = matchSubImage_X11 ( displayLocation, subImage, searchMethod, tolerance );

	cvaPoint result;
	result.x = resultPoint.x;
	result.y = resultPoint.y;

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return result;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int movementX, movementY;

	movementX = resultPoint.x - pointerLocation.x;
	movementY = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, movementX, movementY, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );

	XFlush( displayLocation );

	return result;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickMouseImage_location
 *  Description:  Click the mouse at the top-left corner of an image on the specified display
 * 					where the subImage is a file location
 * =====================================================================================
 */
cvaPoint xte_clickMouseImage_location ( Display *displayLocation, const char *fileName, int mouseButton, int searchMethod, int tolerance )
{
	CvPoint resultPoint;

	resultPoint = matchSubImage_X11_location( displayLocation, fileName, searchMethod, tolerance );

	cvaPoint result;
	result.x = resultPoint.x;
	result.y = resultPoint.y;

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return result;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int movementX, movementY;

	movementX = resultPoint.x - pointerLocation.x;
	movementY = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, movementX, movementY, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );

	XFlush( displayLocation );

	return result;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickMouseImage_center
 *  Description:  Click the mouse at the center of an image on the specified display
 * =====================================================================================
 */
cvaPoint xte_clickMouseImage_center ( Display *displayLocation, IplImage *subImage, int mouseButton, int searchMethod, int tolerance )
{
	/* This one is a bit more in-depth -
	 * 	Find where the image is at
	 * 	Find where the cursor is currently at
	 * 	Move the cursor to the given point using relative motion - 
	 * 		This method is screen-agnostic */
	CvPoint resultPoint;

	resultPoint = matchSubImage_X11_center ( displayLocation, subImage, searchMethod, tolerance );

	cvaPoint result;
	result.x = resultPoint.x;
	result.y = resultPoint.y;

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return result;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int movementX, movementY;

	movementX = resultPoint.x - pointerLocation.x;
	movementY = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, movementX, movementY, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );

	XFlush( displayLocation );

	return result;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickMouseImage_location_center
 *  Description:  Click the mouse at the center of an image on the specified display
 *					where the subImage is a file location
 * =====================================================================================
 */
cvaPoint xte_clickMouseImage_location_center ( Display *displayLocation, const char *fileName, int mouseButton, int searchMethod, int tolerance )
{
	CvPoint resultPoint;

	resultPoint = matchSubImage_X11_location_center( displayLocation, fileName, searchMethod, tolerance );

	cvaPoint result;
	result.x = resultPoint.x;
	result.y = resultPoint.y;

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return result;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );
	
	int movementX, movementY;

	movementX = resultPoint.x - pointerLocation.x;
	movementY = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, movementX, movementY, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );

	XFlush( displayLocation );

	return result;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_hoverMouseXY
 *  Description:  Move the mouse to a location and leave it there
 * =====================================================================================
 */
void xte_hoverMouseXY ( Display *displayLocation, int xLocation, int yLocation )
{
	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = xLocation - pointerLocation.x;
	yIncrement = yLocation - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );

	XFlush( displayLocation );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_hoverMouseRXY
 *  Description:  Move the mouse to a location relative to where it currently is 
 *  				and leave it there
 * =====================================================================================
 */
void xte_hoverMouseRXY ( Display *displayLocation, int xIncrement, int yIncrement )
{
	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );

	XFlush( displayLocation );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_hoverMouseMouseImage
 *  Description:  Move the mouse to a location at the top-left corner of an image on
 *  				the specified display but don't click the mouse
 * =====================================================================================
 */
cvaPoint xte_hoverMouseImage ( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance )
{
	CvPoint resultPoint;
	resultPoint = matchSubImage_X11( displayLocation, subImage, searchMethod, tolerance );

	cvaPoint result;
	result.x = resultPoint.x;
	result.y = resultPoint.y;

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return result;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = resultPoint.x - pointerLocation.x;
	yIncrement = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );

	XFlush( displayLocation );

	return result;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_hoverMouseMouseImage_location
 *  Description:  Move the mouse to a location at the top-left corner of an image from
 *  				file on the specified display but don't click the mouse
 * =====================================================================================
 */
cvaPoint xte_hoverMouseImage_location ( Display *displayLocation, const char *fileName, int searchMethod, int tolerance )
{
	CvPoint resultPoint;
	resultPoint = matchSubImage_X11_location( displayLocation, fileName, searchMethod, tolerance );

	cvaPoint result;
	result.x = resultPoint.x;
	result.y = resultPoint.y;

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return result;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = resultPoint.x - pointerLocation.x;
	yIncrement = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );

	XFlush( displayLocation );

	return result;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_hoverMouseMouseImage_center
 *  Description:  Move the mouse to a location at the center of an image on the
 *  specified display but don't click the mouse
 * =====================================================================================
 */
cvaPoint xte_hoverMouseImage_center ( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance )
{
	CvPoint resultPoint;
	resultPoint = matchSubImage_X11_center( displayLocation, subImage, searchMethod, tolerance );

	cvaPoint result;
	result.x = resultPoint.x;
	result.y = resultPoint.y;

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return result;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = resultPoint.x - pointerLocation.x;
	yIncrement = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );

	XFlush( displayLocation );

	return result;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_hoverMouseMouseImage_location_center
 *  Description:  Move the mouse to a location at the center of an image from file on
 *  the specified display but don't click the mouse
 * =====================================================================================
 */
cvaPoint xte_hoverMouseImage_location_center ( Display *displayLocation, const char *fileName, int searchMethod, int tolerance )
{
	CvPoint resultPoint;
	resultPoint = matchSubImage_X11_location_center( displayLocation, fileName, searchMethod, tolerance );

	cvaPoint result;
	result.x = resultPoint.x;
	result.y = resultPoint.y;

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return result;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = resultPoint.x - pointerLocation.x;
	yIncrement = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );

	XFlush( displayLocation );
	
	return result;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_mouseDown
 *  Description:  Push a mouse button down, but don't release it
 * =====================================================================================
 */
void xte_mouseDown ( Display *displayLocation, int mouseButton )
{
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );

	XFlush( displayLocation );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_mouseUp
 *  Description:  Let a mouse button up
 * =====================================================================================
 */
void xte_mouseUp ( Display *displayLocation, int mouseButton )
{
	XTestFakeButtonEvent( displayLocation, mouseButton, False, CurrentTime );

	XFlush( displayLocation );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_mouseJiggle
 *  Description:  Move the mouse a little bit
 * =====================================================================================
 */
void xte_mouseJiggle ( Display *displayLocation )
{
	XTestFakeRelativeMotionEvent( displayLocation, 1, 1, CurrentTime );
	XTestFakeRelativeMotionEvent( displayLocation, -1, -1, CurrentTime );

	XFlush( displayLocation );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickKey
 *  Description:  Press and release a single key
 * =====================================================================================
 */
void xte_clickKey ( Display *displayLocation, char *key )
{
	/* Part of this code based on xte from the xautomation source
	 * available at http://hoopajoo.net/projects/xautomation.html */
	KeyCode kc;
	KeySym ks;

	ks = XStringToKeysym( key );
	if ( ks == NoSymbol )
		return;

	kc = XKeysymToKeycode( displayLocation, ks );

	XTestFakeKeyEvent( displayLocation, kc, True, CurrentTime );	
	XTestFakeKeyEvent( displayLocation, kc, False, CurrentTime );	

	XFlush( displayLocation );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickKeyStr
 *  Description:  Press and release keys in a string
 * =====================================================================================
 */
void xte_clickKeyStr ( Display *displayLocation, char *string )
{
	/* TODO: Write the code to implement a function that allows you to enter a string
	 * at a time to X, rather than a single character.*/
	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_keyDown
 *  Description:  Press a key down
 * =====================================================================================
 */
void xte_keyDown ( Display *displayLocation, char *key )
{
	KeyCode kc;
	KeySym ks;

	ks = XStringToKeysym( key );
	if ( ks == NoSymbol )
		return;

	kc = XKeysymToKeycode( displayLocation, ks );

	XTestFakeKeyEvent( displayLocation, kc, True, CurrentTime );

	XFlush( displayLocation );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_keyUp
 *  Description:  Release a key
 * =====================================================================================
 */
void xte_keyUp ( Display *displayLocation, char *key )
{
	KeyCode kc;
	KeySym ks;

	ks = XStringToKeysym( key );
	if ( ks == NoSymbol )
		return;

	kc = XKeysymToKeycode( displayLocation, ks );

	XTestFakeKeyEvent( displayLocation, kc, True, CurrentTime );

	XFlush( displayLocation );
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_commandString
 *  Description:  Use one of the functions by command name
 * =====================================================================================
 */
cvaPoint xte_commandString ( Display *displayLocation, char *commandString, int mouseButton, int searchMethod, int tolerance )
{
	/* Alright, this function bears a bit of talking about.
	 * What happens is that I test here for the command, and pass it off.
	 * This functionality was inspired by xte from xautomation,
	 * the original can be found at: http://hoopajoo.net/projects/xautomation.html 
	 * Most of the code for parsing is the same, just easier to do it that way. */

	/* Note that most of the functions don't need mouseButton, searchMethod, or tolerance,
	 * but they're here to make sure that they're available if needed. */

	cvaPoint resultPoint;
	resultPoint.x = -1;
	resultPoint.y = -1;

	/* Perform basic sanity checking */
	if (commandString == NULL)
		return resultPoint;

	/* And now we sanitize the input */
	char *s_commandString;
	s_commandString = (char*)malloc(COMMAND_STR_LEN * sizeof(char));
	memset(s_commandString, '\0', COMMAND_STR_LEN * sizeof(char));

	strncpy( s_commandString, commandString, COMMAND_STR_LEN - 1 );

	/* And now to test for all of our options */
	if (IS_CMD( s_commandString, "mouseclick" ))
	{
		int mouseButton;
		sscanf( s_commandString, "mouseclick %i", &mouseButton );

		xte_clickMouse( displayLocation, mouseButton );
	}
	else if (IS_CMD( s_commandString, "mousexy" ))
	{
		int xLocation, yLocation;
		sscanf( s_commandString, "mousexy %i %i", &xLocation, &yLocation );

		xte_hoverMouseXY( displayLocation, xLocation, yLocation );
	}
	else if (IS_CMD( s_commandString, "mouserxy" ))
	{
		int xIncrement, yIncrement;
		sscanf( s_commandString, "mouserxy %i %i", &xIncrement, &yIncrement );

		xte_hoverMouseRXY( displayLocation, xIncrement, yIncrement );
	}
	else if (IS_CMD( s_commandString, "mouseimage" ))
	{
		char *fileName;
		fileName = malloc(COMMAND_STR_LEN * sizeof(char));
		sscanf( s_commandString, "mouseimage %s", fileName );

		cvaPoint resultPoint;
		resultPoint = xte_hoverMouseImage_location( displayLocation, fileName, searchMethod, tolerance );

		free(fileName);

		return resultPoint;
	}
	else if (IS_CMD( s_commandString, "cmouseimage" ))
	{
		char *fileName;
		fileName = malloc(COMMAND_STR_LEN * sizeof(char));
		sscanf( s_commandString, "cmouseimage %s", fileName );

		xte_hoverMouseImage_location_center( displayLocation, fileName, searchMethod, tolerance );

		free(fileName);
	}
	else if (IS_CMD( s_commandString, "imouseclick" ))
	{
		char *fileName;
		fileName = malloc(COMMAND_STR_LEN * sizeof(char));
		sscanf( s_commandString, "imouseclick %s", fileName );

		cvaPoint resultPoint;
		resultPoint = xte_clickMouseImage_location( displayLocation, fileName, mouseButton, searchMethod, tolerance );

		free(fileName);

		return resultPoint;
	}
	else if (IS_CMD( s_commandString, "icmouseclick" ))
	{
		char *fileName;
		fileName = malloc(COMMAND_STR_LEN * sizeof(char));
		sscanf( s_commandString, "icmouseclick %s", fileName );

		cvaPoint resultPoint;
		resultPoint = xte_clickMouseImage_location_center( displayLocation, fileName, mouseButton, searchMethod, tolerance );

		free(fileName);

		return resultPoint;
	}
	else if (IS_CMD( s_commandString, "mousedown" ))
	{
		int mouseButton;
		sscanf( s_commandString, "mousedown %i", &mouseButton );

		xte_mouseDown( displayLocation, mouseButton );
	}
	else if (IS_CMD( s_commandString, "mouseup" ))
	{
		int mouseButton;
		sscanf( s_commandString, "mouseup %i", &mouseButton );

		xte_mouseUp( displayLocation, mouseButton );
	}
	else if (IS_CMD( s_commandString, "mousejiggle" ))
	{
		xte_mouseJiggle( displayLocation );
	}
	else if (IS_CMD( s_commandString, "keyclick" ))
	{
		char *key;
		key = malloc(COMMAND_STR_LEN * sizeof(char));
		sscanf( s_commandString, "keyclick %s", key );

		xte_clickKey( displayLocation, key );

		free(key);
	}
	else if (IS_CMD( s_commandString, "keydown" ))
	{
		char *key;
		key = malloc(COMMAND_STR_LEN * sizeof(char));
		sscanf( s_commandString, "keydown %s", key );

		xte_keyDown( displayLocation, key );

		free(key);
	}
	else if (IS_CMD( s_commandString, "keyup" ))
	{
		char *key;
		key = malloc(COMMAND_STR_LEN * sizeof(char));
		sscanf( s_commandString, "keyup %s", key );

		xte_keyUp( displayLocation, key );

		free(key);
	}
	else if (IS_CMD( s_commandString, "keystring" ))
	{
		char *keyString;
		keyString = malloc(COMMAND_STR_LEN * sizeof(char));
		sscanf( s_commandString, "keystring %s", keyString );

		xte_clickKeyStr( displayLocation, keyString );

		free(keyString);
	}

	return resultPoint;
}
