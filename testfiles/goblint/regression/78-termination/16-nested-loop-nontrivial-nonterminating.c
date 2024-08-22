// SKIP NONTERM PARAM: --set "ana.activated[+]" termination --set
// ana.activated[+] apron --enable ana.int.interval --set ana.apron.domain
// polyhedra
#include <stdio.h>

int main() {
  int outerCount = 1;

  while (outerCount <= 3) {
    int innerCount = 1;

    while (outerCount < 3 ||
           innerCount > 0) // NONTERMLOOP termination analysis shall mark
                           // beginning of while as non-terminating loop
    {
      printf("(%d, %d) ", outerCount, innerCount);
      innerCount++;
    }

    printf("\n");
    outerCount++;
  }

  return 0;
}
