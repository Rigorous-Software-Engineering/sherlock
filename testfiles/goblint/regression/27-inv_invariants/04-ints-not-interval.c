// PARAM: --disable ana.int.def_exc --enable ana.int.interval


int main() {
  int x;

  if (!x) {
  } else {
    __goblint_check(x == 1); // UNKNOWN!
  }
}
