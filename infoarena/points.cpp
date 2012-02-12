#include <cstdio>
#include <cassert>

long long f[4];

void read() {
  int n, x, y;

  assert(scanf("%d", &n));

  for (int i = 1; i <= n; ++i) {
    assert(scanf("%d%d", &x, &y));

    f[(x & 1) + ((y & 1) << 1)]++;
  }
}

void solve() {
  long long rez = 0;
  
  bool x1, x2, x3, y1, y2, y3;

  for (int i = 0; i < 4; ++i)
    for (int j = i; j < 4; ++j)
      for (int k = j; k < 4; ++k) {
        x1 = i & 1; y1 = i & 2;
        x2 = j & 1; y2 = j & 2;
        x3 = k & 1; y3 = k & 2;

        int nr = 0;
  
        if (!x1 || (y2 == y3))
          ++nr;
        if (!x2 || (y1 == y3))
          ++nr;
        if (!x3 || (y1 == y2))
          ++nr;

        if (nr == 1 || nr == 3) {
          if (i == j && j == k) 
            rez += f[i] * (f[i] - 1) * (f[i] - 2) / 6;
          else if (i == j)
            rez += f[i] * (f[i] - 1) / 2 * f[k];
          else if (i == k)
            rez += f[i] * (f[i] - 1) / 2 * f[j];
          else if (j == k)
            rez += f[j] * (f[j] - 1) / 2 * f[i];
          else
            rez += f[i] * f[j] * f[k];
        }
      }

  printf("%lld\n", rez);
}

int main() {
  assert(freopen("points.in", "r", stdin));
  assert(freopen("points.out", "w", stdout));

  read();

  solve();

  return 0;
}
