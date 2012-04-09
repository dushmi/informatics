#include <cstdio>
#include <cassert>

const int N = 100000, Max = 1000000;

int n, m, fr[Max + 5];

void read() {
  int x;
  
  assert(scanf("%d%d", &n, &m));

  for (int i = 1; i <= n; ++i) {
    assert(scanf("%d", &x));
  
    if (!fr[x])
      fr[x] = 1;
  }
}

void init() {
  for (int i = 1; i <= Max; ++i)
    fr[i] = fr[i - 1] + fr[i];
}

void solve() {
  int x, y;

  for (int i = 1; i <= m; ++i) {
    assert(scanf("%d%d", &x, &y));

    printf("%d\n", fr[y] - fr[x - 1]);
  }
}

int main() {
  assert(freopen("distincte2.in", "r", stdin));
  assert(freopen("distincte2.out", "w", stdout));

  read();

  init();

  solve();

  return 0;
}
