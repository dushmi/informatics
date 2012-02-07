#include <cstdio>
#include <cassert>
#include <cmath>

int n, r;

int main() {
  assert(freopen("insula.in", "r", stdin));
  assert(freopen("insula.out", "w", stdout));

  assert(scanf("%d", &n));

  for (int i = 1; i <= n; ++i) {
    assert(scanf("%d", &r));
    
    double rez = 1.0 / sqrt(r * 1.0 * r + 1.0);

    printf("%.3lf\n", (double)((long long)(rez * 1000.0)) / 1000.0);
  }

  return 0;
}
