// PARAM: --set ana.int.refinement once --enable ana.int.interval_set --enable
// ana.int.congruence --disable ana.int.def_exc


int main(void) {
  int ret = 0;
  unsigned int s__version;
  if (s__version + 65280 != 768) {
    ret = 0;
  } else {
    ret = 1;
  }

  __goblint_check(ret == 0); // UNKNOWN!
}
