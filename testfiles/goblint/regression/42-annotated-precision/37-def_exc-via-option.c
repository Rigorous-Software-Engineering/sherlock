// PARAM: --enable annotation.int.enabled --set ana.int.refinement fixpoint
// --set annotation.goblint_precision.f[+] def_exc --set
// annotation.goblint_precision.f[+] interval  --set
// annotation.goblint_precision.main[+] def_exc


int f(int in) {
  in++;
  return in;
}

int main() {
  int a = 0;
  __goblint_check(a); // FAIL!
  a = f(a);
  __goblint_check(a);
  return 0;
}
