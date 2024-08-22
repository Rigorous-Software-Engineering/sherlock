// PARAM:  --enable ana.int.congruence
#include <stdbool.h>


int main() {

  bool x = 1;
  bool y = 1;
  bool z = x + y;
  __goblint_check(z);

  return 0;
}
