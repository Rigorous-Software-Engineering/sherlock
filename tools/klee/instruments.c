#include <stdbool.h>
#include <stddef.h>
#include "klee/klee.h"
#include <assert.h>

void __VERIFIER_assume(int cond){
  klee_assume(cond);
}

void __VERIFIER_assert(int cond){
  klee_assert(cond);
}

void __VERIFIER_error(){
  klee_assert(0);
}

bool __VERIFIER_nondet_bool() { bool val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
unsigned short __VERIFIER_nondet_ushort() { unsigned val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
unsigned __VERIFIER_nondet_unsigned() { unsigned val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
unsigned long long __VERIFIER_nondet_ulonglong() { unsigned long long val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
unsigned long __VERIFIER_nondet_ulong() { unsigned long val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
unsigned long long __VERIFIER_nondet_uint128() { unsigned long long val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
unsigned int __VERIFIER_nondet_uint() { unsigned int val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
unsigned char __VERIFIER_nondet_uchar() { unsigned char val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
size_t __VERIFIER_nondet_size_t() { size_t val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
short __VERIFIER_nondet_short() { short val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
long long __VERIFIER_nondet_longlong() { long long val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
long __VERIFIER_nondet_long() { long val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
long long __VERIFIER_nondet_int128() { long long val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
int __VERIFIER_nondet_int() { int val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
char __VERIFIER_nondet_char() { char val;   klee_make_symbolic(&val, sizeof(val), "val"); return val; }
