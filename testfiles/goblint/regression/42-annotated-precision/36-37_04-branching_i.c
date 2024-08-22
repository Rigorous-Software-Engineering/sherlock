// PARAM: --set sem.int.signed_overflow assume_none --enable
// annotation.int.enabled --set ana.int.refinement fixpoint


int main()
    __attribute__((goblint_precision("no-def_exc", "interval", "congruence")));

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
    __goblint_check(k > 0);
  } else {
    __goblint_check(k <= 0);
  }

  return 0;
}
