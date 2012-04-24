#include <cstdio>

inline int modul(int x) {
  return x < 0 ? (-x) : x;
}

int main() {
  freopen("cal.in", "r", stdin);
  freopen("cal.out", "w", stdout);

  int x, y, X, Y, S, N, nr = 0;

  scanf("%d%d%d%d", &X, &Y, &S, &N);

  for (int i = 1; i <= N; ++i) {
    scanf("%d%d", &x, &y);

    if (modul(x - X) + modul(y - Y) == S)
      ++nr;
  }

  printf("%d\n", nr);

  return 0;
}
