#!/bin/bash - 
#===============================================================================
#
#          FILE: openCVLogo.sh
# 
#         USAGE: ./openCVLogo.sh 
# 
#   DESCRIPTION: This is a test script to demonstrate libcvautomation
#					We are going to find different sections of the OpenCV logo
#					in itself.
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Bradlee Speice (), bspeice.nc@gmail.com
#  ORGANIZATION: 
#       CREATED: 06/21/2012 03:45:19 PM EDT
#      REVISION:  ---
#===============================================================================

CVAMATCH=`which cva-match`

if [ ! -x "$CVA_MATCH" ]; then
	echo "Could not find the cva-match binary! Can't continue..."
	exit 255
fi

echo
echo "Finding the red circle in the OpenCV logo..."
echo "The red circle is located at: `$CVA_MATCH -r opencvlogo.png -s redcircle.png -p ', ' | cut -d',' -f2-`"
echo "Finding the blue circle in the OpenCV logo..."
echo "The blue circle is located at: `$CVA_MATCH -r opencvlogo.png -s bluecircle.png -p ', ' | cut -d',' -f2-`"
echo "Finding the green circle in the OpenCV logo..."
echo "The green circle is located at: `$CVA_MATCH -r opencvlogo.png -s greencircle.png -p ', ' | cut -d',' -f2-`"
echo
