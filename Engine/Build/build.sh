#!/usr/bin/env bash

cd ./Engine/Build

mkdir -p CMake

cd ./CMake

cmake .. -DCMAKE_BUILD_TYPE=Debug

make

make install

cd ..
