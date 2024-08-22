// PARAM: --enable ana.int.interval --enable ana.int.enums --set
// solvers.td3.side_widen never

#include <setjmp.h>

jmp_buf my_jump_buffer;
int count = 0;

void foo() {
  __goblint_check(count >= 0 && count < 5);
  count++;
  longjmp(my_jump_buffer, 1);
  __goblint_check(0); // NOWARN
}

int main(void) {
  setjmp(my_jump_buffer);
  __goblint_check(count == 0); // UNKNOWN!
  if (count < 5) {
    foo();
    __goblint_check(0); // NOWARN
  }
  __goblint_check(count == 5);
}
