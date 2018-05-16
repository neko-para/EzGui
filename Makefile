FLAG=-std=c++11 -Wall -Wextra -g

GLEWLIB:=$(shell pkg-config --cflags --libs glew)
GLFWLIB:=$(shell pkg-config --cflags --libs glfw3)
FREEIMAGELIB=-lfreeimage

all: test

clean:
	-rm -f test libEg.so

test: test.cpp libEg.so
	g++ -o $@ $< $(FLAG) -Wl,--rpath=. -L. -lEg $(GLEWLIB)

libEg.so: global.h.gch $(wildcard E*.cpp E*.h)
	g++ -shared -o $@ $(wildcard E*.cpp) $(FLAG) -fPIC $(GLFWLIB) $(FREEIMAGELIB) $(GLEWLIB)

global.h.gch: global.h
	g++ $< $(FLAG)
