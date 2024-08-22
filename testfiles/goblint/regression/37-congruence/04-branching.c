// PARAM: --enable ana.int.congruence --set sem.int.signed_overflow assume_none
// --disable ana.int.def_exc


int main() {
  // A refinement of a congruence class should only take place for the == and !=
  // operator.
  int i;
  if (i == 0) {
    __goblint_check(i == 0);
  } else {
    __goblint_check(i != 0); // UNKNOWN
  }

  int k;
  if (k > 0) {
    __goblint_check(k > 0); // UNKNOWN
  } else {
    __goblint_check(k <= 0); // UNKNOWN
  }

  return 0;
}
