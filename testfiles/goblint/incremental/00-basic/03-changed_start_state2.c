

int g = 1;

int main() {
  // After the presolve phase, g is in the start state but neither in the
  // context nor in the start variables. If the change of the start state of
  // main would not be propagated by the call to side on all start variables,
  // the asserts in the incremental run would wrongly fail. Side however only
  // joins with the previous value instead of overwriting, therefore the current
  // imprecision.
  __goblint_check(g == 1);
  __goblint_check(g != 2);
  return 0;
}
