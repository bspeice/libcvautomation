libcvautomation
============

Use OpenCV to create a GUI testing framework - replaces Sikuli, Xpresser

###### Why I'm doing this ######
In trying to create an application testing framework for the MOSAIC team at the University of North Carolina at Charlotte, I was very discouraged by what was currently offered.  

Sikuli represented some great ideas, and the built-in IDE was great. Problem being, it crashed whenever I tried to create the first screenshot. Xpresser also looked like it could be great, but died pretty quickly too. Plus, neither of these programs ran on the Prominent North American Enterprise Linux Vendor's software platform.  

As such, starting with a sample OpenCV program to recognize sub-images, I'm attempting to create a GUI testing framework that's more stable, no-questions-asked, simple, and otherwise just usable (specifically from BASH - don't make things more complicated than they need to be.)

###### How it works ######
OpenCV is used for image processing, and XTestExtension is used for driving X11. I'll be looking into XInput2 eventually, but the focus is on getting something stable out the door first.

###### Where we're headed #######
Image recognition and basic X automation are done. From here, code more advanced X automations (ex. Giving the library a string of text to enter, rather than just a character at a time), and clean up the code.

After the basic functionality is done (Image recognition and automation) I'll develop python bindings to make interfacing with the library simpler. If there are any suggestions, please let me know!

###### Get in contact #######
If you have a suggestion, comment, question, concern, or otherwise, feel free to email me at <bspeice@uncc.edu>. This product is developed with the community in mind, so if there's any feedback to be had I welcome it.
