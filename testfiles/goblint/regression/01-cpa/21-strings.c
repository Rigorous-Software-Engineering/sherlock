

int main() {
  char *str = "0123456789";
  char c1 = str[1];
  char **strh;
  strh = &str;
  c1 = (*strh)[1];
  str[2] = '3';
  __goblint_check(c1 == '1'); // UNKNOWN
  return 0;
}
