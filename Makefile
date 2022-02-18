########################################
##
## Makefile
## LINUX compilation
##
##############################################

# Flags
CPPFLAGS = -g -std=c++11 -Wall

# Math library

MATH_LIBS = -lm

# Includes.
INCLUDES=  -I.

# Compiling all

all:
	g++ $(CPPFLAGS) test_points3d.cc -o test_points3d $(INCLUDES) $(LIBS_ALL)

# Clean obj files
clean:
	rm -f *.o; rm -f test_points3d


