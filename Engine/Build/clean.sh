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

echo "[1/5] Static Core"
rm -f ./libCore.a
echo "[2/5] Static Graphics"
rm -rf ./libGraphics.a
echo "[3/5] Static GLFW"
rm -rf ./libglfw3.a
echo "[4/5] Shared ASSIMP"
rm -rf ./libassimp.so.4.1.0
echo "[5/5] Binary Raptor"
rm -rf ./Raptor

echo "Done."
