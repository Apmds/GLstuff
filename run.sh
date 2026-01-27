#!/usr/bin/env bash

if (( $# != 1 )); then
    echo Must specify an executable to run!
    exit 1
fi

if [ ! -d build ]; then
    mkdir -p build
    cd build
    cmake ..
else
    cd build
fi
make $1 && cd .. && ./build/$1
