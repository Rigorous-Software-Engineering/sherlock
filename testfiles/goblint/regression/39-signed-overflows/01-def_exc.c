// PARAM: --set sem.int.signed_overflow assume_none


int main(void) {
  int a;

  if (a != -1) {
    int s = a + 1;
    __goblint_check(s != 0);
  }
}
