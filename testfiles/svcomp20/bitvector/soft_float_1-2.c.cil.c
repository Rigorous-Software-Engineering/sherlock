extern void __VERIFIER_error() __attribute__((__noreturn__));
extern void __VERIFIER_assume(int);

extern char __VERIFIER_nondet_char(void);
extern unsigned int __VERIFIER_nondet_uint(void);
void __VERIFIER_assert(int cond) {
  if (!(cond)) {
  ERROR:
    __VERIFIER_error();
  }
  return;
}
/* Generated by CIL v. 1.3.7 */
/* print_CIL_Input is true */

unsigned int base2flt(unsigned int m, int e) {
  unsigned int res;
  unsigned int __retres4;

  {
    if (!m) {
      __retres4 = 0U;
      goto return_label;
    } else {
    }
    if (m < 1U << 24U) {
      {
        while (1) {
        while_0_continue: /* CIL Label */;
          if (e <= -128) {
            __retres4 = 0U;
            goto return_label;
          } else {
          }
          e = e - 1;
          m = m << 1U;
          if (m < 1U << 24U) {

          } else {
            goto while_0_break;
          }
        }
      while_0_break: /* CIL Label */;
      }
    } else {
      {
        while (1) {
        while_1_continue: /* CIL Label */;
          if (m >= 1U << 25U) {

          } else {
            goto while_1_break;
          }
          if (e >= 127) {
            __retres4 = 4294967295U;
            goto return_label;
          } else {
          }
          e = e + 1;
          m = m >> 1U;
        }
      while_1_break: /* CIL Label */;
      }
    }
    m = m & ~(1U << 24U);
    res = m | (unsigned int)((e + 128) << 24U);
    __retres4 = res;
  return_label: /* CIL Label */
    return (__retres4);
  }
}
unsigned int addflt(unsigned int a, unsigned int b) {
  unsigned int res;
  unsigned int ma;
  unsigned int mb;
  unsigned int delta;
  int ea;
  int eb;
  unsigned int tmp;
  unsigned int __retres10;

  {
    if (a < b) {
      tmp = a;
      a = b;
      b = tmp;
    } else {
    }
    if (!b) {
      __retres10 = a;
      goto return_label;
    } else {
    }
    {
      ma = a & ((1U << 24U) - 1U);
      ea = (int)(a >> 24U) - 128;
      ma = ma | (1U << 24U);
      mb = b & ((1U << 24U) - 1U);
      eb = (int)(b >> 24U) - 128;
      mb = mb | (1U << 24U);
      __VERIFIER_assert(ea >= eb);
      delta = ea - eb;
      __VERIFIER_assume(delta < sizeof(mb) * 8);
      mb = mb >> delta;
    }
    if (!mb) {
      __retres10 = a;
      goto return_label;
    } else {
    }
    ma = ma + mb;
    if (ma & (1U << 25U)) {
      if (ea == 127) {
        __retres10 = 4294967295U;
        goto return_label;
      } else {
      }
      ea = ea + 1;
      ma = ma >> 1U;
    } else {
    }
    {
      __VERIFIER_assert(ma < 1U << 25U);
      ma = ma & ((1U << 24U) - 1U);
      res = ma | (unsigned int)((ea + 128) << 24U);
    }
    __retres10 = res;
  return_label: /* CIL Label */
    return (__retres10);
  }
}
unsigned int mulflt(unsigned int a, unsigned int b) {
  unsigned int res;
  unsigned int ma;
  unsigned int mb;
  unsigned long long accu;
  int ea;
  int eb;
  unsigned int tmp;
  unsigned int __retres10;

  {
    if (a < b) {
      tmp = a;
      a = b;
      b = tmp;
    } else {
    }
    if (!b) {
      __retres10 = 0U;
      goto return_label;
    } else {
    }
    ma = a & ((1U << 24U) - 1U);
    ea = (int)(a >> 24U) - 128;
    ma = ma | (1U << 24U);
    mb = b & ((1U << 24U) - 1U);
    eb = (int)(b >> 24U) - 128;
    mb = mb | (1U << 24U);
    ea = ea + eb;
    ea = ea + 24;
    if (ea > 127) {
      __retres10 = 4294967295U;
      goto return_label;
    } else {
    }
    if (ea < -128) {
      __retres10 = 0U;
      goto return_label;
    } else {
    }
    accu = ma;
    accu = accu * (unsigned long long)mb;
    accu = accu >> 24U;
    if (accu >= (unsigned long long)(1U << 25U)) {
      if (ea == 127) {
        __retres10 = 4294967295U;
        goto return_label;
      } else {
      }
      ea = ea + 1;
      accu = accu >> 1U;
      if (accu >= (unsigned long long)(1U << 25U)) {
        __retres10 = 4294967295U;
        goto return_label;
      } else {
      }
    } else {
    }
    {
      __VERIFIER_assert(accu < (unsigned long long)(1U << 25U));
      __VERIFIER_assert(accu & (unsigned long long)(1U << 24U));
      ma = accu;
      ma = ma & ~(1U << 24U);
      res = ma | (unsigned int)((ea + 128) << 24U);
    }
    __retres10 = res;
  return_label: /* CIL Label */
    return (__retres10);
  }
}
int main(void) {
  unsigned int a;
  unsigned int ma = __VERIFIER_nondet_uint();
  signed char ea = __VERIFIER_nondet_char();
  unsigned int b;
  unsigned int mb = __VERIFIER_nondet_uint();
  signed char eb = __VERIFIER_nondet_char();
  unsigned int r_add;
  unsigned int zero;
  int sa;
  int sb;
  int tmp;
  int tmp___0;
  int tmp___1;
  int tmp___2;
  int tmp___3;
  int tmp___4;
  int tmp___5;
  int tmp___6;
  int tmp___7;
  int tmp___8;
  int tmp___9;
  int __retres23;

  {
    {
      zero = base2flt(0, 0);
      a = base2flt(ma, ea);
      b = base2flt(mb, eb);
    }
    if (a < zero) {
      sa = -1;
    } else {
      if (a > zero) {
        tmp = 1;
      } else {
        tmp = 0;
      }
      sa = tmp;
    }
    if (b < zero) {
      sb = -1;
    } else {
      if (b > zero) {
        tmp___0 = 1;
      } else {
        tmp___0 = 0;
      }
      sb = tmp___0;
    }
    { r_add = addflt(a, b); }
    if (sa > 0) {
      if (sb > 0) {
        if (r_add < a) {
          tmp___2 = -1;
        } else {
          if (r_add > a) {
            tmp___1 = 1;
          } else {
            tmp___1 = 0;
          }
          tmp___2 = tmp___1;
        }
        { __VERIFIER_assert(tmp___2 >= 0); }
        if (r_add < b) {
          tmp___4 = -1;
        } else {
          if (r_add > b) {
            tmp___3 = 1;
          } else {
            tmp___3 = 0;
          }
          tmp___4 = tmp___3;
        }
        { __VERIFIER_assert(tmp___4 >= 0); }
      } else {
      }
    } else {
    }
    if (sa == 0) {
      goto _L;
    } else {
      if (sb == 0) {
      _L: /* CIL Label */
        if (r_add < a) {
          tmp___6 = -1;
        } else {
          if (r_add > a) {
            tmp___5 = 1;
          } else {
            tmp___5 = 0;
          }
          tmp___6 = tmp___5;
        }
        if (tmp___6 == 0) {
          tmp___9 = 1;
        } else {
          if (r_add < b) {
            tmp___8 = -1;
          } else {
            if (r_add > b) {
              tmp___7 = 1;
            } else {
              tmp___7 = 0;
            }
            tmp___8 = tmp___7;
          }
          if (tmp___8 == 0) {
            tmp___9 = 1;
          } else {
            tmp___9 = 0;
          }
        }
        { __VERIFIER_assert(tmp___9); }
      } else {
      }
    }
    __retres23 = 0;
    return (__retres23);
  }
}
