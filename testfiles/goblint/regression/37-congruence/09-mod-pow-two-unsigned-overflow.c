// PARAM: --enable ana.int.congruence


int main() {
  unsigned int a = 0;
  unsigned int b = 16;

  while (1) {
    a = a + b * 3;
    b = b + b * 5;
    __goblint_check(a % 16 == 0);
  }

  return 0;
}
