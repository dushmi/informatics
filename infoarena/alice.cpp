#include <cstdio>
#include <cmath>

const int N = 35;

double x, d[N][N];

int n, r;

void solve() {
  d[0][0] = 1;

  for (int i = 1; i <= n; ++i)
    d[i][0] = 2 * d[i - 1][0];

  for (int j = 1; j <= r; ++j)
    d[0][j] = 2 * d[0][j - 1];

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= r; ++j)
      d[i][j] = d[i - 1][j] * (1 - ((d[i - 1][j] - d[i][j - 1]) / (d[i - 1][j] + d[i][j - 1])));
}

int main() {
  freopen("alice.in", "r", stdin);
  freopen("alice.out", "w", stdout);

  scanf("%d%d%lf", &n, &r, &x);

  solve();

  printf("%0.0lf", floor(d[n][r] * x));

  return 0;
}
