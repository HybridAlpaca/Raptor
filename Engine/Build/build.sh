#!/usr/bin/env sh

BASEDIR=$(dirname "$0")

cd $BASEDIR

mkdir -p Temp

cd Temp
cmake ..
make -j6
make install

cd ../

cd ../Source/External/glfw/Temp
make -j6
