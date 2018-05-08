
FLAG=-std=c++11 -Wall -Wextra -g

all: test

test: libEg.so test.cpp
	g++ test.cpp -o test $(FLAG) -Wl,--rpath=. -L. -lEg $(shell pkg-config --cflags --libs glew)

libEg.so: $(shell ls E*.cpp E*.h)
	g++ -shared -o libEg.so $(shell ls E*.cpp) $FLAG -fPIC $(shell pkg-config --cflags --libs glfw3 glew)