// PARAM: --enable ana.int.interval --disable ana.context.widen


int f(int x) __attribute__((goblint_context(
    "widen"))); // attributes are not permitted in a function definition
int f(int x) {
  if (x) {
    return f(x + 1);
  } else {
    return x;
  }
}

int main() {
  int a = f(1);
  __goblint_check(!a);
  return 0;
}
