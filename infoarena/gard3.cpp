#include <cstdio>

const int N = 51, Base = 10000;

typedef int Huge[30];

int n, k;

Huge aux, d[N][N][3];

void add(Huge A, Huge B) {
  int i, T = 0;

  for (i = 1; i <= A[0] || i <= B[0] || T; ++i) {
    A[i] += B[i] + T;
    T = A[i] / Base;
    A[i] %= Base;
  }

  A[0] = i - 1;
}

void reset(Huge A) {
  for (int i = 1; i <= A[0]; ++i)
    A[i] = 0;

  A[0] = 0;
}

void mult(Huge A, Huge B, Huge C) {
  A[0] = B[0] + C[0] - 1;

  for (int i = 1; i <= B[0]; ++i)
    for (int j = 1; j <= C[0]; ++j)
      A[i + j - 1] += B[i] * C[j];

  int T = 0;

  for (int i = 1; i <= A[0]; ++i) {
    A[i] += T;
    T = A[i] / Base;
    A[i] %= Base;
  }

  while (T) {
    A[++A[0]] = T % Base;
    T /= Base;
  }
}

void print(Huge A) {
  while (!A[A[0]])
    --A[0];

  printf("%d", A[A[0]]);
  for (int i = A[0] - 1; i >= 1; --i)
    printf("%.4d", A[i]);
}

void solve() {  
  for (int i = 3; i <= n; ++i) {
    d[i][1][0][0] = d[i][1][0][1] = 1;
    d[i][1][2][0] = d[i][1][2][1] = 1;

    for (int j = 2; j <= i - 2; ++j) {
      //splits without node 1
      add(d[i][j][0], d[i - 1][j][2]);
      add(d[i][j][0], d[i - 1][j - 1][2]);

      //splits with node 1
      for (int k = 3; k < i; ++k)
        for (int l = 1; l < j; ++l) {
          reset(aux);
          mult(aux, d[k][j - l][2], d[i - k + 2][l][0]);
          add(d[i][j][1], aux);
        }

      add(d[i][j][2], d[i][j][0]);
      add(d[i][j][2], d[i][j][1]);
    }
  }

  print(d[n][k][2]);
}

int main() {
  freopen("gard3.in", "r", stdin);
  freopen("gard3.out", "w", stdout);

  scanf("%d%d", &n, &k);

  solve();

  return 0;
}
