#!/bin/bash

rm -r build
rm -r tp2

mkdir build
cd build
cmake ../
cmake --build .
cd ..