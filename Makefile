#===============================================================================
#
#         File: Makefile
#  Description: 
#
#        Usage: make              (generate executable(s)                    )
#               make clean        (remove objects, executables, prerequisits )
#               make tarball      (generate compressed archive               )
#               make zip          (generate compressed archive               )
#                                  
#       Author: Bradlee Speice
#        Email: bspeice@uncc.edu
#      Created: 6/21/2012
#
#===============================================================================


CC              = gcc
CCP             = g++
CFLAGS          = -c -g -Wall -fPIC
LDFLAGS         = -g
SYS_LIBS        = 
TARBALL_EXCLUDE = "*.{o,gz,zip}"
ZIP_EXCLUDE     = *.o *.gz *.zip

SRC_DIR			= src
OBJ_DIR			= obj
BIN_DIR			= bin
LIB_DIR			= lib

CV_FLAGS		= `pkg-config --cflags opencv`
CV_LIBS			= `pkg-config --libs opencv`
X11_FLAGS		= `pkg-config --cflags x11`
X11_LIBS		= `pkg-config --libs x11`

EXECUTABLE		= $(BIN_DIR)/cva-match
LIBRARIES		= $(LIB_DIR)/libcvautomation.so
SOURCES			= $(SRC_DIR)/cva-match.c $(SRC_DIR)/libcvautomation-x11.c $(SRC_DIR)/libcvautomation-opencv.c
CVAM_OBJECTS	= $(OBJ_DIR)/cva-match.o
CVAM_SOURCES	= $(SRC_DIR)/cva-match.c
LIBCVAM_OBJECTS	= $(OBJ_DIR)/libcvautomation-opencv.o $(OBJ_DIR)/libcvautomation-x11.o
LIBCVAM_SOURCES = $(SRC_DIR)/libcvautomation-opencv.c $(SRC_DIR)/libcvautomation-x11.c

TARGETS	= $(OBJECTS) $(LIBRARIES) $(EXECUTABLE)

#---------- targets --------------------------------------
all:	.dirs	$(TARGETS)

#---------- installation directories ---------------------
.dirs:
	mkdir -p $(SRC_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(LIB_DIR)
	touch .dirs

#---------- link libcvautomation -------------------------
$(LIB_DIR)/libcvautomation.so:	$(LIBCVAM_OBJECTS)
					$(CC) $(LDFLAGS) -o $@ $(LIBCVAM_OBJECTS)  $(SYS_LIBS) $(CV_LIBS) $(X11_LIBS) -shared

#---------- link cva-match program -----------------------
$(BIN_DIR)/cva-match:		$(CVAM_OBJECTS)
					$(CC) $(LDFLAGS) -o $@ $(CVAM_OBJECTS)  $(SYS_LIBS) -L$(LIB_DIR) -lcvautomation

#---------- compile libcvautomation-opencv.c ------------
$(OBJ_DIR)/libcvautomation-opencv.o:	src/libcvautomation-opencv.c
					$(CC) $(CFLAGS) -o $@ src/libcvautomation-opencv.c $(CV_FLAGS)

#---------- compile libcvautomation-x11.c ----------------
$(OBJ_DIR)/libcvautomation-x11.o:	src/libcvautomation-x11.c
					$(CC) $(CFLAGS) -o $@ src/libcvautomation-x11.c $(X11_FLAGS)

#---------- compile cva-match ----------------------------
$(OBJ_DIR)/cva-match.o:	$(CVAM_SOURCES)
					$(CC) $(CFLAGS) -o $@ $(CVAM_SOURCES)


#---------- tarball --------------------------------------
tarball:
					localdir=`pwd`; localdir=$${localdir##*/}; \
					rm --force $$localdir.tar.gz;              \
					tar --exclude=$(TARBALL_EXCLUDE)           \
					    --create                               \
					    --gzip                                 \
					    --verbose                              \
					    --file  $$localdir.tar.gz *

#---------- zip ------------------------------------------
zip:
					localdir=`pwd`; localdir=$${localdir##*/}; \
					zip -r  $$localdir.zip * -x $(ZIP_EXCLUDE)

#---------- clear up -------------------------------------
clean:
				rm -f $(OBJ_DIR)/*
				rm -f $(BIN_DIR)/*
				rm -f $(LIB_DIR)/*

distclean:
				rm -rf $(OBJ_DIR)
				rm -rf $(BIN_DIR)
				rm -rf $(LIB_DIR)
				rm .dirs

