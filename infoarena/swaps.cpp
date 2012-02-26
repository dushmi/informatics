#include <cstdio>

const int Nmax = 1000005;

int N, P, A, B;

double d[Nmax], newd[Nmax];

void inm(double a[2][2], double b[2][2], double c[2][2]) {
  double aux[2][2];

  for (int i = 0; i < 2; ++i)
    for (int k = 0; k < 2; ++k) {
      aux[i][k] = 0;
      for (int j = 0; j < 2; ++j)
        aux[i][k] += b[i][j] * c[j][k];
    }

  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j)
      a[i][j] = aux[i][j];
}

void solve() {
  scanf("%d%d%d%d", &N, &P, &A, &B);

  double p1 = 2.0 / ((double)N * N), p2 = (double)(N - 2) / N;

  double rez[2][2], mat[2][2];

  rez[0][0] = 1; rez[0][1] = 0;
  rez[1][0] = 0; rez[1][1] = 1;

  mat[0][0] = p1 + p2; mat[0][1] = p1 * (N - 1);
  mat[1][0] = p1; mat[1][1] = p1 * (N - 1) + p2;

  while (P) {
    if (P & 1)
      inm(rez, rez, mat);

    inm(mat, mat, mat);

    P >>= 1;
  }

  double ap = rez[0][0], bp = rez[1][0];

  if (A == B)
    printf("%.9lf\n", ap);
  else
    printf("%.9lf\n", bp);
}

int main() {
  freopen("swaps.in", "r", stdin);
  freopen("swaps.out", "w", stdout);

  int T;

  scanf("%d", &T);

  for (int i = 1; i <= T; ++i)
    solve();

  return 0;
}
