#include <stddef.h>


int main() {
  int *r; // rand

  if (r == NULL) {
    __goblint_check(r == NULL);
  } else {
    __goblint_check(r != NULL);
  }

  if (r != NULL) {
    __goblint_check(r != NULL);
  } else {
    __goblint_check(r == NULL);
  }

  return 0;
}
