#include <stdbool.h>


int main() {
  int a;
  int *p = &a;

  bool x = p;
  __goblint_check(x);
  bool y = !!p;
  __goblint_check(y);
  bool z = p != 0;
  __goblint_check(z);

  int b = 10;
  bool bb = b;
  __goblint_check(bb);

  return 0;
}