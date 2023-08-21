#!/bin/sh

BUID_DIR=./build

echo "Start building"

if [[ ! -d $BUID_DIR ]]; then
    mkdir -p build
fi

cd build

LIB_DIR=../../libraries
if [[ ! -d $LIB_DIR ]]; then
    mkdir $LIB_DIR || exit 1
fi

if [[ ! -d $LIB_DIR/tclap-1.2.5 ]]; then
    wget https://github.com/xguerin/tclap/archive/refs/tags/v1.2.5.tar.gz -O - | tar -xz -C $LIB_DIR || exit 1
fi

if [[ ! -d $LIB_DIR/toml11-3.7.1 ]]; then
    wget https://github.com/ToruNiina/toml11/archive/refs/tags/v3.7.1.tar.gz -O - | tar -xz -C $LIB_DIR || exit 1
fi

cmake ..
make
