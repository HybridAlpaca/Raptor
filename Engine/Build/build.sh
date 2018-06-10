#!/usr/bin/env bash

##################
# Compile Raptor #
##################

cd ./Engine/Build

mkdir -p Temp
cd ./Temp

# compile

cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j4

# install

make install

cd ..
