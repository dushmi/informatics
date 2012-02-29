#include <cstdio>
#include <cassert>

const int N = 1205, INF = 0x3f3f3f3f;

int n, steps[N], fee[N], water[N], energy[N];

void read() {
  int k, l, x, y;
  
  assert(scanf("%d", &n));

  assert(scanf("%d", &k));
  for (int i = 1; i <= k; ++i) {
    assert(scanf("%d%d", &x, &y));
    water[x] = y;
  }

  assert(scanf("%d", &l));
  for (int i = 1; i <= l; ++i) {
    assert(scanf("%d%d", &x, &y));
    energy[x] = y;
  }
}

void solve() {
  steps[1] = 1;
  fee[1] = 0;

  for (int i = 2; i <= n; ++i)
    steps[i] = INF;

  for (int i = 1; i < n; ++i)
    if (steps[i]) {
      if (steps[i] + 1 < steps[i + 1]) {
        steps[i + 1] = steps[i] + 1;
        fee[i + 1] = fee[i];
      } else if (steps[i] + 1 == steps[i + 1] && fee[i] < fee[i + 1])
        fee[i + 1] = fee[i];

      // G uses water
      for (int l = 1; l <= water[i] && i + l <= n; ++l)
        if (steps[i] + 1 < steps[i + l]) {
          steps[i + l] = steps[i] + 1;
          fee[i + l] = fee[i];
        } else if (steps[i] + 1 == steps[i + l] && fee[i] < fee[i + l])
          fee[i + l] = fee[i];
      
      // G uses energy drink
      for (int l = 1; l <= 2 * energy[i] && i + l <= n; ++l)
        if (steps[i] + 1 < steps[i + l]) {
          steps[i + l] = steps[i] + 1;
          fee[i + l] = fee[i] + (l + 1) / 2;
        } else if (steps[i] + 1 == steps[i + l] && fee[i] + (l + 1) / 2 < fee[i + l])
          fee[i + l] = fee[i] + (l + 1) / 2;
    }

  printf("%d %d", steps[n], fee[n]);
}

int main() {
  assert(freopen("scara3.in", "r", stdin));
  assert(freopen("scara3.out", "w", stdout));

  read();

  solve();

  return 0;
}
