#!/bin/bash

WORKDIR=/home/ESBMC_Project
mkdir /home/ESBMC_Project && cd /home/ESBMC_Project && git clone https://github.com/esbmc/esbmc
cd $WORKDIR
cd esbmc && git checkout $ESBMC_VERSION
cd $WORKDIR
ESBMC_STATIC=ON
cd $WORKDIR
wget https://github.com/Z3Prover/z3/releases/download/z3-4.8.9/z3-4.8.9-x64-ubuntu-16.04.zip && unzip z3-4.8.9-x64-ubuntu-16.04.zip && mv z3-4.8.9-x64-ubuntu-16.04 z3
cd $WORKDIR
git clone --depth=1 --branch=3.2.3 https://github.com/boolector/boolector && cd boolector && ./contrib/setup-lingeling.sh && ./contrib/setup-btor2tools.sh && ./configure.sh --prefix $PWD/../boolector-release && cd build && make -j5 && make install && cd .. && cd ..
cd $WORKDIR
cd esbmc && mkdir build && cd build && cmake .. -GNinja -DBUILD_TESTING=On -DENABLE_REGRESSION=On -DDOWNLOAD_DEPENDENCIES=ON -DBUILD_STATIC=${ESBMC_STATIC:-ON} -DBoolector_DIR=$PWD/../../boolector-release -DZ3_DIR=$PWD/../../z3 -DENABLE_MATHSAT=OFF -DENABLE_YICES=OFF -DCMAKE_INSTALL_PREFIX:PATH=$PWD/../../release
cd $WORKDIR
cd esbmc/build && cmake --build . -- -j 5 && ninja install

