#!/usr/bin/env bash

cd /home/cellman123/Desktop/Raptor

###########################
# Prune Build Temporaries #
###########################

echo "Preparing to prune build trees..."

# GLFW3

echo "[1/2] GLFW"

cd ./Engine/Source/External/glfw-3.2.1

rm -rf Temp

cd ../../../

# Raptor 

echo "[2/2] Raptor"

cd ./Build

rm -rf Temp

cd ../

echo "Done."

##############################
# Prune Binaries & Libraries #
##############################

echo "Preparing to cleanse binaries..."

cd ./Binaries

echo "[1/4] Static Core"
rm -f ./libCore.a
echo "[2/4] Static Graphics"
rm -rf ./libGraphics.a
echo "[3/4] Shared GLFW"
rm -rf ./libglfw3.a
echo "[4/4] Binary Raptor"
rm -rf ./Raptor

echo "Done."
