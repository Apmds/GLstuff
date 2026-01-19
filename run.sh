#!/usr/bin/env bash

if (( $# != 1 )); then
    echo Must specify an executable to run!
    exit 1
fi

mkdir -p build
cd build
cmake ..
make $1 && cd .. && ./build/$1
