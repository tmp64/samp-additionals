#all:
#	g++ -shared -o samp-additionals.so -fPIC Main.cpp -std=c++11 -m32 -fvisibility=default

.PHONY: build clean

ifndef GXX
	GXX = g++
endif

COMPILE_FLAGS = -c -fPIC -m32 -O3 -w -Wall -ISDK/amx/ -DLINUX -std=c++11
LIBRARIES = -lrt

OUTFILE = bin/samp-additionals.so

build:
	mkdir -p bin
	$(GXX) $(COMPILE_FLAGS) SDK/*.cpp
	$(GXX) $(COMPILE_FLAGS) *.cpp
	$(GXX) -m32 -shared -o $(OUTFILE) *.o $(LIBRARIES)
	
clean:
	rm -f *.o