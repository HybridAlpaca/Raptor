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

# install

cp -R ../include/GLFW ../../Include
cp ./src/libglfw3.a ../../../../Binaries

cd ../../../../

##################
# Compile ASSIMP #
##################

cd ./Source/External/assimp-4.1.0

mkdir -p Temp
cd ./Temp

# compile

cmake ..
make -j4

# install

cp -R ../include/assimp ../../Include
cp ./code/libassimp.so.4.1.0  ../../../../Binaries

cd ../../../../

##################
# Compile Raptor #
##################

cd ./Build

mkdir -p Temp
cd ./Temp

# compile

cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j4

# install

make install

cd ..
