#include <cstdio>

int n, f[105];

void read() {
  int x;

  scanf("%d", &n);
  
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    ++f[x];
  }
}

void solve() {
  int tot = 0;

  for (int i = 1; i <= 100; ++i)
    tot += f[i] / 2;

  printf("%d\n", tot / 2);
}

int main() {
  read();

  solve();

  return 0;
}
