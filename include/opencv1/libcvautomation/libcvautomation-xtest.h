/*
 * =====================================================================================
 *
 *       Filename:  libcvautomation-xinput.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/26/2012 09:08:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Bradlee Speice (), bspeice.nc@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef LIBCVAUTOMATION_XTEST_H
#define LIBCVAUTOMATION_XTEST_H

#include <libcvautomation/libcvautomation.h>

/* Make sure that the XTest extension is supported.
 * If it's not, return 0 (false) */
Bool xte_XTestSupported ( Display *displayLocation );

/* Get the current location of the pointer */
cvaPoint xte_pointerLocation ( Display *displayLocation );

/* Click the mouse where it is currently at */
void xte_clickMouse ( Display *displayLocation, int mouseButton );

/* Click the mouse on an absolute screen location */
void xte_clickMouseXY ( Display *displayLocation, int xLocation, int yLocation, int mouseButton );

/* Click the mouse on a screen location relative to where it currently is */
void xte_clickMouseRXY ( Display *displayLocation, int xIncrement, int yIncrement, int mouseButton );

/* Click the mouse at the top-left corner of an image on the specified display */
cvaPoint xte_clickMouseImage ( Display *displayLocation, IplImage *subImage, int mouseButton, int searchMethod, int tolerance );

/* Click the mouse at the top-left corner of an image on the specified display
 * where the subImage is a file location */
cvaPoint xte_clickMouseImage_location ( Display *displayLocation, const char *fileName, int mouseButton, int searchMethod, int tolerance );

/* Click the mouse at the center of an image on the specified display */
cvaPoint xte_clickMouseImage_center ( Display *displayLocation, IplImage *subImage, int mouseButton, int searchMethod, int tolerance );

/* Click the mouse at the center of an image on the specified display
 * where the subImage is a file location */
cvaPoint xte_clickMouseImage_location_center ( Display *displayLocation, const char *fileName, int mouseButton, int searchMethod, int tolerance );

/* Move the mouse to a location and leave it there */
void xte_hoverMouseXY ( Display *displayLocation, int xLocation, int yLocation );

/* Move the mouse to a location relative to where it currently is and leave it there */
void xte_hoverMouseRXY ( Display *displayLocation, int xIncrement, int yIncrement );

/* Move the mouse to a location at the top-left corner of an image on the specified display
 * but don't click the mouse */
cvaPoint xte_hoverMouseImage ( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance );

/* Move the mouse to a location at the top-left corner of an image from file on the specified display
 * but don't click the mouse */
cvaPoint xte_hoverMouseImage_location ( Display *displayLocation, const char *filename, int searchMethod, int tolerance );

/* Move the mouse to a location at the center of an image on the specified display
 * but don't click the mouse */
cvaPoint xte_hoverMouseImage_center ( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance );

/* Move the mouse to a location at the center of an image from file on the specified display
 * but don't click the mouse */
cvaPoint xte_hoverMouseImage_location_center ( Display *displayLocation, const char *fileName, int searchMethod, int tolerance );

/* Push a mouse button down, but don't release it */
void xte_mouseDown ( Display *displayLocation, int mouseButton );

/* Let a mouse button up */
void xte_mouseUp ( Display *displayLocation, int mouseButton );

/* Move the mouse a little bit */
void xte_mouseJiggle ( Display *displayLocation );

/* Press and release a key 
 * Note that we use a string for *key, since keys like "space" are still valid. */
void xte_clickKey ( Display *displayLocation, char *key );

/* Press and release keys in a string */
void xte_clickKeyStr ( Display *displayLocation, char *string );

/* Press a key down */
void xte_keyDown ( Display *displayLocation, char *key );

/* Release a key */
void xte_keyUp ( Display *displayLocation, char *key );

/* Use one of the functions by command name */
cvaPoint xte_commandString ( Display *displayLocation, char *command, int mouseButton, int searchMethod, int tolerance );

#endif /* LIBCVAUTOMATION_XTEST_H */
