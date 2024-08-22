// This file is part of the SV-Benchmarks collection of verification tasks:
// https://github.com/sosy-lab/sv-benchmarks
//
// SPDX-FileCopyrightText: 2016 Gilles Audemard
// SPDX-FileCopyrightText: 2020 Dirk Beyer <https://www.sosy-lab.org>
// SPDX-FileCopyrightText: 2020 The SV-Benchmarks Community
//
// SPDX-License-Identifier: MIT

extern void abort(void) __attribute__((__nothrow__, __leaf__))
__attribute__((__noreturn__));
extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__((__nothrow__, __leaf__))
__attribute__((__noreturn__));
int __VERIFIER_nondet_int();
void reach_error() { __assert_fail("0", "Haystacks-06.c", 5, "reach_error"); }
void assume(int cond) {
  if (!cond) {
    abort();
  }
}
int main() {
  int cond0;
  int dummy = 0;
  int N;
  int var0;
  var0 = __VERIFIER_nondet_int();
  assume(var0 >= 0);
  assume(var0 <= 5);
  int var1;
  var1 = __VERIFIER_nondet_int();
  assume(var1 >= 0);
  assume(var1 <= 5);
  int var2;
  var2 = __VERIFIER_nondet_int();
  assume(var2 >= 0);
  assume(var2 <= 5);
  int var3;
  var3 = __VERIFIER_nondet_int();
  assume(var3 >= 0);
  assume(var3 <= 5);
  int var4;
  var4 = __VERIFIER_nondet_int();
  assume(var4 >= 0);
  assume(var4 <= 5);
  int var5;
  var5 = __VERIFIER_nondet_int();
  assume(var5 >= 0);
  assume(var5 <= 5);
  int var6;
  var6 = __VERIFIER_nondet_int();
  assume(var6 >= 0);
  assume(var6 <= 5);
  int var7;
  var7 = __VERIFIER_nondet_int();
  assume(var7 >= 0);
  assume(var7 <= 5);
  int var8;
  var8 = __VERIFIER_nondet_int();
  assume(var8 >= 0);
  assume(var8 <= 5);
  int var9;
  var9 = __VERIFIER_nondet_int();
  assume(var9 >= 0);
  assume(var9 <= 5);
  int var10;
  var10 = __VERIFIER_nondet_int();
  assume(var10 >= 0);
  assume(var10 <= 5);
  int var11;
  var11 = __VERIFIER_nondet_int();
  assume(var11 >= 0);
  assume(var11 <= 5);
  int var12;
  var12 = __VERIFIER_nondet_int();
  assume(var12 >= 0);
  assume(var12 <= 5);
  int var13;
  var13 = __VERIFIER_nondet_int();
  assume(var13 >= 0);
  assume(var13 <= 5);
  int var14;
  var14 = __VERIFIER_nondet_int();
  assume(var14 >= 0);
  assume(var14 <= 5);
  int var15;
  var15 = __VERIFIER_nondet_int();
  assume(var15 >= 0);
  assume(var15 <= 5);
  int var16;
  var16 = __VERIFIER_nondet_int();
  assume(var16 >= 0);
  assume(var16 <= 5);
  int var17;
  var17 = __VERIFIER_nondet_int();
  assume(var17 >= 0);
  assume(var17 <= 5);
  int var18;
  var18 = __VERIFIER_nondet_int();
  assume(var18 >= 0);
  assume(var18 <= 5);
  int var19;
  var19 = __VERIFIER_nondet_int();
  assume(var19 >= 0);
  assume(var19 <= 5);
  int var20;
  var20 = __VERIFIER_nondet_int();
  assume(var20 >= 0);
  assume(var20 <= 5);
  int var21;
  var21 = __VERIFIER_nondet_int();
  assume(var21 >= 0);
  assume(var21 <= 5);
  int var22;
  var22 = __VERIFIER_nondet_int();
  assume(var22 >= 0);
  assume(var22 <= 5);
  int var23;
  var23 = __VERIFIER_nondet_int();
  assume(var23 >= 0);
  assume(var23 <= 5);
  int var24;
  var24 = __VERIFIER_nondet_int();
  assume(var24 >= 0);
  assume(var24 <= 5);
  int var25;
  var25 = __VERIFIER_nondet_int();
  assume(var25 >= 0);
  assume(var25 <= 5);
  int var26;
  var26 = __VERIFIER_nondet_int();
  assume(var26 >= 0);
  assume(var26 <= 5);
  int var27;
  var27 = __VERIFIER_nondet_int();
  assume(var27 >= 0);
  assume(var27 <= 5);
  int var28;
  var28 = __VERIFIER_nondet_int();
  assume(var28 >= 0);
  assume(var28 <= 5);
  int var29;
  var29 = __VERIFIER_nondet_int();
  assume(var29 >= 0);
  assume(var29 <= 5);
  int var30;
  var30 = __VERIFIER_nondet_int();
  assume(var30 >= 0);
  assume(var30 <= 5);
  int var31;
  var31 = __VERIFIER_nondet_int();
  assume(var31 >= 0);
  assume(var31 <= 5);
  int var32;
  var32 = __VERIFIER_nondet_int();
  assume(var32 >= 0);
  assume(var32 <= 5);
  int var33;
  var33 = __VERIFIER_nondet_int();
  assume(var33 >= 0);
  assume(var33 <= 5);
  int var34;
  var34 = __VERIFIER_nondet_int();
  assume(var34 >= 0);
  assume(var34 <= 5);
  int var35;
  var35 = __VERIFIER_nondet_int();
  assume(var35 >= 0);
  assume(var35 <= 5);
  int myvar0 = 1;
  assume(var10 != var13);
  assume(var10 + var13 >= 2);
  assume(var10 != var14);
  assume(var10 + var14 >= 2);
  assume(var10 != var21);
  assume(var10 + var21 >= 2);
  assume(var10 != var31);
  assume(var10 + var31 >= 2);
  assume(var10 != var34);
  assume(var10 + var34 >= 2);
  assume(var26 != var0);
  assume(var26 + var0 >= 2);
  assume(var26 != var11);
  assume(var26 + var11 >= 2);
  assume(var26 != var16);
  assume(var26 + var16 >= 2);
  assume(var26 != var25);
  assume(var26 + var25 >= 2);
  assume(var26 != var28);
  assume(var26 + var28 >= 2);
  assume(var32 != var22);
  assume(var32 + var22 >= 2);
  assume(var32 != var29);
  assume(var32 + var29 >= 2);
  assume(var32 != var33);
  assume(var32 + var33 >= 2);
  assume(var32 != var35);
  assume(var32 + var35 >= 2);
  assume(var32 != var8);
  assume(var32 + var8 >= 2);
  assume(var4 != var20);
  assume(var4 + var20 >= 2);
  assume(var4 != var24);
  assume(var4 + var24 >= 2);
  assume(var4 != var27);
  assume(var4 + var27 >= 2);
  assume(var4 != var3);
  assume(var4 + var3 >= 2);
  assume(var4 != var30);
  assume(var4 + var30 >= 2);
  assume(var6 != var12);
  assume(var6 + var12 >= 2);
  assume(var6 != var15);
  assume(var6 + var15 >= 2);
  assume(var6 != var17);
  assume(var6 + var17 >= 2);
  assume(var6 != var18);
  assume(var6 + var18 >= 2);
  assume(var6 != var23);
  assume(var6 + var23 >= 2);
  assume(0 > (var11 - var0) * (var0 - var11));
  assume(0 > (var12 - var17) * (var17 - var12));
  assume(0 > (var13 - var31) * (var31 - var13));
  assume(0 > (var13 - var34) * (var34 - var13));
  assume(0 > (var16 - var0) * (var0 - var16));
  assume(0 > (var16 - var11) * (var11 - var16));
  assume(0 > (var16 - var28) * (var28 - var16));
  assume(0 > (var19 - var1) * (var1 - var19));
  assume(0 > (var19 - var7) * (var7 - var19));
  assume(0 > (var21 - var31) * (var31 - var21));
  assume(0 > (var21 - var34) * (var34 - var21));
  assume(0 > (var22 - var8) * (var8 - var22));
  assume(0 > (var23 - var15) * (var15 - var23));
  assume(0 > (var23 - var18) * (var18 - var23));
  assume(0 > (var24 - var20) * (var20 - var24));
  assume(0 > (var24 - var27) * (var27 - var24));
  assume(0 > (var24 - var3) * (var3 - var24));
  assume(0 > (var24 - var30) * (var30 - var24));
  assume(0 > (var25 - var11) * (var11 - var25));
  assume(0 > (var25 - var28) * (var28 - var25));
  assume(0 > (var27 - var20) * (var20 - var27));
  assume(0 > (var27 - var30) * (var30 - var27));
  assume(0 > (var29 - var22) * (var22 - var29));
  assume(0 > (var29 - var35) * (var35 - var29));
  assume(0 > (var3 - var20) * (var20 - var3));
  assume(0 > (var3 - var30) * (var30 - var3));
  assume(0 > (var33 - var22) * (var22 - var33));
  assume(0 > (var34 - var14) * (var14 - var34));
  assume(0 > (var34 - var31) * (var31 - var34));
  assume(0 > (var35 - var33) * (var33 - var35));
  assume(0 > (var35 - var8) * (var8 - var35));
  assume(0 > (var5 - var1) * (var1 - var5));
  assume(0 > (var7 - var5) * (var5 - var7));
  assume(0 > (var9 - var1) * (var1 - var9));
  assume(0 > (var9 - var7) * (var7 - var9));
  assume(var11 != var28);
  assume(var12 != var15);
  assume(var12 != var18);
  assume(var12 != var23);
  assume(var13 != var14);
  assume(var13 != var21);
  assume(var14 != var31);
  assume(var15 != var17);
  assume(var15 != var18);
  assume(var16 != var25);
  assume(var17 != var18);
  assume(var19 != var2);
  assume(var19 != var5);
  assume(var19 != var9);
  assume(var2 != var1);
  assume(var2 != var5);
  assume(var2 != var7);
  assume(var2 != var9);
  assume(var21 != var14);
  assume(var23 != var17);
  assume(var25 != var0);
  assume(var27 != var3);
  assume(var28 != var0);
  assume(var29 != var33);
  assume(var29 != var8);
  assume(var30 != var20);
  assume(var33 != var8);
  assume(var35 != var22);
  assume(var7 != var1);
  assume(var9 != var5);
  assume(var19 == var10);
  assume(var2 == var6);
  assume(var5 == var4);
  assume(var7 == var26);
  assume(var9 == var32);
  reach_error();
  return 0; /* 0 x[0]1 x[1]2 x[2]3 x[3]4 x[4]5 x[5]6 x[6]7 x[7]8 x[8]9 x[9]10
               x[10]11 x[11]12 x[12]13 x[13]14 x[14]15 x[15]16 x[16]17 x[17]18
               x[18]19 x[19]20 x[20]21 x[21]22 x[22]23 x[23]24 x[24]25 x[25]26
               x[26]27 x[27]28 x[28]29 x[29]30 x[30]31 x[31]32 x[32]33 x[33]34
               x[34]35 x[35] */
}