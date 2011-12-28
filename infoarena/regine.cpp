#include <cstdio>

int n, nr;

void solve() {
  int l = n - (2 * n + 1) / 3 + 1; 
  int la = l, ca = 1;
  
  while (la <= n) {
    printf("%d %d\n", la, ca);
    la += 2;
    ++ca;
  }

  la = l + 1, ca = l + 1;

  while (la <= n) {
    printf("%d %d\n", la, ca);
    la += 2;
    ++ca;
  }
}

int main() {
  freopen("regine.in", "r", stdin);
  freopen("regine.out", "w", stdout);

  scanf("%d", &n);

  nr = (2 * n + 1) / 3;

  printf("%d\n", nr);

  solve();

  return 0;
}
