## Bug ID 8

**Analyzer**: `Clam (https://github.com/seahorn/clam/)`
<br>
**Buggy commit**: `3fde3046e3a4d10690d1a95d3697ba591b534d69`
<br>
**Fixed commit**: `3a64ddbc7729aa942eab25c0e2fe7071109a83b8`
<br>
**Issue**: `https://github.com/seahorn/clam/issues/91`
<br>
**Seed file**: `testfiles/svcomp20/reducercommutativity/sep.c`
<br>
**Integer seeds**: `7559283,4050235,711251,3264036,1041208`


### Sherlock command

```
./sherlock.sh -s <seed> -t clam -c -o "--crab-lower-unsigned-icmp true" testfiles/svcomp20/reducercommutativity/sep.c
```