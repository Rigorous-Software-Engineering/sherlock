// PARAM: --enable ana.int.def_exc --disable ana.int.interval --enable
// ana.sv-comp.functions Copied from 56-witness/28-mine-tutorial-ex4.8


extern _Bool __VERIFIER_nondet_bool();
int main() {
  int v = 0;
  while (__VERIFIER_nondet_bool() == 0) {
    __goblint_check(0 <= v);
    __goblint_check(v <= 1);
    if (v == 0) {
      v = 1;
    }
    // ...
  }
  return 0;
}
