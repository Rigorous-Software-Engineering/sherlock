// PARAM: --set ana.activated[+] expRelation

#include <stddef.h>

int main() {
  int x;

  // expRelation EvalInt
  __goblint_check(!(x + 1 == x));
  __goblint_check(!(x == x + 1));
  __goblint_check(!(x - 1 == x));
  __goblint_check(!(x == x - 1));
  return 0;
}