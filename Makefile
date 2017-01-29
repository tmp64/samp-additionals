all:
	g++ -shared -o samp-additionals.so -fPIC Main.cpp -std=c++11 -m32 -fvisibility=default