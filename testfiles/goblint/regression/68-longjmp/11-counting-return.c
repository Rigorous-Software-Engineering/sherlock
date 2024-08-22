// PARAM: --enable ana.int.interval --enable ana.int.enums --set
// solvers.td3.side_widen never  --set ana.setjmp.split none

#include <setjmp.h>

jmp_buf my_jump_buffer;

void foo(int count) {
  __goblint_check(count >= 0 && count < 5);
  longjmp(my_jump_buffer, count + 1);
  __goblint_check(0); // NOWARN
}

int main(void) {
  int count = setjmp(my_jump_buffer);
  __goblint_check(count == 0); // UNKNOWN!
  if (count < 5) {
    foo(count);
    __goblint_check(0); // NOWARN
  }
  __goblint_check(count == 5);
}
