# Reference: https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall

SRC_DIR = rtx_source/
LIB_DIR = lib/rtx_source/
INCLUDE_PATH = glm-0.9.7.1 freeImage
# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
all: main

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
main:  Geo Image.o Main.o
	$(CC) $(CFLAGS) -o main Sphere.o Triangle.o Image.o Main.o

Geo:  $(SRC_DIR)Sphere.cpp $(SRC_DIR)Triangle.cpp $(LIB_DIR)Intersection.h
	$(CC) $(CFLAGS) -c -I$(INCLUDE_PATH) $(SRC_DIR)Sphere.cpp $(SRC_DIR)Triangle.cpp

# Triangle.o:  $(SRC_DIR)Triangle.cpp
# 	$(CC) $(CFLAGS) -c -I$(INCLUDE_PATH) $(SRC_DIR)Triangle.cpp

Image.o:  $(SRC_DIR)Image.cpp
	$(CC) $(CFLAGS) -c -I$(INCLUDE_PATH) $(SRC_DIR)Image.cpp

Main.o: $(SRC_DIR)Main.cpp lib/Screenshot.h lib/FreeImage.h src/Scene.inl
	$(CC) $(CFLAGS) -c -I$(INCLUDE_PATH) $(SRC_DIR)Main.cpp

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) count *.o *~
