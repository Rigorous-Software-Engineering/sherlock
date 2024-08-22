#!/bin/bash

cd / && git clone https://github.com/seahorn/clam.git && cd clam && git checkout $1 && mkdir build
cd /clam/build
cmake -DCMAKE_INSTALL_PREFIX=$DIR ..
cmake --build . --target crab && cmake ..
cmake --build . --target extra && cmake ..
cmake --build . --target install -- -j 5
