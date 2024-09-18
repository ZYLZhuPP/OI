#!/bin/sh
set -v
rm -f ./triangle
g++ -o triangle LightBitmap.cpp LightTriangleIntersection.cpp triangle.cpp ./src/* -O3 -std=c++11 -pthread -I include
echo Triangle Compilation Finished!
