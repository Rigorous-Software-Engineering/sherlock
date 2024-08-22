// SKIP NONTERM PARAM: --set "ana.activated[+]" termination --set
// ana.activated[+] apron --enable ana.int.interval --set ana.apron.domain
// polyhedra --enable ana.context.widen
#include <stdio.h>

void recursiveFunction(int n) // NONTERMFUNDEC termination analysis shall mark
                              // fundec of non-terminating function
{
  // Base case: When n reaches 0, stop recursion
  if (n == 30) {
    printf("Terminating recursion\n");
    return;
  }

  printf("Recursive call with n = %d\n", n);

  // Recursive call: Decrement n and call the function again
  recursiveFunction(n - 1);
}

int main() {
  // Call the recursive function with an initial value
  recursiveFunction(5);

  return 0;
}
