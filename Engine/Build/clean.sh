#!/usr/bin/env bash

cd /home/cellman123/Desktop/Raptor

##################
# Prune Binaries #
##################

echo "Preparing to cleanse binaries..."

cd ./Engine/Binaries

echo "[1/3] Static Core"
rm -f ./libCore.a
echo "[2/3] Static Graphics"
rm -f ./libGraphics.a
echo "[3/3] Binary Raptor"
rm -f ./Raptor

echo "Done."
