extern void abort(void);
extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__((__nothrow__, __leaf__))
__attribute__((__noreturn__));
void reach_error() { __assert_fail("0", "matrix-2-2.c", 3, "reach_error"); }

void __VERIFIER_assert(int cond) {
  if (!(cond)) {
  ERROR : {
    reach_error();
    abort();
  }
  }
  return;
}
extern unsigned int __VERIFIER_nondet_uint();
extern int __VERIFIER_nondet_int();

int main() {
  unsigned int N_LIN = __VERIFIER_nondet_uint();
  unsigned int N_COL = __VERIFIER_nondet_uint();
  if (N_LIN >= 4000000000 / sizeof(int) || N_COL >= 4000000000 / sizeof(int)) {
    return 0;
  }
  unsigned int j, k;
  int matriz[N_COL][N_LIN], maior;

  maior = __VERIFIER_nondet_int();
  for (j = 0; j < N_COL; j++) {
    for (k = 0; k < N_LIN; k++) {
      matriz[j][k] = __VERIFIER_nondet_int();

      if (matriz[j][k] > maior) {
        maior = matriz[j][k];
      }
    }
  }

  for (j = 0; j < N_COL; j++) {
    for (k = 0; k < N_LIN; k++) {
      __VERIFIER_assert(matriz[j][k] < maior);
    }
  }
}
