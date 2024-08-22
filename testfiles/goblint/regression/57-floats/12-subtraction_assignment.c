// PARAM: --enable ana.float.interval


// previously failed in line 7 with "exception
// Invalid_argument("Cilfacade.get_ikind: non-integer type double ")"
//(same error as in sv-comp: float-newlib/float_req_bl_0220a.c)
// similar error also occurred in the additional examples when branching on a
// float argument
int main() {
  double z;
  int x;

  z = 1 - 1.0;

  __goblint_check(z == 0.); // SUCCESS

  if (0.) {
    x = z;
  }

  if (0 == (0. + 1.)) {
    x = z;
  }

  __goblint_check(0); // FAIL
}
