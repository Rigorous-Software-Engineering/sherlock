#!/bin/bash

git clone https://github.com/klee/klee
cd klee && git checkout $1
mkdir build && cd build
cmake -DENABLE_SOLVER_Z3=ON -DENABLE_SOLVER_STP=ON -DENABLE_UNIT_TESTS=OFF -DENABLE_SYSTEM_TESTS=OFF .. && make -j 5
cd /usr/bin && ln /home/klee/build/bin/klee
