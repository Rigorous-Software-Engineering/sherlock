// PARAM: --enable ana.int.interval_set --disable ana.context.widen --enable
// ana.base.context.int --set annotation.goblint_context.f[+] base.no-int


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
