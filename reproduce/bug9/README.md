## Bug ID 9

**Analyzer**: `Clam (https://github.com/seahorn/clam/)`
<br>
**Buggy commit**: `3a64ddbc7729aa942eab25c0e2fe7071109a83b8`
<br>
**Fixed commit**: `942b86cbacac9536b733ae4284fedb49c75e98c1`
<br>
**Issue**: `https://github.com/seahorn/clam/issues/93`
<br>
**Seed file**: `testfiles/svcomp20/array-cav19/array_tiling_tcpy.c`
<br>
**Integer seeds**: `4386941,1093091,6259906,726223,5079374`


### Sherlock command

```
./sherlock.sh -s <seed> -t clam -c -o "--crab-lower-unsigned-icmp true" testfiles/svcomp20/array-cav19/array_tiling_tcpy.c
```