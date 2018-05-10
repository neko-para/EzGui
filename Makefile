FLAG=-std=c++11 -Wall -Wextra -g
SYS=win

ifeq ($(SYS), win)
	DLL=libEg.dll
	EXE=test.exe
	EXTRALIB=-lglu32 -lopengl32
else
	DLL=libEg.so
	EXE=test
endif

GLEWLIB:=$(shell pkg-config --cflags --libs glew) $(EXTRALIB)
GLFWLIB:=$(shell pkg-config --cflags --libs glfw3)

all: $(EXE)

$(EXE): test.cpp $(DLL)
	g++ -o $@ $< $(FLAG) -Wl,--rpath=. -L. -lEg $(GLEWLIB)

$(DLL): global.h.gch $(shell ls E*.cpp E*.h)
	g++ -shared -o $@ $(shell ls E*.cpp) $(FLAG) -fPIC $(GLFWLIB) $(GLEWLIB)

global.h.gch: global.h
	g++ $< $(FLAG)
