// PARAM: --set exp.earlyglobs true --set exp.exclude_from_earlyglobs[+] "'g'"


int g = 10;
int main(void) {
  g = 100;
  __goblint_check(g == 100);
  return 0;
}
