extern void __VERIFIER_error() __attribute__((__noreturn__));
unsigned int __VERIFIER_nondet_uint();

void __VERIFIER_assert(int cond) {
  if (!(cond)) {
  ERROR:
    __VERIFIER_error();
  }
  return;
}
int b;
_Bool __VERIFIER_nondet_bool();
int main() {
  _Bool k = __VERIFIER_nondet_bool();
  unsigned int i, n, j;
  int a[1025];

  if (k) {
    n = 0;
  } else {
    n = 1023;
  }

  i = 0;
  j = __VERIFIER_nondet_uint();
  if (j > 10000) {
    return 0;
  }

  while (i <= n) {
    i++;
    j = j + 2;
  }

  a[i] = 0;
  __VERIFIER_assert(j < 1025);
  a[j] = 0;
  a[b] = 0;
  if (b >= 0 && b < 1023) {
    a[b] = 1;
  } else {
    a[b % 1023] = 1;
  }

  return 1;
}
