## Bug ID 7

**Analyzer**: `Clam (https://github.com/seahorn/clam/)`
<br>
**Buggy commit**: `a4420033655e7f285c55803ce53ce9ca1e94b2a6`
<br>
**Fixed commit**: `3fde3046e3a4d10690d1a95d3697ba591b534d69`
<br>
**Issue**: `https://github.com/seahorn/clam/issues/89`
<br>
**Seed file**: `testfiles/svcomp20/array-cav19/array_tiling_tcpy.c`
<br>
**Integer seeds**: `1206260,2169630,7156179,5125451,8676840`


### Sherlock command

```
./sherlock.sh -s <seed> -t clam -c -o "" testfiles/svcomp20/array-cav19/array_tiling_tcpy.c
```