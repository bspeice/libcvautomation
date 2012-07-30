#!/bin/bash - 
#===============================================================================
#
#          FILE: packageDebian.sh
# 
#         USAGE: ./packageDebian.sh 
# 
#   DESCRIPTION: 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Bradlee Speice (), bspeice@uncc.edu
#  ORGANIZATION: 
#      REVISION:  ---
#===============================================================================

#This script is a simple wrapper for building the .deb packages for libcvautomation
#It is not intended to be bullet-proof - if it gets broken I will do my best to
#provide bugfixes, but this is a fairly low priority.

#Also, this script is intended to be run from the Git source, and *not* from
#a release tarball.

set -o errexit

if [ -z "$1" ]; then
	echo "Building without signing the package..."
fi

PACKAGE_NAME=`grep AC_INIT configure.ac | cut -d'(' -f2 | cut -d',' -f1`
PACKAGE_VERSION=`grep AC_INIT configure.ac | cut -d',' -f2 | tr -d [:space:]`

./autogen.sh
./configure
make -j`grep processor /proc/cpuinfo | wc -l`
make dist

BUILD_DIR=`mktemp -d`
TARBALL="${PACKAGE_NAME}-${PACKAGE_VERSION}.tar.gz"
cp $TARBALL $BUILD_DIR
cp $TARBALL $BUILD_DIR/`echo $TARBALL | sed 's/-/_/g;s/tar/orig.tar/'`
tar xf $TARBALL -C $BUILD_DIR
cp debian $PACKAGE_NAME-$PACKAGE_VERSION -r
cd $BUILD_DIR/$PACKAGE_NAME-$PACKAGE_VERSION

if [ -z "$1" ]; then
	debuild
else
	debuild -k$1
fi

echo "Package successfully built in $BUILD_DIR."
