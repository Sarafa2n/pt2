#!/bin/bash

mkdir build
cd build
cmake ..
cmake --build .
./test_utils
./test_realisation
cd ..
cppcheck --project=compile_commands.json