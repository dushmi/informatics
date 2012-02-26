#include <cstdio>
#include <cassert>

const int N = 1024;

int n, d[N], s[N], m[N][N];

void read() {
  assert(scanf("%d", &n));

  for (int i = 1; i < n; ++i)
    for (int j = 1; j < n - i + 1; ++j) {
      assert(scanf("%d", &m[i][j]));
      d[i] += m[i][j];
      d[i + j] -= m[i][j];
    }
}

void sp() {
  for (int i = 1; i <= n; ++i)
    s[i] = s[i - 1] + d[i];
}

void solve() {
  for (int i = 1; i < n; ++i, printf("\n")) {
    for (int j = 1; j < n - i + 1; ++j)
      printf("%d ", s[i + j - 1] - s[i - 1]);
  
    for (int j = 1; j < n - i + 1; ++j) {
      d[i] -= m[i][j];
      d[i + j] += m[i][j];
    }

    sp();
  }
}

int main() {
  assert(freopen("controlor.in", "r", stdin));
  assert(freopen("controlor.out", "w", stdout));

  read();
  
  sp();

  solve();

  return 0;
}
