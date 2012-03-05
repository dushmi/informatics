#include <cstdio>

int n, f[10];

inline int min(int x, int y) {
  return x < y ? x : y;
}

int main() {
  scanf("%d", &n);

  int x;

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    ++f[x];
  }
  
  int ans = f[4], comb = min(f[1], f[3]);
  ans += comb;
  f[1] -= comb;
  f[3] -= comb;

  if (f[3] != 0)
    ans += f[3];

  ans += f[2] / 2;
  f[2] -= (int)(f[2] / 2) * 2;
  
  if (f[2] == 0) {
    if (f[1] > 0)
      ans += (f[1] - 1) / 4 + 1;
  } else {
    if (f[1] > 2)
      ans += 1 + (f[1] - 2 - 1) / 4 + 1;
    else
      ans += 1;
  }

  printf("%d", ans);

  return 0;
}
