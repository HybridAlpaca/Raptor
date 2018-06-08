#!/usr/bin/env bash

################
# Compile GLFW #
################

cd ./Engine/Source/External/glfw-3.2.1

mkdir -p Temp
cd ./Temp

# compile

cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF ..
make -j4

cp -R ../include/GLFW ../../Include
cp ./src/libglfw3.a ../../../../Binaries

cd ../../../../

#########################
# Compile Raptor Source #
#########################

cd ./Build

mkdir -p Temp
cd ./Temp

cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j4
make install

cd ..
