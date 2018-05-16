FLAG=-std=c++11 -Wall -Wextra -g

all: test.exe

clean:
	-rm -f test.exe libEg.dll

test.exe: ../test.cpp libEg.dll
	g++ -o $@ $< $(FLAG) -L. -lEg -lglew32 -lglu32 -lopengl32

libEg.dll: ../global.h.gch $(wildcard ../E*.cpp ../E*.h)
	g++ -shared -o $@ $(wildcard ../E*.cpp) $(FLAG) -fPIC -lglfw3 -lFreeImage -lglew32 -lglu32 -lopengl32 -lgdi32

../global.h.gch: ../global.h
	g++ $< $(FLAG)
