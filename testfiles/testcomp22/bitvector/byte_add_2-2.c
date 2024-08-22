// This file is part of the SV-Benchmarks collection of verification tasks:
// https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks
//
// SPDX-FileCopyrightText: 2012-2021 The SV-Benchmarks Community
// SPDX-FileCopyrightText: 2012 FBK-ES <https://es.fbk.eu/>
//
// SPDX-License-Identifier: Apache-2.0

extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }

extern unsigned int __VERIFIER_nondet_uint(void);
void __VERIFIER_assert(int cond) {
  if (!(cond)) {
  ERROR : {
    reach_error();
    abort();
  }
  }
  return;
}
/* emulates multi-precision addition */
#include <assert.h>

unsigned int mp_add(unsigned int a, unsigned int b) {
  unsigned char a0, a1, a2, a3;
  unsigned char b0, b1, b2, b3;
  unsigned char r0, r1, r2, r3;

  unsigned short carry;
  unsigned short partial_sum;
  unsigned int r;
  unsigned char i;
  unsigned char na, nb;

  a0 = a;
  a1 = a >> 8;
  a2 = a >> 16U;
  a3 = a >> 24U;

  b0 = b;
  b1 = b >> 8U;
  b2 = b >> 16U;
  b3 = b >> 24U;

  na = (unsigned char)4; /* num of components of a */
  if (a3 == (unsigned char)0) {
    na = na - 1;
    if (a2 == (unsigned char)0) {
      na = na - 1;
      if (a1 == (unsigned char)0) {
        na = na - 1;
      }
    }
  }

  nb = (unsigned char)4; /* num of components of b */
  if (b3 == (unsigned char)0) {
    nb = nb - 1;
    if (b2 == (unsigned char)0) {
      nb = nb - 1;
      if (b1 == (unsigned char)0) {
        nb = nb - 1;
      }
    }
  }

  carry = (unsigned short)0;
  i = (unsigned char)0;
  while ((i < na) || (i < nb) || (carry != (unsigned short)0)) {
    partial_sum = carry;
    carry = (unsigned short)0;

    if (i < na) {
      if (i == (unsigned char)0) {
        partial_sum = partial_sum + a0;
      }
      if (i == (unsigned char)1) {
        partial_sum = partial_sum + a1;
      }
      if (i == (unsigned char)2) {
        partial_sum = partial_sum + a2;
      }
      if (i == (unsigned char)3) {
        partial_sum = partial_sum + a3;
      }
    }
    if (i < nb) {
      if (i == (unsigned char)0) {
        partial_sum = partial_sum + b0;
      }
      if (i == (unsigned char)1) {
        partial_sum = partial_sum + b1;
      }
      if (i == (unsigned char)2) {
        partial_sum = partial_sum + b2;
      }
      if (i == (unsigned char)3) {
        partial_sum = partial_sum + b3;
      }
    }
    if (partial_sum > ((unsigned char)255)) {
      partial_sum = partial_sum & ((unsigned char)255);
      carry = (unsigned short)1;
    }

    if (i == (unsigned char)0) {
      r0 = (unsigned char)partial_sum;
    }
    if (i == (unsigned char)1) {
      r1 = (unsigned char)partial_sum;
    }
    if (i == (unsigned char)2) {
      r2 = (unsigned char)partial_sum;
    }
    if (i == (unsigned char)3) {
      r3 = (unsigned char)partial_sum;
    }

    i = i + (unsigned char)1;
  }

  while (i < (unsigned char)4) {
    if (i == (unsigned char)0) {
      r0 = (unsigned char)0;
    }
    if (i == (unsigned char)1) {
      r1 = (unsigned char)0;
    }
    if (i == (unsigned char)2) {
      r2 = (unsigned char)0;
    }
    if (i == (unsigned char)3) {
      r3 = (unsigned char)0;
    }

    i = i + (unsigned char)1;
  }

  r = r0 | (r1 << 8U) | (r2 << 16U) | ((unsigned int)r3 << 24U);

  return r;
}

int main() {
  unsigned int a, b, r;

  a = __VERIFIER_nondet_uint();
  b = 234770789;

  r = mp_add(a, b);

  __VERIFIER_assert(r == a + b);

  return 0;
}
