#all:
#	g++ -shared -o samp-additionals.so -fPIC Main.cpp -std=c++11 -m32 -fvisibility=default

.PHONY: build clean

COMPILE_FLAGS = -c -fPIC -m32 -O3 -w -Wall -ISDK/amx/ -DLINUX -std=c++11
LIBRARIES = -lrt

OUTFILE = bin/samp-additionals.so

build:
	mkdir -p bin
	g++ $(COMPILE_FLAGS) SDK/*.cpp
	g++ $(COMPILE_FLAGS) *.cpp
	g++ -m32 -shared -o $(OUTFILE) *.o $(LIBRARIES)
	
clean:
	rm -f *.o