#!/bin/bash
cd build 
make clean
make && cd ../example/build && make clean && make && gdb echo
