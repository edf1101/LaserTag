#! /bin/bash

# This script remakes the project into a format the arduino IDE can compile.

echo "Compiling project for Arduino IDE..."
echo ""

cd ./arduino_builds
echo "Removing old build"
echo ""
rm -r -f LaserTag

echo "Creating new build"
echo "Making new directory"
mkdir LaserTag
echo "Copying .ino entrance file"
cp LaserTag.ino LaserTag/
mkdir LaserTag/src
echo "Copying src code"
cp -r ../../src/* LaserTag/src
echo "Removing main.cpp from arduino build"
rm -f LaserTag/src/main.cpp

echo ""
echo "Done!"

