#!/bin/bash

cd ~ && git clone https://gitlab.com/mopsa/mopsa-analyzer.git
cd mopsa-analyzer
git checkout $1
opam init -y
eval $(opam env) && opam install --deps-only --with-doc --with-test -y --confirm-level=unsafe-yes .
eval $(opam env) && ./configure && make -j 5 && make install