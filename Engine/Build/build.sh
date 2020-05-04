#!/usr/bin/env sh

BASEDIR=$(dirname "$0")

cd $BASEDIR

mkdir -p Temp

cd Temp
cmake ../../Source/
make -j6
make install
