/*
 * =====================================================================================
 *
 *       Filename:  libcvautomation-xinput.c
 *
 *    Description:  
 *
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

/* The following includes are used only by the code brought in with xautomation.
 * As such, the rest of libcvautomation doesn't get access to them, which is why
 * they are included here, rather than in the header (so that all of libcvautomation
 * would end up including them). */
#include <wchar.h>
#include <stdint.h>
#include <libcvautomation/xautomation_kbd.h>
#include <libcvautomation/xautomation_keysym_map.h>
#include <libcvautomation/xautomation_multikey_map.h>

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
	cvaPoint resultPoint;

	resultPoint = matchSubImage_X11 ( displayLocation, subImage, searchMethod, tolerance );

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return resultPoint;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int movementX, movementY;

	movementX = resultPoint.x - pointerLocation.x;
	movementY = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, movementX, movementY, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );

	XFlush( displayLocation );

	return resultPoint;
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
	cvaPoint resultPoint;

	resultPoint = matchSubImage_X11_location( displayLocation, fileName, searchMethod, tolerance );

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return resultPoint;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int movementX, movementY;

	movementX = resultPoint.x - pointerLocation.x;
	movementY = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, movementX, movementY, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );

	XFlush( displayLocation );

	return resultPoint;
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
	cvaPoint resultPoint;

	resultPoint = matchSubImage_X11_center ( displayLocation, subImage, searchMethod, tolerance );

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return resultPoint;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int movementX, movementY;

	movementX = resultPoint.x - pointerLocation.x;
	movementY = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, movementX, movementY, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );

	XFlush( displayLocation );

	return resultPoint;
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
	cvaPoint resultPoint;

	resultPoint = matchSubImage_X11_location_center( displayLocation, fileName, searchMethod, tolerance );

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return resultPoint;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );
	
	int movementX, movementY;

	movementX = resultPoint.x - pointerLocation.x;
	movementY = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, movementX, movementY, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 1, CurrentTime );
	XTestFakeButtonEvent( displayLocation, mouseButton, 0, CurrentTime );

	XFlush( displayLocation );

	return resultPoint;
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
	cvaPoint resultPoint;
	resultPoint = matchSubImage_X11( displayLocation, subImage, searchMethod, tolerance );

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return resultPoint;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = resultPoint.x - pointerLocation.x;
	yIncrement = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );

	XFlush( displayLocation );

	return resultPoint;
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
	cvaPoint resultPoint;
	resultPoint = matchSubImage_X11_location( displayLocation, fileName, searchMethod, tolerance );

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return resultPoint;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = resultPoint.x - pointerLocation.x;
	yIncrement = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );

	XFlush( displayLocation );

	return resultPoint;
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
	cvaPoint resultPoint;
	resultPoint = matchSubImage_X11_center( displayLocation, subImage, searchMethod, tolerance );

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return resultPoint;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = resultPoint.x - pointerLocation.x;
	yIncrement = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );

	XFlush( displayLocation );

	return resultPoint;
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
	cvaPoint resultPoint;
	resultPoint = matchSubImage_X11_location_center( displayLocation, fileName, searchMethod, tolerance );

	if (resultPoint.x == -1 && resultPoint.y == -1)
		/* Match not found */
		return resultPoint;

	cvaPoint pointerLocation;
	pointerLocation = xte_pointerLocation( displayLocation );

	int xIncrement, yIncrement;
	xIncrement = resultPoint.x - pointerLocation.x;
	yIncrement = resultPoint.y - pointerLocation.y;

	XTestFakeRelativeMotionEvent( displayLocation, xIncrement, yIncrement, CurrentTime );

	XFlush( displayLocation );
	
	return resultPoint;
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
 *         Name:  xte_mouseScrollUp
 *  Description:  Scroll the mouse up
 * =====================================================================================
 */
void xte_mouseScrollUp ( Display *displayLocation )
{
	XTestFakeButtonEvent( displayLocation, 4, True, CurrentTime );
	XTestFakeButtonEvent( displayLocation, 4, False, CurrentTime );

	XFlush( displayLocation );
}		/* -----  end of function xte_mouseScrollUp  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_mouseScrollDown
 *  Description:  Scroll the mouse down
 * =====================================================================================
 */
void xte_mouseScrollDown ( Display *displayLocation )
{
	XTestFakeButtonEvent( displayLocation, 5, True, CurrentTime );
	XTestFakeButtonEvent( displayLocation, 5, False, CurrentTime );

	XFlush( displayLocation );
}		/* -----  end of function xte_mouseScrollDown  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickKey
 *  Description:  Press and release a single key
 * =====================================================================================
 */
void xte_clickKey ( Display *displayLocation, char *key )
{
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
 *         Name:  xautomation_load_keycodes
 *  Description:  load_keycodes function from xte in xautomation
 * =====================================================================================
 */
void xautomation_load_keycodes ( Display *displayLocation )
{
	int i_min_keycode, i_max_keycode, keysyms_per_keycode,keycode_index,wrap_key_index,num_modifiers;
	KeyCode min_keycode, max_keycode;
    char *str;
    KeySym *keysyms, keysym;
    KeyCode keycode;

    XDisplayKeycodes( displayLocation, &i_min_keycode, &i_max_keycode);
	min_keycode = i_min_keycode;
	max_keycode = i_max_keycode;
    keysyms = XGetKeyboardMapping( displayLocation,
        min_keycode, max_keycode + 1 - min_keycode,
        &keysyms_per_keycode );

    /* Clear tables */
    for( keysym=0; keysym<MAX_KEYSYM; keysym++ ) {
        keysym_to_modifier_map[keysym]=-1;
        keysym_to_keycode_map[keysym]=0;
    }

    if( keysyms_per_keycode < NUM_KEY_MODIFIERS*2 ) {
        num_modifiers = keysyms_per_keycode;
    } else {
        num_modifiers = NUM_KEY_MODIFIERS*2;
    }

    for( keycode_index = 0; keycode_index < ( max_keycode + 1 - min_keycode ); keycode_index++ ) {
        keycode = keycode_index + min_keycode;
        for( wrap_key_index = 0; wrap_key_index < num_modifiers; wrap_key_index++ ) {
            str = XKeysymToString( keysyms[ keycode_index * keysyms_per_keycode + wrap_key_index ] );
            if( str != NULL ) {
                keysym = XStringToKeysym( str );

                if( keysym < MAX_KEYSYM &&
                        keysym_to_modifier_map[ keysym ] == -1 ) {
                    keysym_to_modifier_map[ keysym ] = wrap_key_index;
                    keysym_to_keycode_map[ keysym ] = keycode;
                }
            }
        }
    }

    /* Free storage */
    XFree(keysyms);

}		/* -----  end of function xautomation_load_keycodes  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xautomation_send_char
 *  Description:  
 * =====================================================================================
 */
void xautomation_send_char ( Display *d, KeySym keysym )
{
	/* The following code lovingly (and with full permission) ripped from
	 * the 'xte' program as part of xautomation, and massaged to work with
	 * libcvautomation. Find the original code at:
	 * http://hoopajoo.net/projects/xautomation.html */
	
	KeyCode keycode;
    char *wrap_key = NULL;
    int shift;

    /* KeyCode and keyboard modifier lookup */
    keycode  = keysym_to_keycode_map[keysym];
    shift    = keysym_to_modifier_map[ keysym ]%2;
    wrap_key = key_modifiers[ (keysym_to_modifier_map[ keysym ]-shift)/2 ];

    /* Generate key events */
    if( wrap_key != NULL )
	{
		KeySym wrap_keysym;
		wrap_keysym = XStringToKeysym(wrap_key);
		KeyCode wrap_keycode;
		wrap_keycode = XKeysymToKeycode( d, wrap_keysym);
        XTestFakeKeyEvent( d, wrap_keycode, True, CurrentTime );
	}
    if ( shift )
	{
		KeySym shift_keysym;
		shift_keysym = XStringToKeysym(shift_key);
		KeyCode shift_keycode;
		shift_keycode = XKeysymToKeycode( d, shift_keysym );
        XTestFakeKeyEvent( d, shift_keycode, True, CurrentTime );
	}
    XTestFakeKeyEvent( d, keycode, True, CurrentTime );
    XTestFakeKeyEvent( d, keycode, False, CurrentTime );
    if ( shift )
	{
		KeySym shift_keysym;
		shift_keysym = XStringToKeysym(shift_key);
		KeyCode shift_keycode;
		shift_keycode = XKeysymToKeycode( d, shift_keysym);
        XTestFakeKeyEvent( d, shift_keycode, False, CurrentTime );
	}
    if( wrap_key != NULL )
	{
		KeySym wrap_keysym;
		wrap_keysym = XStringToKeysym(wrap_key);
		KeyCode wrap_keycode;
		wrap_keycode = XKeysymToKeycode( d, wrap_keysym);
        XTestFakeKeyEvent( d, wrap_keycode, False, CurrentTime );
	}

    /* Flushing after every key, thanks thorsten@staerk.de */
    XFlush( d );

}		/* -----  end of function xautomation_send_char  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_clickKeyStr
 *  Description:  Press and release keys in a string
 * =====================================================================================
 */
void xte_clickKeyStr ( Display *displayLocation, char *string )
{
	/* The following code lovingly (and with full permission) ripped from
	 * the 'xte' program as part of xautomation, and massaged to work with
	 * libcvautomation. Find the original code at:
	 * http://hoopajoo.net/projects/xautomation.html */
	
	static Bool didLoadKeyCodes = False;

	if ( ! didLoadKeyCodes )
	{
		xautomation_load_keycodes( displayLocation );
		didLoadKeyCodes = True;
	}
	
	int i,j;

    KeySym keysym[2];

    wchar_t string_s[ COMMAND_STR_LEN ];
    wchar_t wc_singlechar_str[2];

    wmemset( string_s, L'\0', COMMAND_STR_LEN );
    mbstowcs( string_s, string, COMMAND_STR_LEN );
    wc_singlechar_str[ 1 ] = L'\0';
    i = 0;
    while( ( string[ i ] != L'\0' ) && ( i < COMMAND_STR_LEN ) ) {
        wc_singlechar_str[ 0 ] = string[ i ];

        /* KeySym lookup */
		if (wc_singlechar_str[ 0] >= MAX_KEYSYM)
			keysym[0] = 0;
		else
			keysym[0] = wc_singlechar_str[ 0 ];
        keysym[1] = 0;
        if ( (keysym[0] == 0) || (keysym_to_keycode_map[keysym[0]] == 0) ) {
            // No keycode found -> try to find a Multi_key combination for this character
            keysym[0] = 0;
            for(j=0;j<MULTIKEY_MAP_SIZE;j++) {
                if (wc_singlechar_str[ 0 ] == multikey_map_char[ j ]) {
                    /* Found */
					keysym[0] = multikey_map_first[j];
					keysym[1] = multikey_map_first[j];

                    if ((keysym_to_keycode_map[keysym[0]] == 0) || (keysym_to_keycode_map[keysym[1]] == 0)) {
                        /* Character not supported */
                        keysym[0] = 0;
                    }
                    break;
                }
            }
        }

        if (keysym[0]) {
            if (keysym[1]) {
                /* Multi key sequence */
				XTestFakeKeyEvent( displayLocation,
						XKeysymToKeycode( displayLocation,
								XStringToKeysym( "Multi_key" )),
						True, CurrentTime );
				XTestFakeKeyEvent( displayLocation,
						XKeysymToKeycode( displayLocation,
								XStringToKeysym( "Multi_key" )),
						False, CurrentTime );

                xautomation_send_char( displayLocation,keysym[0]);
                xautomation_send_char( displayLocation,keysym[1]);
            } else {
                /* Single key */
                xautomation_send_char( displayLocation,keysym[0]);
            }
        } else {
            fprintf( stderr, "Character '%ls' is not supported by your keyboard layout.\n", wc_singlechar_str );
        }

        i++;
    }
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

	XTestFakeKeyEvent( displayLocation, kc, False, CurrentTime );

	XFlush( displayLocation );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_waitForImage
 *  Description:  Wait for an image to show up on screen
 * =====================================================================================
 */
cvaPoint xte_waitForImage ( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance, int timeout )
{
	cvaPoint resultPoint;
	resultPoint.x = resultPoint.y = -1;

	int localTime = 0;
	while ( localTime < timeout )
	{
		resultPoint = matchSubImage_X11( displayLocation, subImage, searchMethod, tolerance );

		if ( resultPoint.x != -1 && resultPoint.y != -1 )
			return resultPoint;

		sleep( 1 );
		localTime++;
	}

	/* Return error, we couldn't find the image */
	return resultPoint;
}		/* -----  end of function xte_waitForImage  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_waitForImage_location
 *  Description:  Wait for an image from file to show up on screen
 * =====================================================================================
 */
cvaPoint xte_waitForImage_location ( Display *displayLocation, const char *fileName, int searchMethod, int tolerance, int timeout )
{
	cvaPoint resultPoint;
	resultPoint.x = resultPoint.y = -1;

	/* The next conditional bears some discussion. Due to the way template matching works,
	 * if the tolerance is INT_MAX or INT_MIN (depending on the search method) you will
	 * *always* get a result back. Thus, while your intentions may be good, you kill
	 * the point of waiting until an image appears. Please tune your tolerance values. */
	if ((searchMethod == CV_TM_SQDIFF && tolerance == INT_MAX) ||
		(searchMethod == CV_TM_SQDIFF_NORMED && tolerance == INT_MAX) ||
		(searchMethod == CV_TM_CCORR && tolerance == INT_MIN) ||
		(searchMethod == CV_TM_CCORR_NORMED && tolerance == INT_MIN) ||
		(searchMethod == CV_TM_CCOEFF && tolerance == INT_MIN) ||
		(searchMethod == CV_TM_CCOEFF_NORMED && tolerance == INT_MIN) )
		
		fprintf( stderr, "Passing a bad tolerance value to xte_waitForImage_location()...\n" );

	int localTime = 0;
	while ( localTime < timeout )
	{
		resultPoint = matchSubImage_X11_location( displayLocation, fileName, searchMethod, tolerance );

		if ( resultPoint.x != -1 && resultPoint.y != -1 )
			return resultPoint;

		sleep( 1 );
		localTime++;
	}

	/* Return error, we couldn't find the image */
	return resultPoint;
}		/* -----  end of function xte_waitForImage_location  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  xte_commandString
 *  Description:  Use one of the functions by command name
 * =====================================================================================
 */
cvaPoint xte_commandString ( Display *displayLocation, char *commandString, int mouseButton, int searchMethod, int tolerance, int timeout )
{
	/* Alright, this function bears a bit of talking about.
	 * What happens is that I test here for the command, and pass it off.
	 * This functionality was inspired by xte from xautomation,
	 * the original can be found at: http://hoopajoo.net/projects/xautomation.html 
	 * Most of the code for parsing is the same, just easier to do it that way. */

	/* Note that most of the functions don't need mouseButton, searchMethod, etc.
	 * but they're here to make sure that they're available if needed. */

	/* The returns also bear a bit of instruction.
	 * A return of (0,0) or up is a success
	 * A return of (-1,-1) is an error
	 * A return of (-2,-2) indicates that the command didn't need to use the point -
	 * 	This helps differentiate between errors and functions like keyclick that
	 * 	don't use the resultPoint. */

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
		/* The integer argument is optional */
		int mouseButton;
		if (sscanf( s_commandString, "mouseclick %i", &mouseButton ) != 1)
			mouseButton = 1;

		xte_clickMouse( displayLocation, mouseButton );

		resultPoint.x = resultPoint.y = -2;
	}
	else if (IS_CMD( s_commandString, "mousexy" ))
	{
		int xLocation, yLocation;
		if (sscanf( s_commandString, "mousexy %i %i", &xLocation, &yLocation ) != 2)
		{
			cvaPoint pointerLocation;
			pointerLocation = xte_pointerLocation( displayLocation );
			xLocation = pointerLocation.x;
			yLocation = pointerLocation.y;
		}

		xte_hoverMouseXY( displayLocation, xLocation, yLocation );

		resultPoint.x = resultPoint.y = -2;
	}
	else if (IS_CMD( s_commandString, "mouserxy" ))
	{
		int xIncrement, yIncrement;
		if (sscanf( s_commandString, "mouserxy %i %i", &xIncrement, &yIncrement ) != 2)
		{
			xIncrement = 0;
			yIncrement = 0;
		}

		xte_hoverMouseRXY( displayLocation, xIncrement, yIncrement );

		resultPoint.x = resultPoint.y = -2;
	}
	else if (IS_CMD( s_commandString, "mouseimage" ))
	{
		char *fileName;
		fileName = malloc(COMMAND_STR_LEN * sizeof(char));
		if (sscanf( s_commandString, "mouseimage %s", fileName ) == 1 )
			resultPoint = xte_hoverMouseImage_location( displayLocation, fileName, searchMethod, tolerance );

		free(fileName);
	}
	else if (IS_CMD( s_commandString, "cmouseimage" ))
	{
		char *fileName;
		fileName = malloc(COMMAND_STR_LEN * sizeof(char));
		if (sscanf( s_commandString, "cmouseimage %s", fileName ) == 1)
			resultPoint = xte_hoverMouseImage_location_center( displayLocation, fileName, searchMethod, tolerance );

		free(fileName);
	}
	else if (IS_CMD( s_commandString, "imouseclick" ))
	{
		char *fileName;
		fileName = malloc(COMMAND_STR_LEN * sizeof(char));
		if (sscanf( s_commandString, "imouseclick %s", fileName ) == 1)
			resultPoint = xte_clickMouseImage_location( displayLocation, fileName, mouseButton, searchMethod, tolerance );

		free(fileName);
	}
	else if (IS_CMD( s_commandString, "icmouseclick" ))
	{
		char *fileName;
		fileName = malloc(COMMAND_STR_LEN * sizeof(char));
		if (sscanf( s_commandString, "icmouseclick %s", fileName ) == 1)
			resultPoint = xte_clickMouseImage_location_center( displayLocation, fileName, mouseButton, searchMethod, tolerance );

		free(fileName);
	}
	else if (IS_CMD( s_commandString, "mousedown" ))
	{
		/* The integer argument is optional */
		int mouseButton;
		if (sscanf( s_commandString, "mousedown %i", &mouseButton ) != 1)
			mouseButton = 1;

		xte_mouseDown( displayLocation, mouseButton );

		resultPoint.x = resultPoint.y = -2;
	}
	else if (IS_CMD( s_commandString, "mouseup" ))
	{
		/* The integer argument is optional */
		int mouseButton;
		if (sscanf( s_commandString, "mouseup %i", &mouseButton ) != 1)
			mouseButton = 1;

		xte_mouseUp( displayLocation, mouseButton );

		resultPoint.x = resultPoint.y = -2;
	}
	else if (IS_CMD( s_commandString, "mousejiggle" ))
	{
		xte_mouseJiggle( displayLocation );

		resultPoint.x = resultPoint.y = -2;
	}
	else if (IS_CMD( s_commandString, "mousescrollu" ))
	{
		xte_mouseScrollUp( displayLocation );

		resultPoint.x = resultPoint.y = -2;
	}
	else if (IS_CMD( s_commandString, "mousescrolld" ))
	{
		xte_mouseScrollDown( displayLocation );

		resultPoint.x = resultPoint.y = -2;
	}
	else if (IS_CMD( s_commandString, "keyclick" ))
	{
		char *key;
		key = malloc(COMMAND_STR_LEN * sizeof(char));
		if (sscanf( s_commandString, "keyclick %s", key ) == 1)
			xte_clickKey( displayLocation, key );

		free(key);

		resultPoint.x = resultPoint.y = -2;
	}
	else if (IS_CMD( s_commandString, "keydown" ))
	{
		char *key;
		key = malloc(COMMAND_STR_LEN * sizeof(char));
		if (sscanf( s_commandString, "keydown %s", key ) == 1)
			xte_keyDown( displayLocation, key );

		free(key);

		resultPoint.x = resultPoint.y = -2;
	}
	else if (IS_CMD( s_commandString, "keyup" ))
	{
		char *key;
		key = malloc(COMMAND_STR_LEN * sizeof(char));
		if (sscanf( s_commandString, "keyup %s", key ) == 1)
			xte_keyUp( displayLocation, key );

		free(key);

		resultPoint.x = resultPoint.y = -2;
	}
	else if (IS_CMD( s_commandString, "keystring" ))
	{
		char *keyString;
		keyString = malloc(COMMAND_STR_LEN * sizeof(char));
		if (sscanf( s_commandString, "keystring %s", keyString ) == 1)
			xte_clickKeyStr( displayLocation, keyString );

		free(keyString);

		resultPoint.x = resultPoint.y = -2;
	}
	else if (IS_CMD( s_commandString, "waitfor" ))
	{
		char *fileName;
		fileName = malloc(COMMAND_STR_LEN * sizeof(char));
		if (sscanf( s_commandString, "waitfor %s", fileName ) == 1)
			resultPoint = xte_waitForImage_location( displayLocation, fileName, searchMethod, tolerance, timeout );

		free(fileName);
	}

	/* Note that we will return (-1,-1) implicitly
	 * if we don't recognize the argument */
	return resultPoint;
}

