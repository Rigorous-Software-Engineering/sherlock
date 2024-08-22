## Bug ID 13

**Analyzer**: `ESBMC (https://github.com/esbmc/esbmc)`
<br>
**Buggy commit**: `61cdf7f22ac91922482944c66fa17f155798e66c`
<br>
**Fixed commit**: `79c621ff20dfd9856540a314eb26e537e0b04083`
<br>
**Issue**: `https://github.com/esbmc/esbmc/issues/1537`
<br>
**Seed file**: `testfiles/testcomp22/product-lines/email_spec11_product30.cil.c`
<br>
**Integer seeds**: `653577,2249008,3002025,3147016,3670049`


### Sherlock command

```
./sherlock.sh -s <seed> -t esbmc -c -o "--unwind 1 --z3" testfiles/testcomp22/product-lines/email_spec11_product30.cil.c
```