## Bug ID 22

**Analyzer**: `MOPSA (https://gitlab.com/mopsa/mopsa-analyzer/)`
<br>
**Buggy commit**: `41f73f5c5afef2aeab94eef849461e77c2cfc01e`
<br>
**Fixed commit**: `d4c73a5e7311180e953c69713aad91907d8adb62`
<br>
**Issue**: `https://gitlab.com/mopsa/mopsa-analyzer/-/issues/173`
<br>
**Seed file**: `testfiles/testcomp22/loops/invert_string-2.c`
<br>
**Integer seeds**: `1819109,114568,2150266,3999596,5972394`


### Sherlock command

```
./sherlock.sh -s <seed> -t mopsa -o "-config=tools/mopsa/configs/cell-string-length-itv-powerset-zero.json" testfiles/testcomp22/loops/invert_string-2.c 
```