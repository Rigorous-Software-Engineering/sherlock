// SKIP PARAM: --set ana.activated[+] apron --set ana.path_sens[+] threadflag
// Copied from 01/45 for apron.


int isNan(float arg) {
  float x;
  return arg != arg;
}

int main() {
  struct blub {
    float f;
  } s;
  float fs[3];

  float top;
  // float may be NaN here, therefore the comaprison should be unknown
  __goblint_check(top == top);     // UNKNOWN!
  __goblint_check(s.f == s.f);     // UNKNOWN!
  __goblint_check(fs[1] == fs[1]); // UNKNOWN!

  int r = isNan(top);

  if (r) {
    __goblint_check(1);
  } else {
    __goblint_check(1);
  }
}
