// PARAM: --enable ana.int.interval_set --disable ana.int.def_exc


int main() {
  for (int i = 2; i < 42; i++) {
    int x = i == 2; // NOWARN
    __goblint_check(1);
  }
}
