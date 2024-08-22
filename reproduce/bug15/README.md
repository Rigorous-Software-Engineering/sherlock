## Bug ID 15

**Analyzer**: `ESBMC (https://github.com/esbmc/esbmc)`
<br>
**Buggy commit**: `db5ae0a66e178cd666f9574c0e04d3268c93aaeb`
<br>
**Fixed commit**: `db4c241b975597aa24b940f98856431b4a51cf47`
<br>
**Issue**: `https://github.com/esbmc/esbmc/issues/1655`
<br>
**Seed file**: `testfiles/goblint/regression/44-trier_analyzer/40-S6.c`
<br>
**Integer seeds**: `1521326,3256090,967057,841400,3989787`


### Sherlock command

```
./sherlock.sh -s <seed> -t esbmc -c -o "--unwind=100 --no-remove-no-op --partial-loops --goto-unwind --tuple-node-flattener --array-flattener --smt-during-symex --all-runs --interval-analysis-narrowing --interval-analysis-modular --interval-analysis-no-contract" testfiles/goblint/regression/44-trier_analyzer/40-S6.c
```