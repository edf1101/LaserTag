#! /bin/bash

# This script how many lines of code are in the project.
cd ../src

echo "Counting lines of .cpp ..."
find . -name '*.cpp' | xargs wc -l

echo "Counting lines of .h ..."
find . -name '*.h' | xargs wc -l

echo "Counting lines of image/sound data to ignore ..."
cat Displays/Images/*.h | wc -l
cat Sound/Sounds/*.h | wc -l