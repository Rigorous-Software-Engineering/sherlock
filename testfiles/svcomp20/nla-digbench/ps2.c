extern void __VERIFIER_error() __attribute__((__noreturn__));
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assume(int expression);
void __VERIFIER_assert(int cond) {
  if (!(cond)) {
  ERROR:
    __VERIFIER_error();
  }
  return;
}

int main() {
  int k, y, x, c;
  k = __VERIFIER_nondet_int();

  y = 0;
  x = 0;
  c = 0;

  while (1) {
    __VERIFIER_assert((y * y) - 2 * x + y == 0);

    if (!(c < k)) {
      break;
    }

    c = c + 1;
    y = y + 1;
    x = y + x;
  }
  __VERIFIER_assert((y * y) - 2 * x + y == 0);

  return 0;
}
