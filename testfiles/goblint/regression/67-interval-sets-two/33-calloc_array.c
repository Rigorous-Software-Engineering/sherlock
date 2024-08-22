// PARAM: --set ana.int.interval_set true --set ana.base.arrays.domain
// partitioned

#include <stdlib.h>


int main(void) {
  int *r = calloc(5, sizeof(int));

  __goblint_check(r[0] == 0);

  r[0] = 3;

  __goblint_check(r[0] == 3); // UNKNOWN

  int z = r[1];

  __goblint_check(z == 0); // UNKNOWN
  __goblint_check(z != 365);
}
