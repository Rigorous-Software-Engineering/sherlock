// SKIP PARAM: --set ana.activated[+] apron --set ana.path_sens[+] threadflag


int f(int x) { return x + 1; }

int main(void) {
  int y = 42;

  y = f(y);
  // combine should forget callee's y after substituting arg vars with args to
  // avoid bottom in #ret substitute

  __goblint_check(y);
  return 0;
}
