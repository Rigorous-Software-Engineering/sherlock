// PARAM: --set otherfun "['f']" --enable exp.earlyglobs


int glob;

void f() {
  int i = glob;
  __goblint_check(i == 0);
}

int main(void *arg) { return 0; }
