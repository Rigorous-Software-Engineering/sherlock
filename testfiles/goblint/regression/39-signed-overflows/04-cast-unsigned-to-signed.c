// PARAM: --enable ana.int.interval --set sem.int.signed_overflow assume_none


int main(void) {
  unsigned long x;
  long y = x;
  __goblint_check(y >= 0); // UNKNOWN!
  return 0;
}
