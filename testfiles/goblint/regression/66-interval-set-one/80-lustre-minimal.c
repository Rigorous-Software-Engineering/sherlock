// PARAM: --enable ana.int.interval_set --enable ana.int.def_exc
// issue #120


int main() {
  // should be LP64
  unsigned long n = 16;
  unsigned long size = 4912;

  __goblint_check(!(0xffffffffffffffffUL / size < n));
}
