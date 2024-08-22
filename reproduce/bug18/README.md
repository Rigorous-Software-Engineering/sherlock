## Bug ID 18

**Analyzer**: `KLEE (https://github.com/klee/klee)`
<br>
**Buggy commit**: `cb5e898561f9b8769d8838bc1bdca17a6f4f5d20`
<br>
**Fixed commit**: `f813c88c8cb868fc9c0be78fbf92a94d72ac02b0`
<br>
**Issue**: `https://github.com/klee/klee/issues/1668`
<br>
**Seed file**: `testfiles/testcomp22/locks/test_locks_15-1.c`
<br>
**Integer seeds**: `280680,3107985,1369023,5918199,9480205`


### Sherlock command

```
./sherlock.sh -s <seed> -t klee -o "--cex-cache-superset=1 --cex-cache-try-all=0 --solver-optimize-divides=0 --return-null-on-zero-malloc=1 --verify-each=1 --polly=0 --polly-2nd-level-tiling=0 --polly-enable-simplify=1 --polly-parallel=0 --polly-register-tiling=0 --polly-reschedule=0 --polly-stmt-granularity=scalar-indep --polly-tiling=0 --polly-vectorizer=stripmine --search=nurs:depth --solver-backend=stp --use-iterative-deepening-time-search=0 --allow-seed-extension=0 --allow-seed-truncation=1 --named-seed-matching=0 --optimize=0 --use-batching-search=1" testfiles/testcomp22/locks/test_locks_15-1.c
```