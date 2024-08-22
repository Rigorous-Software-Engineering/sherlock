// SKIP PARAM: --set ana.activated[+] apron
// Example from
// https://github.com/sosy-lab/sv-benchmarks/blob/master/c/recursive-simple/afterrec-1.c


void f(int n) {
  if (n < 3) {
    return;
  }
  n--;
  f(n);
  __goblint_check(1);
}

int main(void) { f(4); }
