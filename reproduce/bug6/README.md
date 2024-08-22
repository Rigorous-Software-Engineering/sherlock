## Bug ID 6

**Analyzer**: `Clam (https://github.com/seahorn/clam/)`
<br>
**Buggy commit**: `75b5fb95fa6320f59a7b9b07241f780352ba5ab2`
<br>
**Fixed commit**: `7a7880a2a5af5465a1c6c3a2a247e67e9abf2876`
<br>
**Issue**: `https://github.com/seahorn/clam/issues/87`
<br>
**Seed file**: `testfiles/svcomp20/bitvector/s3_srvr_2_alt.BV.c.cil.c`
<br>
**Integer seeds**: `7944188,688407,9989268,7968462,6538169`


### Sherlock command

```
./sherlock.sh -s <seed> -t clam -c -o "--crab-lower-unsigned-icmp true" testfiles/svcomp20/bitvector/s3_srvr_2_alt.BV.c.cil.c
```