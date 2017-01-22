#!/bin/bash

g++ -c *.cpp -std=c++11
g++ *.o -o Server -l sfml-window -l sfml-graphics -l sfml-network -l sfml-system
rm *.o
