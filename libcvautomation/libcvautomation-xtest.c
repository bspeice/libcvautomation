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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_xTestSupported
 *  Description:  Make sure that the XTest extension is supported.
 *  				If it's not, return 0 (false)
 * =====================================================================================
 */
int xte_XTestSupported ( Display *displayLocation )
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
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickMouseImage
 *  Description:  Click the mouse at the top-left corner of an image on the specified display
 * =====================================================================================
 */
void xte_clickMouseImage ( Display *displayLocation, IplImage *subImage, int mouseButton, int searchMethod, int tolerance )
{
	/* This one is a bit more in-depth -
	 * 	Find where the image is at
	 * 	Find where the cursor is currently at
	 * 	Move the cursor to the given point using relative motion - 
	 * 		This method is screen-agnostic */
	CvPoint resultPoint;

	resultPoint = matchSubImage_X11 ( displayLocation, subImage, searchMethod, tolerance );

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int movementX, movementY;

	movementX = resultPoint.x - pointerLocation.x;
	movementY = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, movementX, movementY, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickMouseImage_location
 *  Description:  Click the mouse at the top-left corner of an image on the specified display
 * 					where the subImage is a file location
 * =====================================================================================
 */
void xte_clickMouseImage_location ( Display *displayLocation, const char *fileName, int mouseButton, int searchMethod, int tolerance )
{
	CvPoint resultPoint;

	resultPoint = matchSubImage_X11_location( displayLocation, fileName, searchMethod, tolerance );

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int movementX, movementY;

	movementX = resultPoint.x - pointerLocation.x;
	movementY = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, movementX, movementY, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickMouseImage_center
 *  Description:  Click the mouse at the center of an image on the specified display
 * =====================================================================================
 */
void xte_clickMouseImage_center ( Display *displayLocation, IplImage *subImage, int mouseButton, int searchMethod, int tolerance )
{
	/* This one is a bit more in-depth -
	 * 	Find where the image is at
	 * 	Find where the cursor is currently at
	 * 	Move the cursor to the given point using relative motion - 
	 * 		This method is screen-agnostic */
	CvPoint resultPoint;

	resultPoint = matchSubImage_X11_center ( displayLocation, subImage, searchMethod, tolerance );

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int movementX, movementY;

	movementX = resultPoint.x - pointerLocation.x;
	movementY = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, movementX, movementY, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickMouseImage_location_center
 *  Description:  Click the mouse at the center of an image on the specified display
 *					where the subImage is a file location
 * =====================================================================================
 */
void xte_clickMouseImage_location_center ( Display *displayLocation, const char *fileName, int mouseButton, int searchMethod, int tolerance )
{
	CvPoint resultPoint;

	resultPoint = matchSubImage_X11_location_center( displayLocation, fileName, searchMethod, tolerance );

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );
	
	int movementX, movementY;

	movementX = resultPoint.x - pointerLocation.x;
	movementY = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, movementX, movementY, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );
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
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_hoverMouseMouseImage
 *  Description:  Move the mouse to a location at the top-left corner of an image on
 *  				the specified display but don't click the mouse
 * =====================================================================================
 */
void xte_hoverMouseImage ( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance )
{
	CvPoint resultPoint;
	resultPoint = matchSubImage_X11( displayLocation, subImage, searchMethod, tolerance );

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = resultPoint.x - pointerLocation.x;
	yIncrement = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_hoverMouseMouseImage_location
 *  Description:  Move the mouse to a location at the top-left corner of an image from
 *  				file on the specified display but don't click the mouse
 * =====================================================================================
 */
void xte_hoverMouseImage_location ( Display *displayLocation, const char *fileName, int searchMethod, int tolerance )
{
	CvPoint resultPoint;
	resultPoint = matchSubImage_X11_location( displayLocation, fileName, searchMethod, tolerance );

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = resultPoint.x - pointerLocation.x;
	yIncrement = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_hoverMouseMouseImage_center
 *  Description:  Move the mouse to a location at the center of an image on the
 *  specified display but don't click the mouse
 * =====================================================================================
 */
void xte_hoverMouseImage_center ( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance )
{
	CvPoint resultPoint;
	resultPoint = matchSubImage_X11_center( displayLocation, subImage, searchMethod, tolerance );

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = resultPoint.x - pointerLocation.x;
	yIncrement = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_hoverMouseMouseImage_location_center
 *  Description:  Move the mouse to a location at the center of an image from file on
 *  the specified display but don't click the mouse
 * =====================================================================================
 */
void xte_hoverMouseImage_location_center ( Display *displayLocation, const char *fileName, int searchMethod, int tolerance )
{
	CvPoint resultPoint;
	resultPoint = matchSubImage_X11_location_center( displayLocation, fileName, searchMethod, tolerance );

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = resultPoint.x - pointerLocation.x;
	yIncrement = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );
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
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_mouseUp
 *  Description:  Let a mouse button up
 * =====================================================================================
 */
void xte_mouseUp ( Display *displayLocation, int mouseButton )
{
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );
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
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickKey
 *  Description:  Press and release a single key
 * =====================================================================================
 */
void xte_clickKey ( Display *displayLocation, char key )
{

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickKeyStr
 *  Description:  Press and release keys in a string
 * =====================================================================================
 */
void xte_clickKeyStr ( Display *displayLocation, const char *string )
{

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_keyDown
 *  Description:  Press a key down
 * =====================================================================================
 */
void xte_keyDown ( Display *displayLocation, char key )
{

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_keyUp
 *  Description:  Release a key
 * =====================================================================================
 */
void xte_keyUp ( Display *displayLocation, char key )
{

}
