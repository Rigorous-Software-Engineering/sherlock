#!/bin/bash

git clone https://github.com/diffblue/cbmc.git
cd /home/cbmc && git checkout $1
cd /home/cbmc && git submodule update --init
cd /home/cbmc && cmake -S. -Bbuild -DWITH_JBMC=OFF -DCMAKE_C_COMPILER=/usr/bin/clang
cd /home/cbmc && cmake --build build -- -j 5
cd /usr/bin && ln /home/cbmc/build/bin/cbmc
