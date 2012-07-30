#!/bin/bash - 
#===============================================================================
#
#          FILE: packageRPM.sh
# 
#         USAGE: ./packageRPM.sh 
# 
#   DESCRIPTION: 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Bradlee Speice (), bspeice.nc@gmail.com
#  ORGANIZATION: 
#       CREATED: 07/30/2012 11:29:28 AM EDT
#      REVISION:  ---
#===============================================================================

#This script is a simple wrapper for building the .rpm packages for libcvautomation
#It is not intended to be bullet-proof - if it gets broken I will do my best to
#provide bugfixes, but this is a fairly low priority.

#Also, this script is intended to be run from the Git source, and *not* from
#a release tarball.
set -o errexit

if [ -z "$SIGN_PACKAGE" ]; then
	echo "Building without signing packages..."
fi

PACKAGE_NAME=`grep AC_INIT configure.ac | cut -d'(' -f2 | cut -d',' -f1`
PACKAGE_VERSION=`grep AC_INIT configure.ac | cut -d',' -f2 | tr -d [:space:]`

./autogen.sh
./configure
make -j`grep processor /proc/cpuinfo | wc -l`
make dist

if [ ! -d $HOME/rpmbuild ]; then
	echo "Could not find the rpmbuild directory!"
	echo "Please make sure your packaging environment is set up correctly."
fi

TARBALL="${PACKAGE_NAME}-${PACKAGE_VERSION}.tar.gz"
cp $TARBALL $HOME/rpmbuild/SOURCES
cp rpm/libcvautomation.spec $HOME/rpmbuild/SPECS
cd $HOME/rpmbuild/SPECS
if [ -z "$SIGN_PACKAGE" ]; then
	rpmbuild -ba libcvautomation.spec
else
	rpmbuild -ba --sign libcvautomation.spec
fi

echo "Package successfully built in $HOME/rpmbuild/RPMS."
