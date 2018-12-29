#/bin/bash
g++ process.h process.cpp alg.cpp -fPIC -shared -o libalg.so $(pkg-config --cflags opencv) $(pkg-config --libs opencv) -std=c++11
