// PARAM: --set ana.activated[+] var_eq --set ana.ctx_insens[+] var_eq --set
// ana.activated[+] taintPartialContexts


void f(int *zptr) {}

int main() {
  int z, x;

  f(&z);
  z = x;
  f(&z);

  __goblint_check(z == x);
}
