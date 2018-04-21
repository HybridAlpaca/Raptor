#!/usr/bin/env bash

cd ./Engine/Build

mkdir CMake

cd ./CMake

cmake ..

make

make install

cd ..