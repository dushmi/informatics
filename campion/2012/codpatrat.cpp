#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

const int N = 105;

char code[N];

int n, op;

void move_left(int n) {
  if (n < 0) {
    printf("%d", op);
    exit(0);
  }

  if (code[n] == '1') {
    code[n] = '2';
    move_left(n - 1);
  } else if (code[n] == '2')
    code[n] = '1';
  else if (code[n] == '3')
    code[n] = '4';
  else {
    code[n] = '3';
    move_left(n - 1);
  }
}

void move_up(int n) {
  if (n < 0) {
    printf("%d", op);
    exit(0);
  }

  if (code[n] == '1') {
    code[n] = '4';
    move_up(n - 1);
  } else if (code[n] == '2') {
    code[n] = '3';
    move_up(n - 1);
  } else if (code[n] == '3')
    code[n] = '2';
  else
    code[n] = '1';
}

void move_right(int n) {
  if (n < 0) {
    printf("%d", op);
    exit(0);
  }

  if (code[n] == '1')
    code[n] = '2';
  else if (code[n] == '2') {
    code[n] = '1';
    move_right(n - 1);
  } else if (code[n] == '3') {
    code[n] = '4';
    move_right(n - 1);
  } else
    code[n] = '3';
}

void move_down(int n) {
  if (n < 0) {
    printf("%d", op);
    exit(0);
  }

  if (code[n] == '1')
    code[n] = '4';
  else if (code[n] == '2')
    code[n] = '3';
  else if (code[n] == '3') {
    code[n] = '2';
    move_down(n - 1);
  } else {
    code[n] = '1';
    move_down(n - 1);
  }
}

void solve() {
  char dir, opc[10];
  int nr;

  while (fgets(opc, 10, stdin)) {
    ++op;

    if (opc[0] != 'L' && opc[0] != 'U' && opc[0] != 'R' && opc[0] != 'D')
      return;

    dir = opc[0];

    nr = opc[2] - '0';
    if (opc[3] >= '0' && opc[3] <= '9') {
      nr = nr * 10 + opc[3] - '0';
      if (opc[4] >= '0' && opc[4] <= '9')
        nr = nr * 10 + opc[4] - '0';
    }

    for (int i = 1; i <= nr; ++i)
      if (dir == 'L')
        move_left(n);
      else if (dir == 'U')
        move_up(n);
      else if (dir == 'R')
        move_right(n);
      else
        move_down(n);
  }
}

int main() {
  assert(freopen("codpatrat.in", "r", stdin));
  assert(freopen("codpatrat.out", "w", stdout));

  assert(fgets(code, N, stdin));

  n = strlen(code) - 2;

  solve();

  printf("%s", code);

  return 0;
}
