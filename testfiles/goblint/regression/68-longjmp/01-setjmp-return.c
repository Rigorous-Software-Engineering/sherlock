// PARAM: --enable ana.int.interval --enable ana.int.enums --set
// solvers.td3.side_widen never
#include <setjmp.h>
#include <assert.h>


int main(void) {
  jmp_buf jmp_buf;

  __goblint_check(1);
  switch (setjmp(jmp_buf)) {
  case 0:
    __goblint_check(1);
    longjmp(jmp_buf, 1);
    __goblint_check(0); // NOWARN
    break;
  case 1:
    __goblint_check(1);
    break;
  case 2:
    __goblint_check(0); // NOWARN
    break;
  default:
    __goblint_check(0); // NOWARN
    break;
  }
  __goblint_check(1);

  return 0;
}
