#include <cstdio>
#include <cassert>

const int N = 1005, MOD = 9973;

int n, k, ways[N], rez[N], d[N][N][2];

inline void mod(int &x) {
  if (x >= MOD)
    x -= MOD;
}

void init() {
  d[1][1][0] = d[1][1][1] = 1;

  for (int i = 1; i <= k + 1; ++i) {
    ways[i] = d[i][0][0] + d[i][0][1];
    mod(ways[i]);

    for (int j = 1; j <= i; ++j) {
      if (d[i][j][0]) {
        d[i + 1][j - 1][0] += d[i][j][0];
        mod(d[i + 1][j - 1][0]);
        d[i + 1][j + 1][0] += d[i][j][0];
        mod(d[i + 1][j + 1][0]);
      }

      if (d[i][j][1]) {
        d[i + 1][j - 1][1] += d[i][j][1];
        mod(d[i + 1][j - 1][1]);
        d[i + 1][j + 1][1] += d[i][j][1];
        mod(d[i + 1][j + 1][1]);
      }
    }
  }
}

inline int max(int x, int y) {
  return x > y ? x : y;
}

void solve() {
  rez[0] = 1;

  for (int i = 1; i <= n; ++i)
    for (int j = max(i - k, 0); j <= i; ++j)
      rez[i] = (rez[i] + rez[j - 1] * ways[i - j + 1]) % MOD;

  printf("%d\n", rez[n]);
}

int main() {
  assert(freopen("stiva2.in", "r", stdin));
  assert(freopen("stiva2.out", "w", stdout));

  assert(scanf("%d%d", &n, &k));

  init();

  solve();

  return 0;
}
