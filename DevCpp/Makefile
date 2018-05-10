FLAG=-std=c++11 -Wall -Wextra -g

GLEWLIB:=$(shell pkg-config --cflags --libs glew) -lglu32 -lopengl32
GLFWLIB:=$(shell pkg-config --cflags --libs glfw3)

all: test.exe

clean:
	-rm -f test.exe libEg.dll

test.exe: ../test.cpp libEg.dll
	g++ -o $@ $< $(FLAG) -L. -lEg $(GLEWLIB)

libEg.dll: ../global.h.gch $(wildcard ../E*.cpp ../E*.h)
	g++ -shared -o $@ $(wildcard ../E*.cpp) $(FLAG) -fPIC $(GLFWLIB) $(GLEWLIB)

../global.h.gch: ../global.h
	g++ $< $(FLAG)
