#! /bin/bash

# This script how many lines of code are in the project.
cd ../src

echo "Counting lines of .cpp ..."
find . -name '*.cpp' | xargs wc -l

echo "Counting lines of .h ..."
find . -name '*.h' | xargs wc -l

echo "Counting lines of image/sound data to ignore ..."
cat Hardware/Displays/Images/*.h | wc -l
cat Hardware/Sound/Sounds/*.h | wc -l

echo "Counting lines of library code to ignore ..."
cd ./libs
find . -name '*.cpp' | xargs wc -l
find . -name '*.h' | xargs wc -l