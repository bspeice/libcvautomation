libcvautomation
============

Use OpenCV to create a GUI testing framework - replaces Sikuli, Xpresser

## Why I'm doing this ##
In trying to create an application testing framework for the MOSAIC team at the University of North Carolina at Charlotte, I was very discouraged by what was currently offered.  

Sikuli represented some great ideas, and the built-in IDE was great. Problem being, it crashed whenever I tried to create the first screenshot. Xpresser also looked like it could be great, but died pretty quickly too. Plus, neither of these programs ran on the Prominent North American Enterprise Linux Vendor's software platform.  

As such, starting with a sample OpenCV program to recognize sub-images, I'm attempting to create a GUI testing framework that's more stable, no-questions-asked, simple, and otherwise just usable (specifically from BASH - don't make things more complicated than they need to be.)

#### How it works ####
OpenCV is used for image processing, and XTestExtension is used for driving X11. Reference implementations are given, and they are fairly full-featured.

## Installation Instructions ##
#### RPM ####
Place the following content into a file named `/etc/yum.repos.d/libcvautomation.repo`:

	[libcvautomation]
	name=Libcvautomation RPM repository
	baseurl=http://djbushido.github.com/libcvautomation/rpm
	enabled=1
	gpgcheck=0 

#### APT ####
Place the following lines into your `/etc/apt/sources.list`:

	#Libcvautomation Repository
	deb http://djbushido.github.com/libcvautomation/apt libcvautomation/
	deb-src http://djbushido.github.com/libcvautomation/apt libcvautomation-source/ 

#### Tarball ####
The tarball can be downloaded from the [downloads](https://github.com/DjBushido/libcvautomation/downloads) page.
Once you have it, just `./configure; make; make install`


## Where we're headed ##
At this point, most everything is functionally done. I'll develop python bindings to make interfacing with the library simpler, but it will be mostly bugfixes until I can get to those. If there are any suggestions, please let me know!

## Get in contact ##
If you have a suggestion, comment, question, concern, or otherwise, feel free to email me at <bspeice@uncc.edu>. This product is developed with the community in mind, so if there's any feedback to be had I welcome it.
