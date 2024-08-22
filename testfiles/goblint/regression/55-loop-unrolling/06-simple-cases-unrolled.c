// PARAM: --enable ana.int.interval --set exp.unrolling-factor 5 --set
// ana.base.arrays.domain unroll --set ana.base.arrays.unrolling-factor 5
// --enable dbg.run_cil_check


int global;

int main(void) {
  example1();
  example2();
  example3();
  example4();
  example5();
  example6();
  example7();
  example8();
  example9();
  example10();
  return 0;
}

// Simple example
void example1(void) {
  int a[5];
  int i = 0;

  while (i < 5) {
    a[i] = i;
    i++;
  }

  __goblint_check(a[0] == 0);
  __goblint_check(a[3] == 3);
}

// Do-while loop simple example
void example2(void) {
  int a[5];
  int i = 0;

  do {
    a[i] = i;
    i++;
  } while (i <= 5);

  __goblint_check(a[0] == 0);
  __goblint_check(a[3] == 3);
}

// Initialization not completed, yet the array representation is not precise
void example3(void) {
  int a[10];
  int i = 0;

  while (i < 5) {
    a[i] = i;
    i++;
  }

  __goblint_check(a[0] == 0);
  __goblint_check(a[3] == 0); // FAIL
  __goblint_check(a[7] == 0); // UNKNOWN
}

// Example with increased precision. Goblint detects in which iteration it is
// during the unrolled part.
void example4(void) {
  int a[10];
  int i = 0;
  int first_iteration = 1;

  while (i < 10) {
    if (first_iteration == 1) {
      __goblint_check(i == 0);
    } else if (i > 5) {
      __goblint_check(i == 6); // UNKNOWN
    }
    first_iteration = 0;
    a[i] = 0;
    i++;
  }

  __goblint_check(a[0] == 0);
  __goblint_check(first_iteration == 0);
}

// Example where the precision increase can be appreciated by a variable that
// is modified in the loop other than the ones used in the loop head
void example5(void) {
  int a[4];
  int i = 0;
  int top = 0;

  while (i < 4) {
    a[i] = 0;
    top += i;
    if (i == 2) {
      __goblint_check(top == 3);
    } else {
      __goblint_check(top == 3); // FAIL
    }
    i++;
  }

  __goblint_check(a[0] == 0);
  __goblint_check(a[3] == 0);
  __goblint_check(top == 6);
}

// Loop has less iterations than the unrolling factor
void example6(void) {
  int a[5];
  int i = 0;
  int top = 0;

  while (i < 3) {
    a[i] = 0;
    __goblint_check(a[0] == 0);
    i++;
  }

  __goblint_check(a[0] == 0);
  __goblint_check(a[3] == 0); // UNKNOWN!
  __goblint_check(top == 6);  // FAIL
}

// There is a call on the loop's condition
int update(int i) {
  if (i > 5) {
    return 0;
  } else {
    return 1;
  }
}
void example7(void) {
  int a[10];
  int i = 0;
  while (update(i)) {
    a[i] = i;
    ++i;
  }
  __goblint_check(a[0] == 0); // UNKNOWN
  __goblint_check(a[6] == 0); // UNKNOWN
}

// nested loops
void example8(void) {
  int a[5];
  int b[] = {0, 0, 0, 0, 0};
  int i = 0;
  while (i < 5) {
    a[i] = i;
    int j = 0;
    while (j < 5) {
      b[j] += a[i];
      ++j;
    }
    ++i;
  }
  return 0;
}

// example with loop like the ones CIL does internally (while(1) + break)
void example9(void) {
  int a[5];
  int i = 0;
  while (1) {
    a[i] = i;
    ++i;
    if (i == 5) {
      break;
    }
  }
  return 0;
}

// example with loop containing a "continue" instruction
void example10(void) {
  int a[5];
  int i = 0;
  while (i < 5) {
    if (i == 3) {
      i++;
      continue;
    }
    a[i] = i;
    ++i;
  }
  return 0;
}
