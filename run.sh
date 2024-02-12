#!/bin/bash

g++ -g src/*.cpp src/main/Main.cpp -o run.exe -lgtest -lgtest_main -I include -L lib

./run.exe