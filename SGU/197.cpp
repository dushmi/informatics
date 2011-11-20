#include <cstdio>
#include <cstring>

typedef int Huge[105];

Huge n;

int m, p, d[32][32], rez[32][32];

void read() {
  char a[105];
  
  scanf("%s", (a + 1));
  
  n[0] = strlen(a + 1);
  for (int i = 1; i <= n[0]; ++i)
    n[i] = a[i] - '0';

  scanf("%d%d", &m, &p);
}

bool compatible(int c1, int c2) {
  bool a[2][5];

  for (int j = 0; j < m; ++j) {
    a[0][j] = c1 & (1 << j);
    a[1][j] = c2 & (1 << j);
  }

  for (int j = 1; j < m; ++j) {
    int nrb = a[0][j - 1] + a[0][j] + a[1][j - 1] + a[1][j];

    if (nrb == 0 || nrb == 4)
      return 0;
  }

  return 1;
}

void matrix() {
  for (int i = 0; i < (1 << m); ++i)
    for (int j = 0; j < (1 << m); ++j)
      d[i][j] = compatible(i, j);
}

void div2(Huge a) {
  int r = 0;

  if (a[a[0]] == 1) {
    r = a[a[0]];
    --a[0];
  }
 
  for (int i = a[0]; i >= 1; --i) {
    r = r * 10 + a[i];
    a[i] = (r >> 1);
    r = (r & 1);
  }
}

void inm(int a[32][32], int b[32][32]) {
  int c[32][32];

  for (int i = 0; i < (1 << m); ++i)
    for (int k = 0; k < (1 << m); ++k) {
      c[i][k] = 0;
      for (int j = 0; j < (1 << m); ++j)
        c[i][k] = (c[i][k] + a[i][j] * b[j][k]) % p;
    }
 
  for (int i = 0; i < (1 << m); ++i)
    for (int j = 0; j < (1 << m); ++j)
      a[i][j] = c[i][j];
}

void solve() {
  for (int i = 0; i < (1 << m); ++i)
    rez[i][i] = 1;

  while (n[0]) {
    if (n[1] & 1)
      inm(rez, d);
    
    inm(d, d);
    
    div2(n);
  }
}

void print() {
  int sol = 0;

  for (int i = 0; i < (1 << m); ++i)
    for (int j = 0; j < (1 << m); ++j)
      sol = (sol + rez[i][j]) % p;

  printf("%d\n", sol);
}

void scad1(Huge a) {
  if (a[0] == 1 && a[1] == 1) {
    a[0] = 0;
    return;
  }
  
  int poz = -1;

  for (int i = a[0]; i >= 1; --i)
    if (a[i])
      poz = i;

  --a[poz];

  for (int i = poz - 1; i >= 1; --i)
    a[i] = 9;

  while (!a[a[0]])
    --a[0];
}

int main() {
  read();

  matrix();
  
  scad1(n);

  solve();

  print();

  return 0;
}
