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
# CC = g++
# CFLAGS  = -g -Wall

# SRC_DIR = src/
# LIB_DIR = lib/
# INCLUDE_PATH = -I./glm-0.9.7.1 -I./
# L_FLAGS = -lfreeimage
# # typing 'make' will invoke the first target entry in the file 
# # (in this case the default target entry)
# # you can name this target entry anything, but "default" or "all"
# # are the most commonly used names by convention
# #
# all: build

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
# main:  Image.o Camera.o Scene.o Main.o
# 	$(CC) $(CFLAGS) -o Geometry.o Triangle.o Image.o Camera.o Scene.o Main.o

# Geo: $(SRC_DIR)Triangle.cpp src/Geometry.cpp $(LIB_DIR)Intersection.h
# 	$(CC) $(CFLAGS) -c -I$(INCLUDE_PATH) $(SRC_DIR)Triangle.cpp src/Geometry.cpp -l$(L_FLAGS)

# # Triangle.o:  $(SRC_DIR)Triangle.cpp
# # 	$(CC) $(CFLAGS) -c -I$(INCLUDE_PATH) $(SRC_DIR)Triangle.cpp

# Image.o:  $(SRC_DIR)Image.cpp
# 	$(CC) $(CFLAGS) -c -I$(INCLUDE_PATH) $(SRC_DIR)Image.cpp

# Main.o: $(SRC_DIR)Main.cpp lib/Screenshot.h lib/FreeImage.h
# 	$(CC) $(CFLAGS) -c -I$(INCLUDE_PATH) $(SRC_DIR)Main.cpp -l$(L_FLAGS)

# Camera.o: src/Camera.cpp
# 	$(CC) $(CFLAGS) -c -I$(INCLUDE_PATH) src/Camera.cpp -l$(L_FLAGS)

# Scene.o: src/Scene.cpp $(SRC_DIR)Triangle.cpp src/Geometry.cpp $(LIB_DIR)Intersection.h 
# 	$(CC) $(CFLAGS) -c -I$(INCLUDE_PATH) $(SRC_DIR)Triangle.cpp src/Scene.cpp -l$(L_FLAGS)

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
# clean: 
# 	$(RM) count *.o *~

# build: Camera1.o Geometry1.o Scene1.o Main1.o Image1.o Triangle1.o
# 	$(CC) $(CFLAGS) -o main Camera.o Geometry.o Scene.o Main.o Image.o Triangle.o

# Camera1.o: 
# 	$(CC) $(CFLAGS) -c $(INCLUDE_PATH) $(SRC_DIR)Camera.cpp $(L_FLAGS)

# Geometry1.o:
# 	$(CC) $(CFLAGS) -c $(INCLUDE_PATH) $(SRC_DIR)Geometry.cpp $(L_FLAGS)

# Scene1.o:
# 	$(CC) $(CFLAGS) -c $(INCLUDE_PATH) $(SRC_DIR)Scene.cpp $(L_FLAGS)

# Main1.o:
# 	$(CC) $(CFLAGS) -c $(INCLUDE_PATH) $(SRC_DIR)Main.cpp $(L_FLAGS)

# Image1.o:
# 	$(CC) $(CFLAGS) -c $(INCLUDE_PATH) $(SRC_DIR)Image.cpp $(L_FLAGS)

# Triangle1.o:
# 	$(CC) $(CFLAGS) -c $(INCLUDE_PATH) $(SRC_DIR)Triangle.cpp $(L_FLAGS)

CC = g++
CFLAGS = -g -std=c++11 -Wno-deprecated-register -Wno-deprecated-declarations -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
INCFLAGS = -I./glm-0.9.7.1 -I./lib/
LDFLAGS = 
# LDFLAGS = -L./freeImage/mac/ -lm  -lfreeimage 

RM = /bin/rm -f
all: SceneViewer
SceneViewer: main.o Camera.o Geometry.o Image.o Scene.o Triangle.o
	$(CC) -o SceneViewer main.o Camera.o Geometry.o Image.o Scene.o Triangle.o $(LDFLAGS)
main.o: src/main.cpp lib/Screenshot.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/main.cpp 
Camera.o: src/Camera.cpp lib/Camera.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Camera.cpp
Geometry.o: src/Geometry.cpp lib/Geometry.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Geometry.cpp
Image.o: src/Image.cpp lib/Image.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Image.cpp
Scene.o: src/Scene.cpp src/Scene.inl lib/Scene.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Scene.cpp
Triangle.o: src/Triangle.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c src/Triangle.cpp
clean: 
	$(RM) *.o SceneViewer
