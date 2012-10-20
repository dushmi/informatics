#include <cstdio>
#include <cassert>

const int kMaxN = 31;

int N, d[kMaxN][kMaxN][kMaxN][kMaxN];

void init() {
  for (int i = 0; i < kMaxN; ++i)
    for (int j = 0; j < kMaxN; ++j)
      for (int k = 0; k < kMaxN; ++k)
        for (int l = 0; l < kMaxN; ++l)
          d[i][j][k][l] = -1;
}

void test(int &x, int y) {
  if (x == -1) {
    if (y == 0)
      x = 0;

    if (y == 1)
      x = 2;

    if (y == 2)
      x = 1;
  }

  if (x == 0 && y == 2)
      x = 1;

  if (x == 2) {
    if (y == 0)
      x = 0;

    if (y == 2)
      x = 1;
  }
}

int solve(int n2, int n3, int n4, int score) {
  if (n2 == N) {
    if (score == N - score)
      d[n2][n3][n4][score] = 0;

    if (score > N - score)
      d[n2][n3][n4][score] = 1;

    if (score < N - score)
      d[n2][n3][n4][score] = 2;
  }

  if (d[n2][n3][n4][score] != -1)
    return d[n2][n3][n4][score];
  int asda = 0;
  int n1 = 2 * N - (n2 * 2 + n3 * 3 + n4 * 4);
  int n0 = N - (n1 + n2 + n3 + n4);

  if (n0) {
    if (n2) {
      if (score)
        test(d[n2][n3][n4][score], solve(n2 - 1, n3, n4, (n2 - 1) - (score - 1)));

      if (n2 - score)
        test(d[n2][n3][n4][score], solve(n2 - 1, n3, n4, (n2 - 1) - score));
    }

    if (n3)
      test(d[n2][n3][n4][score], solve(n2 + 1, n3 - 1, n4, (n2 + 1) - (score + 1)));

    if (n4)
      test(d[n2][n3][n4][score], solve(n2, n3 + 1, n4 - 1, n2 - score));
  }

  if (n1) {
    if (n3)
      test(d[n2][n3][n4][score], solve(n2 + 2, n3 - 1, n4, (n2 + 2) - (score + 2)));

    if (n4)
      test(d[n2][n3][n4][score], solve(n2 + 1, n3 + 1, n4 - 1, (n2 + 1) - (score + 1)));
  }

  if (n2) {
    if (n4) {
      if (score)
        test(d[n2][n3][n4][score], solve(n2 - 1, n3 + 2, n4 - 1, (n2 - 1) - (score - 1)));

      if (n2 - score)
        test(d[n2][n3][n4][score], solve(n2 - 1, n3 + 2, n4 - 1, (n2 - 1) - score));
    }
  }

  return d[n2][n3][n4][score];
}

int main() {
  assert(freopen("doipatru.in", "r", stdin));
  assert(freopen("doipatru.out", "w", stdout));

  init();

  int T;
  assert(scanf("%d%d", &N, &T) == 2);

  for (int i = 1; i <= T; ++i) {
    int f[5];
    f[0] = f[1] = f[2] = f[3] = f[4] = 0;

    for (int i = 1; i <= N; ++i) {
      int x;
      assert(scanf("%d", &x));

      ++f[x];
    }

    printf("%d\n", solve(f[2], f[3], f[4], f[2] / 2));
  }

  return 0;
}

