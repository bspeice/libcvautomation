#!/bin/bash - 
#===============================================================================
#
#          FILE: update-packages.sh
# 
#         USAGE: ./update-packages.sh 
# 
#   DESCRIPTION: 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#  ORGANIZATION: 
#      REVISION:  ---
#===============================================================================

dpkg-scanpackages libcvautomation /dev/null | gzip -9c > libcvautomation/Packages.gz
dpkg-scansources libcvautomation-source /dev/null | gzip -9c > libcvautomation-source/Sources.gz
