#include <cstdio>

const int N = 105;

int n, s, p, points[N];

void read() {
  scanf("%d%d%d", &n, &s, &p);

  for (int i = 1; i <= n; ++i)
    scanf("%d", &points[i]);
}

bool check(int x) {
  if (x % 3 == 0) {
    if (x / 3 >= p)
      return 1;

    return 0;
  }

  if (x / 3 + 1 >= p)
    return 1;

  return 0;
}

bool checks(int x) {
  if (x % 3 == 2) {
    if (x / 3 + 2 >= p)
      return 1;

    return 0;
  }

  if (x / 3 + 1 >= p)
    return 1;

  return 0;
}

int solve() {
  int sol = 0;

  for (int i = 1; i <= n; ++i) {
    if (check(points[i])) {
      ++sol;
      continue;
    }

    if (s == 0)
      continue;

    if (checks(points[i]) && points[i] >= 2 && points[i] <= 28) {
      ++sol;
      --s;
    }
  }

  return sol;
}

int main() {
  //freopen("data.in", "r", stdin);
  //freopen("data.out", "w", stdout);

  int T;

  scanf("%d", &T);

  for (int i = 1; i <= T; ++i) {
    read();
    
    printf("Case #%d: %d\n", i, solve());
  }

  return 0;
}
