#include <stdlib.h>


int main() {
  int *x[10];
  int i = 0;

  while (i < 10) {
    x[i++] = malloc(sizeof(int));
  }

  *x[3] = 50;
  *x[7] = 100;
  __goblint_check(*x[8] == 100); // UNKNOWN

  return 0;
}
