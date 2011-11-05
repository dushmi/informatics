#include <cstdio>

int n, a, b;

int main() {
  scanf("%d%d%d", &n, &a, &b);

  int pos = 0;

  for (int x = a; x < n; ++x)
    if (n - x - 1 <= b)
      ++pos;

  printf("%d\n", pos);
}
