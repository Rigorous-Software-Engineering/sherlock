## Bug ID 1

**Analyzer**: `CBMC (https://github.com/diffblue/cbmc/)`
<br>
**Buggy commit**: `95b7ac50d79384f108c1bd33bd6710b189b80e27`
<br>
**Fixed commit**: `439bb2c0ccee3dc0e7fb89a6ecceb9e413cbff6b`
<br>
**Issue**: `https://github.com/diffblue/cbmc/issues/7953`
<br>
**Seed file**: `testfiles/testcomp22/nla-digbench-scaling/hard-u_valuebound100.c`
<br>
**Integer seeds**: `3746191,362638,43987,359450,294603`


### Sherlock command

```
./sherlock.sh -s <seed> -t cbmc -o "--unwind 1 --round-to-minus-inf --reachability-slice-fb --drop-unused-functions --max-field-sensitivity-array-size 1 --partial-loops --string-printable --arrays-uf-always" testfiles/testcomp22/nla-digbench-scaling/hard-u_valuebound100.c
```