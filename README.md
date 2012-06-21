libcvautomation
============

Use OpenCV to create a GUI testing framework - replaces Sikuli, Xpresser

###### Why I'm doing this ######
In trying to create an application testing framework for the MOSAIC team at the University of North Carolina at Charlotte, I was very discouraged by what was currently offered.  

Sikuli represented some great ideas, and the built-in IDE was great. Problem being, it crashed whenever I tried to create the first screenshot. Xpresser also looked like it could be great, but died pretty quickly too. Plus, neither of these programs ran on the Prominent North American Enterprise Linux Vendor's software platform.  

As such, starting with a sample OpenCV program to recognize sub-images, I'm attempting to create a GUI testing framework that's more stable, no-questions-asked, simple, and otherwise just usable (specifically from BASH - don't make things more complicated than they need to be).  

###### How it works ######
OpenCV is used for image processing, and should I get around to automating X, I'll likely be using XTE, or XI2, depending on how easy each is.

###### Where we're headed #######
Getting a working program to find sub-images first, add any functionality needed to the library, and then implement X automation
