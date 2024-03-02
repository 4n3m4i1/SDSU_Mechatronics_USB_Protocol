#!/usr/bin/bash

start_dir=$(pwd)

cd protocol
if [ -d "build" ]; then
    sudo rm -r build
fi
mkdir build && cd build && cmake .. && make && sudo make install
cd $start_dir

cd hardware/sam
if [ -d "build" ]; then
    sudo rm -r build
fi
mkdir build && cd build && cmake .. && make
cd $start_dir

cd client_c
if [ -d "build" ]; then
    sudo rm -r build
fi
mkdir build && cd build && cmake .. && make && sudo make install
cd $start_dir