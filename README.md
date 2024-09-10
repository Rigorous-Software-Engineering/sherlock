## Installation:

**Requirements**:

-) Hardware: The build process of Sherlock uses 5 CPU cores. In our experiments we provided 100 GB of RAM for each docker container. Even though smaller memory size might affect running 
times - especially for bugs with a long time-to-bug, we expect that qualitatively the results (i.e. the speedups over the baselines) stay the same.

-) Software: Docker version >= 24.0.7

Install docker and use the Dockerfile to build Sherlock and
the analyzers CBMC, Clam, CPAchecker, ESBMC, KLEE, MOPSA, UltimateAutomizer and Symbiotic.
If you execute from the directory in which `Dockerfile` is located
```
docker build -t sherlock .
```
the build process will take > 1h because all tested analyzers are built.
You can however build only one analyzer by passing option `--build-arg="<analyzer>_VERSION=<git_commit_id>"` where
`<analyzer>` is one of `CBMC`, `CLAM`, `ESBMC`, `KLEE` or `MOPSA` and `<git_commit_id>` is a git commit id of the
analyzer's git repository. E.g. to build Sherlock containing CBMC at a version that Sherlock found buggy, execute

```
docker build --build-arg="CBMC_VERSION=95b7ac50d79384f108c1bd33bd6710b189b80e27" -t sherlock .
```

## Usage:
Once the build processes finishes, the docker image is built and the analyzers are installed inside Sherlock.
Now you can start a container with

```
docker run -it sherlock
```

You can let Sherlock start a testing campaign of an analyzer by invoking

```
./sherlock.sh -t <analyzer>
```

where `<analyzer>` is one of `cbmc`, `clam`, `cpa`, `esbmc`, `klee`, `mopsa`, `ultimate` or `symbiotic`. Sherlock will by default pick seed files from the directory `testfiles`.


To test <analyzer> with a specific seed file run
```
./sherlock.sh -t <analyzer> <path>
```
If `<path>` is a C-file, Sherlock tests `<analyzer>` on this C-file only. If `<path>` is a directory, Sherlock tests `<analyzer>` with each C-File in `<path>` and its subdirectories one by one in an infinite loop.

Specify option `-b` to provide a budget, so  a number of testing iterations. (If omitted Sherlock tests with a specific seed file until it finds a bug)
```
./sherlock.sh -t <analyzer> -b <budget>
```
In order to see reproducible results (up to timing), specify the initial integer seed for the fuzzing process of Sherlock by using option `-s`:
```
./sherlock.sh -t <analyzer> -s <seed>
```

To get more detailed information about Sherlock's options invoke:

```
./sherlock.sh -h
```

Finally, you can have look at Sherlock's log file `out.csv` that contains detailed information about the fuzzing process.

## Minimizing bugs using C-Reduce

Once Sherlock finds a bug, it saves information about it in a directory in `bug_files/<id>`.
When minimizing a bug we use [C-Reduce](https://github.com/csmith-project/creduce). Sherlock has C-Reduce installed, so there are no additional installation steps necessary.

To do the matching of assertions/assumptions during the minimization, we require the initial and transformed file to have the same number of LOCs.
This is already the case for all transformations except _strengthen_, because here we add assertions and assumptions.
In order to align the file initial.c of a strengthening to the same length as the file strengthen.c, use the script in
creduce/equalizer.py. It writes a newline whenever the transformed file has a new assertion/assumption:

```
python3 creduce/equalizer.py bug_files/1/initial.c bug_files/1/strengthen.c
```

When this command finishes, the files bug_files/1/initial.c and bug_files/1/strengthen.c should have equal number of LOCs.
In order to minimize now the bug, execute

```
cp bug_files/1/initial.c .
creduce --debug --n 1 creduce/<analyzer>_interesting.sh initial.c
```

where `<analyzer>` is the analyzer that contains the bug. Note that in case the analyzer exhibits buggy
behavior only if it is invoked with special parameters, specify these parameters by defining variable
`analyzer_opts` in `<analyzer>_interesting.sh` (line 3).

E.g. to minimize the bug of CBMC [bug1](https://github.com/diffblue/cbmc/issues/7953) (produced using integer seed 359450, which results in the fastest run with 15 min
time-to-bug), execute the following in the docker container that revealed the bug (here no special options are required for CBMC):

```
cp bug_files/1/initial.c .
creduce --debug --n 1 creduce/cbmc_interesting.sh initial.c
```

While the files in bug_files/1 have 116 LOCs, C-Reduce will print the minimized initial file with 11 LOCs.
Note that, even though C-Reduce needs about 10 min to complete the minimization, you can always find intermediate reduction of the initial and transformed
file in `bug_files/0`. These files are already quite small after a minute.


## Bugs detected so far:
Sherlock has already detected many unique bugs.
Here is a list of issues we filed on public bug tracking systems together with their classification for various program analyzers.
For fixed bugs which we evaluated in our ASE 2024 paper you can see the commit ID of the buggy and fixed analyzer version.


| Bug ID | Analyzer name     | Bug Type  | Link                                                          | buggy commit ID                          | fixed commit ID                          |
|--------|-------------------|-----------|---------------------------------------------------------------|------------------------------------------|------------------------------------------|
| 1      | CBMC              | Soundness | https://github.com/diffblue/cbmc/issues/7953                  | 95b7ac50d79384f108c1bd33bd6710b189b80e27 | 439bb2c0ccee3dc0e7fb89a6ecceb9e413cbff6b |
| 2      | CBMC              | Soundness | https://github.com/diffblue/cbmc/issues/7997                  |                                          |                                          |
| 3      | CBMC              | Soundness | https://github.com/diffblue/cbmc/issues/8200                  |                                          |                                          |
| 4      | CBMC              | Precision | https://github.com/diffblue/cbmc/issues/8223                  |                                          |                                          |
| 5      | CBMC              | Other     | https://github.com/diffblue/cbmc/issues/8257                  |                                          |                                          |
| 6      | Clam              | Soundness | https://github.com/seahorn/clam/issues/87                     | 75b5fb95fa6320f59a7b9b07241f780352ba5ab2 | 7a7880a2a5af5465a1c6c3a2a247e67e9abf2876 |
| 7      | Clam              | Precision | https://github.com/seahorn/clam/issues/89                     | a4420033655e7f285c55803ce53ce9ca1e94b2a6 | 3fde3046e3a4d10690d1a95d3697ba591b534d69 |
| 8      | Clam              | Precision | https://github.com/seahorn/clam/issues/91                     | 3fde3046e3a4d10690d1a95d3697ba591b534d69 | 3a64ddbc7729aa942eab25c0e2fe7071109a83b8 |
| 9      | Clam              | Soundness | https://github.com/seahorn/clam/issues/93                     | 3a64ddbc7729aa942eab25c0e2fe7071109a83b8 | 942b86cbacac9536b733ae4284fedb49c75e98c1 |
| 10     | Clam              | Soundness | https://github.com/seahorn/clam/issues/94                     |                                          |                                          |
| 11     | CPAchecker        | Precision | https://gitlab.com/sosy-lab/software/cpachecker/-/issues/1140 |                                          |                                          |
| 12     | ESBMC             | Precision | https://github.com/esbmc/esbmc/issues/1528                    |                                          |                                          |
| 13     | ESBMC             | Soundness | https://github.com/esbmc/esbmc/issues/1537                    | 61cdf7f22ac91922482944c66fa17f155798e66c | 79c621ff20dfd9856540a314eb26e537e0b04083 |
| 14     | ESBMC             | Soundness | https://github.com/esbmc/esbmc/issues/1620                    |                                          |                                          |
| 15     | ESBMC             | Soundness | https://github.com/esbmc/esbmc/issues/1655                    | db5ae0a66e178cd666f9574c0e04d3268c93aaeb | db4c241b975597aa24b940f98856431b4a51cf47 |
| 16     | ESBMC             | Soundness | https://github.com/esbmc/esbmc/issues/1650                    |                                          |                                          |
| 17     | KLEE              | Soundness | https://github.com/klee/klee/issues/1666                      |                                          |                                          |
| 18     | KLEE              | Soundness | https://github.com/klee/klee/issues/1668                      | cb5e898561f9b8769d8838bc1bdca17a6f4f5d20 | f813c88c8cb868fc9c0be78fbf92a94d72ac02b0 |
| 19     | KLEE              | Crash     | https://github.com/klee/klee/issues/1654                      |                                          |                                          |
| 20     | MOPSA             | Soundness | https://gitlab.com/mopsa/mopsa-analyzer/-/issues/172          | 5e4d8376716bc9ceae81be1f9e00b83a9615f1ab | 4ce28ae045eede90087a73bbf650c07d380c87d2 |
| 21     | MOPSA             | Precision | https://gitlab.com/mopsa/mopsa-analyzer/-/issues/170          |                                          |                                          |
| 22     | MOPSA             | Soundness | https://gitlab.com/mopsa/mopsa-analyzer/-/issues/173          | 41f73f5c5afef2aeab94eef849461e77c2cfc01e | d4c73a5e7311180e953c69713aad91907d8adb62 |
| 23     | UltimateAutomizer | Soundness | https://github.com/ultimate-pa/ultimate/issues/661            |                                          |                                          |
| 24     | Symbiotic         | Soundness | https://github.com/staticafi/symbiotic/issues/248             |                                          |                                          |
## Reproducing bugs used in the evaluation section of our ASE 2024 paper "Interrogation Testing of Program Analyzers for Soundness and Precision Issues"

**Follow these step to reproduce results for Table 4 and Table 5:**

To refind a specific bug, first you need to build Sherlock with a specific version of the tested analyzers as the analyzers are dockerized inside Sherlock. 
Use the Dockerfile's options CBMC_VERSION, CLAM_VERSION, ESBMC_VERSION, KLEE_VERSION and MOPSA_VERSION.
In order to reproduce the results for a specific bug, provide the commit ID of a buggy version of the analyzer which you
can find in the table above. E.g. in order to reproduce the results for [bug1](https://github.com/diffblue/cbmc/issues/7953), execute

```
docker build --build-arg="CBMC_VERSION=95b7ac50d79384f108c1bd33bd6710b189b80e27" -t sherlock:buggy_cbmc .
docker run -it sherlock:buggy_cbmc
root@<buggy_container_id>:/home/sherlock# ./sherlock.sh -s <seed> -t cbmc -o "<analyzer_options>" testfiles/testcomp22/nla-digbench-scaling/hard-u_valuebound100.c
```

Here you need to replace `<seed>` with an integer seed and `<analyzer_options>` with the analyzer options that were used to find the bug, here `--unwind 1 --round-to-minus-inf --reachability-slice-fb --drop-unused-functions --max-field-sensitivity-array-size 1 --partial-loops --string-printable --arrays-uf-always`.
You can find this information in the bug ID folders in sherlock/reproduce/ .

**To find the full list of parameters of the sherlock command of a specific bug, please follow the instructions within each bug ID folder in the folder sherlock/reproduce/**

If you want to reproduce the results for the baselines, build the Dockerfile in the directories `sherlock-MT` or `sherlock-MT+VR`,
otherwise build the Dockerfile in `sherlock`. To provide a specific time-to-live value, invoke Sherlock with option
`-l <ttl>`.


In order to confirm that the respective
bug and not another bug was found, install the fixed version of the analyzer or let the Dockerfile build
Sherlock with the fixed analyzer inside by providing the commit ID of a fixed version of the analyzer. E.g. in order to confirm that the
first bug found by Sherlock when trying to reproduce bug1, is indeed fixed by the commit fixing bug1, execute
```
docker cp <buggy_conatiner_id>:/home/sherlock/bug_files .
docker build --build-arg="CBMC_VERSION=439bb2c0ccee3dc0e7fb89a6ecceb9e413cbff6b" -t sherlock:fixed_cbmc .
fixed_container_id=$(docker run -dt sherlock:fixed_cbmc)
docker cp bug_files $fixed_container_id:/home/sherlock
docker exec $fixed_container_id ./tools/metamorphic_checker.sh -o "<analyzer_options>" <analyzer> bug_files/1
echo $?
```
Here `<buggy_conatiner_id>` refers to the ID of the container created by the `docker run` command above,
`<analyzer>` is the name of the buggy analyzer (in this case `cbmc`) and `<analyzer_options>` are the options that the fuzzer generated for the analyzer, which you can find in the Sherlock command in the bug ID folders.
The directory `bug_files` contains the information necessary to confirm the bug: Initial and transformed file. The script `tools/metamorphic_checker.sh`
verifies that the bug violates the oracle and exits with exit code 0 only if the oracle is violated. Therefore, we expect that if the fixed
version of the tool is installed, a different exit code than 0 is printed.

Notice that when reproducing Clam and ESBMC bugs, the first bugs reported by Sherlock, are usually different from the fixed bugs: For Clam,
Sherlock finds cases of precision loss (e.g. due to widening) and for ESBMC Sherlock warns about other reported, but not fixed bugs).
To this end we need to invoke Sherlock with option `-c`. This option makes Sherlock _continue testing_  when it finds a bug.
Sherlock will then produce different bug reports in the directory `bug_files`.
In order to verify that Sherlock found the 'right' bug after some time, execute the above commands with several bug reports, i.e.
`bug_files/1`, `bug_files/2`, etc. 
