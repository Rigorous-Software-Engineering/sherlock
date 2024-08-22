// Making sure special function lval is not invalidated recursively


extern int *anIntPlease();
int main() {
  int x = 0;
  int *p = &x;
  p = anIntPlease();

  __goblint_check(x == 0);

  return 0;
}
