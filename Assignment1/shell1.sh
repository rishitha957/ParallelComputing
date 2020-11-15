#!/bin/sh

#Author: Rishitha Kalicheti

make
./dump_graph 4
mpiexec -np 4 ./1 4 3 2

echo "----------------end of shell script-------------------"