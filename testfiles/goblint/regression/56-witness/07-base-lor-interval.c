// PARAM: --enable ana.int.interval --set witness.yaml.validate
// 07-base-lor-interval.yml


int main() {
  int r; // rand
  int x;
  __goblint_assume(x >= 2);
  ; // SUCCESS (witness)
  ; // SUCCESS (witness)
  return 0;
}
