#include <cstdio>

void solve() {
  int n;
  double x;
  long long sc = 0;
  bool ok = 1;

  scanf("%d", &n);

  for (int i = 1; i <= n; ++i) {
    scanf("%lf", &x);

    x *= (double)2;
    sc += (long long)x;

    if (sc >= (long long)i * (i - 1))
      continue;

    if (ok) {
      printf("NO\n");
      ok = 0;
    }
  }

  if (!ok)
    return;

  if (sc == (long long)n * (n - 1)) {
    printf("YES\n");
    return;
  }

  printf("NO\n");
}

int main() {
  freopen("turneu.in", "r", stdin);
  freopen("turneu.out", "w", stdout);
  
  int t;

  scanf("%d", &t);

  for (int i = 1; i <= t; ++i)
    solve();

  return 0;
}
