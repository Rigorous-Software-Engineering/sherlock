FROM ubuntu:22.04
WORKDIR /home
# set default values for analyzer versions: Most recent version for which Sherlock was tested
RUN apt update
RUN apt install python3 python3-pip clang llvm build-essential cmake curl file g++-multilib gcc-multilib git libcap-dev libgoogle-perftools-dev libncurses5-dev libsqlite3-dev libtcmalloc-minimal4 unzip python3-tabulate llvm-dev z3 moreutils gcc cpp bc vim netcat gdb wget openjdk-11-jre bash-completion jq opam libclang-cpp13-dev libgmp-dev libmpfr-dev pkg-config gperf libgmp-dev libtinfo-dev ninja-build openjdk-8-jre libflint-dev bison flex libboost-all-dev perl zlib1g-dev minisat creduce -y
RUN pip install pycparser
RUN pip install pycparser-fake-libc
RUN pip3 install lit
RUN pip3 install OutputCheck
# copy Sherlock's source code
# install CPAchecker
RUN wget https://gitlab.com/sosy-lab/sv-comp/archives-2023/raw/svcomp23/2023/cpachecker.zip
RUN unzip cpachecker.zip
RUN rm cpachecker.zip
RUN mv CPAchecker-2.2-unix ~
# install symbiotic
RUN wget https://gitlab.com/sosy-lab/sv-comp/archives-2023/raw/svcomp23/2023/symbiotic.zip
RUN unzip symbiotic.zip
RUN rm symbiotic.zip
RUN mv /home/symbiotic ~
# install Ultimate
RUN wget https://github.com/ultimate-pa/ultimate/releases/download/v0.2.4/UltimateAutomizer-linux.zip
RUN unzip UltimateAutomizer-linux.zip
RUN mv UAutomizer-linux ~
RUN rm UltimateAutomizer-linux.zip
WORKDIR /home
# install STP (for usage in KLEE)
RUN git clone https://github.com/stp/stp.git
RUN cd stp && git checkout tags/2.3.3 && mkdir build
RUN cd stp/build && cmake .. && make -j 5 && make install
RUN ulimit -s unlimited
COPY . /home/sherlock
ARG MOPSA_VERSION
ARG KLEE_VERSION
ARG CBMC_VERSION
ARG ESBMC_VERSION
ARG CLAM_VERSION
RUN if [ -n "$KLEE_VERSION" ] ; then /home/sherlock/install/klee.sh $KLEE_VERSION; \
    elif [ -n "$CBMC_VERSION" ]; then /home/sherlock/install/cbmc.sh $CBMC_VERSION; \
    elif [ -n "$MOPSA_VERSION" ]; then /home/sherlock/install/mopsa.sh $MOPSA_VERSION; \
    elif [ -n "$ESBMC_VERSION" ]; then /home/sherlock/install/esbmc.sh $ESBMC_VERSION; \
    elif [ -n "$CLAM_VERSION" ]; then /home/sherlock/install/clam.sh $CLAM_VERSION; \
     else \
      /home/sherlock/install/klee.sh f813c88c8cb868fc9c0be78fbf92a94d72ac02b0; \
      /home/sherlock/install/cbmc.sh 439bb2c0ccee3dc0e7fb89a6ecceb9e413cbff6b ; \
      /home/sherlock/install/mopsa.sh d4c73a5e7311180e953c69713aad91907d8adb62 ; \
      /home/sherlock/install/esbmc.sh db4c241b975597aa24b940f98856431b4a51cf47; \
      /home/sherlock/install/clam.sh 942b86cbacac9536b733ae4284fedb49c75e98c1; \
    fi
WORKDIR /home/sherlock