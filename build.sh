#!/usr/bin/env bash

cd ./Engine/Build

mkdir -p CMake

cd ./CMake

cmake ..

make

make install

make clean

cd ..