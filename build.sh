#! /bin/sh
clear
cmake -S. -B build
cmake --build build
./build/subprojects/Build/Algorithms_Visualizer_core/main
