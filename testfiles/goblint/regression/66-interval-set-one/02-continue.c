// PARAM: --enable ana.int.interval_set --set exp.unrolling-factor 5 --set
// ana.base.arrays.domain unroll --set ana.base.arrays.unrolling-factor 5 Simple
// example


void main(void) {
  int j = 0;

  for (int i = 0; i < 50; i++) {
    if (i < 2) {
      continue;
    }
    if (i > 4) {
      break;
    }
    j++;
  }

  __goblint_check(j == 3);
}
