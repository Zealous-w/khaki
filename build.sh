#!/bin/bash
make clean
make && cd example && make clean && make && gdb echo
