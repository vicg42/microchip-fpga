#!/bin/sh

echo "Start building"
mkdir -p build
cd build
cmake ..
make
