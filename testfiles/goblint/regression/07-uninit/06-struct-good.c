// PARAM: --set ana.activated[+] uninit
typedef struct {
  int i;
} S;

int main() {
  S ss;
  ss.i = 0;
  return ss.i; // NOWARN
}
