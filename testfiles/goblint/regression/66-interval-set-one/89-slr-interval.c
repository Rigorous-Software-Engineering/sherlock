// PARAM: --set ana.int.interval_set true --set solver new
// https://github.com/goblint/analyzer/pull/805#discussion_r933230577
#include <stdio.h>


int main() {
  int a = 1, b = 2, c = 3;
  int x, y, z;
  int w;
  int false = 0;
  int true = 42;

  if (x) {
    __goblint_check(x != 0);
  } else {
    __goblint_check(x == 0);
  }

  __goblint_check(!!true);
  __goblint_check(!false);

  if (a) {
    a = a;
  } else {
    __goblint_check(0); // NOWARN
  }

  if (!a) {
    __goblint_check(0); // NOWARN
  } else {
    a = a;
  }

  if (z != 0) {
    a = 8;
    b = 9;
  } else {
    a = 9;
    b = 8;
  }

  __goblint_check(a);
  __goblint_check(a != b); // UNKNOWN
  __goblint_check(a < 10);
  __goblint_check(a <= 9);
  __goblint_check(!(a < 8));
  __goblint_check(a == 8); // UNKNOWN
  __goblint_check(b > 7);
  __goblint_check(b >= 8);
  __goblint_check(!(a > 9));
  __goblint_check(b == 8); // UNKNOWN

  for (x = 0; x < 10; x++) {
    __goblint_check(x >= 0);
    __goblint_check(x <= 9);
  }
  __goblint_check(x == 10);

  if (0 <= w) {
  } else {
    return 0;
  }

  if (w > 0) {
    __goblint_check(1);
  }

  return 0;
}
