#include <cstdio>

const int N = 4005, INF = 0x3f3f3f3f;

int n, k, st[N], time[N], ans[N], d[N][N];

void read() {
  scanf("%d%d", &n, &k);

  for (int i = 1; i <= n; ++i)
    scanf("%d%d", &st[i], &time[i]);
}

inline int min(int x, int y) {
  return x < y ? x : y;
}

inline int max(int x, int y) {
  return x > y ? x : y;
}

void solve() {
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= k; ++j)
      d[i][j] = INF;

  d[1][0] = st[1] + time[1] - 1;
  d[1][1] = 0;

  for (int i = 1; i < n; ++i)
    for (int j = 0; j <= k; ++j) {
      //update for i + 1, j
      if (d[i][j] >= st[i + 1])
        d[i + 1][j] = min(d[i + 1][j], d[i][j] + time[i + 1]);
      else
        d[i + 1][j] = min(d[i + 1][j], st[i + 1] + time[i + 1] - 1);

      //update for i + 1, j + 1
      d[i + 1][j + 1] = min(d[i + 1][j + 1], d[i][j]);
    }

  for (int i = 1; i <= n; ++i) {
    ans[i] = INF;
    for (int j = 0; j <= k; ++j)
      ans[i] = min(ans[i], d[i][j]);
  }

  int rez = st[1] - 1;

  for (int i = 2; i <= n; ++i)
    rez = max(rez, st[i] - ans[i - 1] - 1);

  rez = max(rez, 86400 - ans[n]);

  printf("%d\n", rez);
}

int main() {
  read();

  solve();

  return 0;
}
