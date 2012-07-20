/*
 * =====================================================================================
 *
 *       Filename:  libcvautomation-xinput.h
 *
 *    Description:  
 *
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

#define IS_CMD( x, y ) strncmp( x, y, strlen( y ) ) == 0
#define COMMAND_STR_LEN 512

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

/* Scroll the mouse up */
void xte_mouseScrollUp ( Display *displayLocation );

/* Scroll the mouse down */
void xte_mouseScrollDown ( Display *displayLocation );

/* Press and release a key 
 * Note that we use a string for *key, since keys like "space" are still valid. */
void xte_clickKey ( Display *displayLocation, char *key );

/* Press and release keys in a string */
void xte_clickKeyStr ( Display *displayLocation, char *string );

/* Press a key down */
void xte_keyDown ( Display *displayLocation, char *key );

/* Release a key */
void xte_keyUp ( Display *displayLocation, char *key );

/* Wait for an image to show up on screen */
cvaPoint xte_waitForImage ( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance, int timeout );

/* Wait for an image from file to show up on screen */
cvaPoint xte_waitForImage_location ( Display *displayLocation, const char *fileName, int searchMethod, int tolerance, int timeout );

/* Use one of the functions by command name */
cvaPoint xte_commandString ( Display *displayLocation, char *commandString, int mouseButton, int searchMethod, int tolerance, int timeout );

#endif /* LIBCVAUTOMATION_XTEST_H */

/* Doxygen information */
/** \file libcvautomation-xtest.h
 * \brief The source code to access the XTest extension inside libcvautomation
 * \details This source file builds in the necessary functionality to drive the X11 server in libcvautomation
 * \author Bradlee Speice
 * \date 7/18/2012
 */

/** \page xtest_key_strings XTest Key Strings
This page describes the various extra key strings to use with X11.
The following list is generated with this command:
\code xmodmap -pke | cut -d'=' -f2 |  sed 's/ /\n/g' | tr -s '\n' | awk '{ print length(), $0 | "sort -n" }' | cut -d' ' -f2 | uniq \endcode
\code
0
1
2
3
4
5
6
7
8
9
a
A
b
B
c
C
d
D
e
E
f
F
g
G
h
H
i
I
j
J
k
K
l
L
m
M
n
N
o
O
p
P
q
Q
r
R
s
S
t
T
u
U
v
V
w
W
x
X
y
Y
z
Z
at
F1
F2
F3
F4
F5
F6
F7
F8
F9
Up
bar
End
F10
F11
F12
Tab
Down
Home
KP_0
KP_1
KP_2
KP_3
KP_4
KP_5
KP_6
KP_7
KP_8
KP_9
Left
less
Menu
Next
plus
Alt_L
Break
colon
comma
equal
grave
KP_Up
minus
Pause
Print
Prior
Right
slash
space
aacute
Aacute
dagger
Delete
dollar
eacute
Eacute
Escape
exclam
iacute
Iacute
Insert
KP_Add
KP_End
Meta_L
oacute
Oacute
period
Return
uacute
Uacute
greater
Hyper_L
KP_Down
KP_Home
KP_Left
KP_Next
percent
Shift_L
Shift_R
Super_L
Super_R
Sys_Req
XF86WWW
asterisk
KP_Begin
KP_Enter
KP_Equal
KP_Prior
KP_Right
NoSymbol
Num_Lock
question
quotedbl
XF86Back
XF86Mail
XF86Stop
XF86WLAN
ampersand
backslash
BackSpace
braceleft
brokenbar
Caps_Lock
Control_L
Control_R
KP_Delete
KP_Divide
KP_Insert
parenleft
semicolon
XF86Eject
XF86Sleep
adiaeresis
Adiaeresis
apostrophe
asciitilde
braceright
ediaeresis
Ediaeresis
idiaeresis
KP_Decimal
numbersign
odiaeresis
Odiaeresis
parenright
udiaeresis
Udiaeresis
underscore
XF86Reload
XF86Search
XF86WakeUp
asciicircum
bracketleft
KP_Multiply
KP_Subtract
Mode_switch
Scroll_Lock
XF86Battery
XF86Display
XF86Forward
XF86_Ungrab
bracketright
doubledagger
ISO_Left_Tab
XF86PowerOff
XF86AudioMute
XF86AudioNext
XF86AudioPrev
XF86AudioStop
XF86Favorites
XF86AudioMedia
XF86AudioPause
XF86Calculator
XF86_ClearGrab
XF86MyComputer
XF86_Next_VMode
XF86_Prev_VMode
ISO_Level3_Shift
Terminate_Server
XF86_Switch_VT_1
XF86_Switch_VT_2
XF86_Switch_VT_3
XF86_Switch_VT_4
XF86_Switch_VT_5
XF86_Switch_VT_6
XF86_Switch_VT_7
XF86_Switch_VT_8
XF86_Switch_VT_9
XF86KbdLightOnOff
XF86_Switch_VT_10
XF86_Switch_VT_11
XF86_Switch_VT_12
Pointer_EnableKeys
XF86KbdBrightnessUp
XF86MonBrightnessUp
XF86AudioLowerVolume
XF86AudioRaiseVolume
XF86KbdBrightnessDown
XF86MonBrightnessDown
\endcode
\warning Please note that each key string above is first translated into a key code, and then into the actual key click. Thus, while you might intend to press "dollar", it will actually come out as "4". If you need a <tt>'$'</tt> to come out, use the <tt>'keystring $'</tt> command to \ref xte_commandString() or <tt>'key_str $'</tt> function in the BASH wrapper - see the \ref wrapper_functions.
 */

/** \page xtest_command_strings xte_commandString() Command Strings
This page describes the various command strings available for the \ref xte_commandString() function.
\section mouseclick Mouse Click
\code 'mouseclick <button_number>' \endcode
Click the mouse button \c <button_number> in-place.

\section imouseclick Image Mouse Click
\code 'imouseclick <image_name>' \endcode
Click the mouse at an image's top-left corner.

\section icmouseclick Image Mouse Click (Centered)
\code 'icmouseclick <image_name>' \endcode
Click the mouse at an image's center.

\section mousexy Mouse XY Move
\code 'mousexy <x-coord> <y-coord>' \endcode
Move the mouse to an absolute coordinate.
\warning The \c <x-coord> and \c <y-coord> are expected to be integers.

\section mouserxy Mouse XY Move (Relative)
\code 'mouserxy <x-increment> <y-increment>' \endcode
Move the mouse by the given x and y values (relative motion).
\par A positive X increment will move the mouse to the right, and a positive Y increment will move the mouse down.
\warning The \c <x-increment> and \c <y-increment> are expected to be integers.

\section mouseimage Mouse Image Move
\code 'mouseimage <image_name>' \endcode
Move the mouse to an image's top-left corner.

\section cmouseimage Mouse Image Move (Centered)
\code 'cmouseimage <image_name>' \endcode
Move the mouse to an image's center.

\section mousedown Mouse Button Down
\code 'mousedown <button_number>' \endcode
Push and leave down a mouse button.

\section mouseup Mouse Button Up
\code 'mouseup <button_number>' \endcode
Release  mouse button \c <button_number>

\section mousejiggle Mouse Jiggle
\code 'mousejiggle' \endcode
Jiggle the mouse (helps to activate some widgets). Moves the mouse right and down 1 pixel, and then back.

\section mousescrolld Mouse Scroll Down
\code 'mousescrolld' \endcode
Scroll the mouse down 1 time - depending on window manager settings, etc., this may be multiple lines.
\note This is a wrapper function for clicking button 4 on the mouse

\section mousescrollu Mouse Scroll Up
\code 'mousescrollu' \endcode
Scroll the mouse up 1 time - depending on window manager settings, etc., this may be multiple lines.
\note This is a wrapper function for clicking button 5 on the mouse

\section keyclick Key Button Click
\code 'keyclick <key_name>' \endcode
Push and release a keyboard key. This can be a key like \c 'a', \c 'b', or something fancy like \c 'space'. Please see \ref xtest_key_strings for a full list of special keys.

\section keydown Key Button Down
\code 'keydown <key_name>' \endcode
Push down <em>but do not release</em> a keyboard key. This can be a key like \c 'a', \c 'b', or something fancy like \c 'space'. Please see \ref xtest_key_strings for a full list of special keys.

\section keyup Key Button Up
\code 'keyup <key_name>' \endcode
Release a keyboard key. This can be a key like \c 'a', \c 'b', or something fancy like \c 'space'. Please see \ref xtest_key_strings for a full list of special keys.

\section keystring Keyboard Input String
\code 'keystring <string>' \endcode
Input a string of text to the X11 server. For example, inputting 'Hello, world!" will act as if you typed 'Hello, world!' from the keyboard.
\warning Unlike \ref keydown, \ref keyup, and \ref keyclick, this function can not handle special keys like 'space'.

\section waitfor Wait for Image
\code 'waitfor <image_name>' \endcode
Wait for an image to show up on screen. For example, this can be used to make sure a button exists before clicking it.
*/

/** \def IS_CMD (x, y)
 * \brief Checks if string \c 'x' is in \c 'y'
 * \details Performs a safe check to see if x is in y - this way, you can check that \c "command" is inside \c "command argument"*/

/** \def COMMAND_STR_LEN
 * \brief Specifies the maximum length of a command string*/

/** \fn Bool xte_XTestSupported ( Display *displayLocation );
 * \brief Check if the XTest extension is supported
 * \param displayLocation The Display to check if XTest is supported on
 * \returns True if XTest is supported, False otherwise
 * \warning The program using this library is responsible for checking to see if XTest is supported.
 */

/** \fn cvaPoint xte_pointerLocation ( Display *displayLocation );
 * \brief Grab the current location of the pointer
 * \param displayLocation The Display of which to grab the pointer location from
 * \returns cvaPoint with the current location of the pointer
 */

/** \fn void xte_clickMouse ( Display *displayLocation, int mouseButton );
 * \brief Click the mouse in its current location
 * \details Perform a mouse-down and mouse-up event on button \c mouseButton
 * \param displayLocation The Display of which to click the mouse on
 * \param mouseButton The mouse button to click
 */

/** \fn void xte_clickMouseXY ( Display *displayLocation, int xLocation, int yLocation, int mouseButton );
 * \brief Click the mouse button at an absolute location
 * \details Move the mouse to location (\c xLocation, \c yLocation ) and then click button \c mouseButton
 * \param displayLocation The Display of which to click the mouse on
 * \param xLocation The X-coordinate to move the mouse to before clicking
 * \param yLocation The Y-location to move the mouse to before clicking
 * \param mouseButton The mouse button to click
 */

/** \fn void xte_clickMouseRXY ( Display *displayLocation, int xIncrement, int yIncrement, int mouseButton );
 * \brief Click the mouse button at a relative location
 * \details Move the mouse horizontally \c xIncrement and vertically \c yIncrement before clicking button \c mouseButton
 * \param displayLocation The Display of which to click the mouse on
 * \param xIncrement Move the mouse horizontally this many pixels - positive value is motion to the right
 * \param yIncrement Move the mouse vertically this many pixels - positive value is motion downwards
 * \param mouseButton The mouse button to click
 */

/** \fn cvaPoint xte_clickMouseImage ( Display *displayLocation, IplImage *subImage, int mouseButton, int searchMethod, int tolerance );
 * \brief Click the mouse based on location of an image
 * \details Wraps grabbing the X11 root window of \c displayLocation, finding \c subImage in this display, moving the mouse to that location, and then clicking \c mouseButton. The return value can be ignored, the mouse will already have been clicked there.
 * \param displayLocation The Display of which to click the mouse on
 * \param subImage The sub image (in IplImage format) to find in the root X11 window
 * \param mouseButton The mouse button to click
 * \param searchMethod The search method to use when searching for \c subImage in the root X11 window
 * \param tolerance The tolerance to use when searching for \c subImage in the root X11 window
 * \see \ref libcvautomation_search_methods
 * \returns The location of where the mouse was clicked. This will be (-1,-1) if there was an error, in which case the mouse will not have been clicked.
 */

/** \fn cvaPoint xte_clickMouseImage_location ( Display *displayLocation, const char *fileName, int mouseButton, int searchMethod, int tolerance );
 * \brief Click the mouse based on the location of an image from file
 * \details Wraps grabbing the X11 root window of \c displayLocation, finding the sub image from \c fileName in this display, moving the mouse to that location, and then clicking \c mouseButton. The return value can be ignored, the mouse will already have been clicked there.
 * \param displayLocation The Display of which to click the mouse on
 * \param fileName The file name from which to load the sub-image
 * \param mouseButton The mouse button to click
 * \param searchMethod The search method to use when searching for the sub image in the root X11 window
 * \param tolerance The tolerance to use when searching for the sub image in the root X11 window
 * \see \ref libcvautomation_search_methods
 * \returns The location of where the mouse was clicked. This will be (-1,-1) if there was an error, in which case the mouse will not have been clicked.
 */

/** \fn cvaPoint xte_clickMouseImage_center ( Display *displayLocation, IplImage *subImage, int mouseButton, int searchMethod, int tolerance );
 * \brief Click the mouse based on center location of an image
 * \details Wraps grabbing the X11 root window of \c displayLocation, finding the center of \c subImage in this display, moving the mouse to that location, and then clicking \c mouseButton. The return value can be ignored, the mouse will already have been clicked there.
 * \param displayLocation The Display of which to click the mouse on
 * \param subImage The sub image (in IplImage format) to find in the root X11 window
 * \param mouseButton The mouse button to click
 * \param searchMethod The search method to use when searching for \c subImage in the root X11 window
 * \param tolerance The tolerance to use when searching for \c subImage in the root X11 window
 * \see \ref libcvautomation_search_methods
 * \returns The location of where the mouse was clicked. This will be (-1,-1) if there was an error, in which case the mouse will not have been clicked.
 */

/** \fn cvaPoint xte_clickMouseImage_location_center ( Display *displayLocation, const char *fileName, int mouseButton, int searchMethod, int tolerance );
 * \brief Click the mouse based on the center location of an image from file
 * \details Wraps grabbing the X11 root window of \c displayLocation, finding the center location of the sub image from \c fileName in this display, moving the mouse to that location, and then clicking \c mouseButton. The return value can be ignored, the mouse will already have been clicked there.
 * \param displayLocation The Display of which to click the mouse on
 * \param fileName The file name from which to load the sub-image
 * \param mouseButton The mouse button to click
 * \param searchMethod The search method to use when searching for the sub image in the root X11 window
 * \param tolerance The tolerance to use when searching for the sub image in the root X11 window
 * \see \ref libcvautomation_search_methods
 * \returns The location of where the mouse was clicked. This will be (-1,-1) if there was an error, in which case the mouse will not have been clicked.
 */

/** \fn void xte_hoverMouseXY ( Display *displayLocation, int xLocation, int yLocation );
 * \brief Move the mouse to a location, but do not click it
 * \param displayLocation The Display of which to move the mouse
 * \param xLocation The X-coordinate of which to move the mouse
 * \param yLocation The Y-coordinate of which to move the mouse
 */

/** \fn void xte_hoverMouseRXY ( Display *displayLocation, int xIncrement, int yIncrement );
 * \brief Move the mouse to a relative location, but do not click it
 * \param displayLocation The Display of which to move the mouse
 * \param xIncrement How far to move the mouse horizontally. Positive values indicate motion to the right.
 * \param yIncrement How far to move the mouse vertically. Positive values indicate motion downward.
 */

/** \fn cvaPoint xte_hoverMouseImage ( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance );
 * \brief Move the mouse based on location of an image
 * \details Wraps grabbing the X11 root window of \c displayLocation, finding \c subImage in this display, and then moving the mouse to that location. The return value can be ignored, the mouse will already have been moved there.
 * \param displayLocation The Display of which to move the mouse on
 * \param subImage The sub image (in IplImage format) to find in the root X11 window
 * \param searchMethod The search method to use when searching for \c subImage in the root X11 window
 * \param tolerance The tolerance to use when searching for \c subImage in the root X11 window
 * \see \ref libcvautomation_search_methods
 * \returns The location of where the mouse was moved. This will be (-1,-1) if there was an error, in which case the mouse will not have been moved.
 */

/** \fn cvaPoint xte_hoverMouseImage_location ( Display *displayLocation, const char *filename, int searchMethod, int tolerance );
 * \brief Move the mouse based on location of an image from file
 * \details Wraps grabbing the X11 root window of \c displayLocation, finding the sub image from \c fileName in this display,  and then moving the mouse to that location. The return value can be ignored, the mouse will already have been moved there.
 * \param displayLocation The Display of which to move the mouse on
 * \param filename The file name from which to load the sub-image
 * \param searchMethod The search method to use when searching for the sub image in the root X11 window
 * \param tolerance The tolerance to use when searching for the sub image in the root X11 window
 * \see \ref libcvautomation_search_methods
 * \returns The location of where the mouse was moved. This will be (-1,-1) if there was an error, in which case the mouse will not have been moved.
 */

/** \fn cvaPoint xte_hoverMouseImage_center ( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance );
 * \brief Move the mouse based on center location of an image
 * \details Wraps grabbing the X11 root window of \c displayLocation, finding the center of \c subImage in this display, and then moving the mouse to that location. The return value can be ignored, the mouse will already have been moved there.
 * \param displayLocation The Display of which to move the mouse on
 * \param subImage The sub image (in IplImage format) to find in the root X11 window
 * \param searchMethod The search method to use when searching for \c subImage in the root X11 window
 * \param tolerance The tolerance to use when searching for \c subImage in the root X11 window
 * \see \ref libcvautomation_search_methods
 * \returns The location of where the mouse was moved. This will be (-1,-1) if there was an error, in which case the mouse will not have been moved.
 */

/** \fn cvaPoint xte_hoverMouseImage_location_center ( Display *displayLocation, const char *fileName, int searchMethod, int tolerance );
 * \brief Move the mouse based on the center location of an image from file
 * \details Wraps grabbing the X11 root window of \c displayLocation, finding the center location of the sub image from \c fileName in this display, and then moving the mouse to that location. The return value can be ignored, the mouse will already have been moved there.
 * \param displayLocation The Display of which to move the mouse on
 * \param fileName The file name from which to load the sub-image
 * \param searchMethod The search method to use when searching for the sub image in the root X11 window
 * \param tolerance The tolerance to use when searching for the sub image in the root X11 window
 * \see \ref libcvautomation_search_methods
 * \returns The location of where the mouse was moved. This will be (-1,-1) if there was an error, in which case the mouse will not have been moved.
 */

/** \fn void xte_mouseDown ( Display *displayLocation, int mouseButton );
 * \brief Press a mouse button down, and do not release it
 * \param displayLocation The Display of which to push a mouse button down
 * \param mouseButton The mouse button to push down
 */

/** \fn void xte_mouseUp ( Display *displayLocation, int mouseButton );
 * \brief Release a mouse button
 * \param displayLocation The Display of which to release a mouse button
 * \param mouseButton The mouse button to release
 */

/** \fn void xte_mouseJiggle ( Display *displayLocation );
 * \brief Jiggle the mouse in place
 * \details This moves the mouse down and right one pixel, and then back. This may be needed to activate menu items, etc.
 * \param displayLocation The Display of which to move the mouse
 */

/** \fn void xte_mouseScrollUp ( Display *displayLocation );
 * \brief Scroll the mouse up
 * \details This moves the mouse scroll wheel up one rotation, which may be multiple lines. What this really does is click mouse button 4.
 * \param displayLocation The Display of which to scroll the mouse
 */

/** \fn void void xte_mouseScrollDown ( Display *displayLocation );
 * \brief Scroll the mouse down
 * \details This moves the mouse scroll wheel down one rotation, which may be multiple lines. What this really does is click mouse button 5.
 * \param displayLocation The Display of which to scroll the mouse
 */

/** \fn void xte_clickKey ( Display *displayLocation, char *key );
 * \brief Press and release a keyboard key
 * \details This method allows you to press and release a key, where the key may be \c 'a', \c 'b', or maybe something fancy like \c 'space'. Please see \ref xtest_key_strings for a full list of keys.
 * \param displayLocation The Display of which to click a key
 * \param key The key to click as a string
 * \see \ref xtest_key_strings
 */

/** \fn void xte_clickKeyStr ( Display *displayLocation, char *string );
 * \brief Input a string of characters to the X Server
 * \details Instead of specifying a single character to enter at a time (\c 'a', \c 'space') this function allows you to enter an entire string (\c 'Hello, World!') at a time.
 * \param displayLocation The Display of which to enter a key string on
 * \param string The key string to input to the X Server
 */

/** \fn void xte_keyDown ( Display *displayLocation, char *key );
 * \brief Press a key down, but do not release it
 * \details This method allows you to push down a key, where the key may be \c 'a', \c 'b', or maybe something fancy like \c 'space'. Please see \ref xtest_key_strings for a full list of keys.
 * \param displayLocation The Display of which to push down a key
 * \param key The key to click as a string
 * \see \ref xtest_key_strings
 */

/** \fn void xte_keyUp ( Display *displayLocation, char *key );
 * \brief Release a key
 * \details This method allows you to release a key, where the key may be \c 'a', \c 'b', or maybe something fancy like \c 'space'. Please see \ref xtest_key_strings for a full list of keys.
 * \param displayLocation The Display of which to release a key
 * \param key The key to click as a string
 * \see \ref xtest_key_strings
 */
/** \fn cvaPoint xte_waitForImage ( Display *displayLocation, IplImage *subImage, int searchMethod, int tolerance, int timeout );
 * \brief Wait for an image to show up on screen
 * \details This method allows you to search for an image on screen and wait for it to show up - this way you can make sure an image exists, and then respond to it. Also makes error checking easy.
 * \param displayLocation The Display of which to search for an image
 * \param subImage The sub image to search for
 * \param searchMethod The search method to use when searching for \c subImage
 * \param tolerance The tolerance to use when searching for \c tolerance
 * \param timeout The time (in seconds) to search for the image
 * \see \ref libcvautomation_search_methods
 */

/** \fn cvaPoint xte_waitForImage_location ( Display *displayLocation, const char *fileName, int searchMethod, int tolerance, int timeout );
 * \brief Wait for an image from file to show up on screen
 * \details This method allows you to search for an image on screen and wait for it to show up - this way you can make sure an image exists, and then respond to it. Also makes error checking easy.
 * \param displayLocation The Display of which to search for an image
 * \param fileName The file to load an image from before searching
 * \param searchMethod The search method to use when searching for \c subImage
 * \param tolerance The tolerance to use when searching for \c tolerance
 * \param timeout The time (in seconds) to search for the image
 * \see \ref libcvautomation_search_methods
 */

/** \fn cvaPoint xte_commandString ( Display *displayLocation, char *commandString, int mouseButton, int searchMethod, int tolerance, int timeout );
 * \brief Execute a command where the command is coming from a string
 * \details This function allows you to input a command to libcvautomation from a string. For example, to click a mouse button, you would use the \c command 'mouseclick'. Please note that some <tt>command</tt>s may need arguments to the string, and some may use function arguments. See \ref xtest_command_strings for a full list of command and arguments
 * \param displayLocation The Display of which to operate on
 * \param commandString The command string to execute - limit to \ref COMMAND_STR_LEN characters
 * \param mouseButton The mouse button to click if it is needed by the command being executed
 * \param searchMethod The search method to use if it is needed by the command being executed
 * \param tolerance The tolerance to use if it is needed by the command being executed
 * \param timeout The time in seconds to wait for an image to be displayed when using the \c waitfor command.
 * \see \ref xtest_command_strings
 * \see \ref libcvautomation_search_methods
 */
