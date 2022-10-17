CC = g++
VERSION = 2.24.1
ARCH = x86_64-w64-mingw32
LIBS = ../SDL2-$(VERSION)/$(ARCH)/lib
INCL = ../SDL2-$(VERSION)/$(ARCH)/include/SDL2
TARGET = mandelbrot


# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
#  -I 	  - directory containing include files.
CPPFLAGS =\
    -g -Wall \
    -I$(INCL)


# linker flags:
#	-L 		- this flag adds the following directory to the library search path.
CPPLIBS =\
    -L$(LIBS) \
	-lSDL2 -lSDL2main


all: $(TARGET)

$(TARGET): $(TARGET).cpp 
	$(CC) $(CPPFLAGS) -o $(TARGET) $(TARGET).cpp $(CPPLIBS)


clean:

	$(RM) $(TARGET)