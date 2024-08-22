## Bug ID 20

**Analyzer**: `MOPSA (https://gitlab.com/mopsa/mopsa-analyzer/)`
<br>
**Buggy commit**: `5e4d8376716bc9ceae81be1f9e00b83a9615f1ab`
<br>
**Fixed commit**: `4ce28ae045eede90087a73bbf650c07d380c87d2`
<br>
**Issue**: `https://gitlab.com/mopsa/mopsa-analyzer/-/issues/172`
<br>
**Seed file**: `testfiles/testcomp22/nla-digbench-scaling/freire1_unwindbound10.c`
<br>
**Integer seeds**: `6143351,415814,4092266,5221121,7014723`


### Sherlock command

```
./sherlock.sh -s <seed> -t mopsa -o "-config=tools/mopsa/configs/cell-string-length-itv-congr.json" testfiles/testcomp22/nla-digbench-scaling/freire1_unwindbound10.c 
```