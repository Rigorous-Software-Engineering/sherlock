
int main() {
  signed char x;
  unsigned char y;

  // y = 224;
  x = -32;
  if (((signed short)y) == x) {
    // Unreachable
    x = 12;
  }
  __goblint_check(x == -32);
}
