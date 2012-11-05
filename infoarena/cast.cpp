#include <cstdio>
#include <queue>

using namespace std;

const int N = 12, INF = 0x3f3f3f3f;

int n, c[N][N], d[N][1 << N];

void read() {
  scanf("%d", &n);

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      scanf("%d", &c[i][j]);
}

void init() {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < (1 << n); ++j)
      d[i][j] = INF;

  for (int i = 0; i < n; ++i)
    d[i][1 << i] = 0;
}

int solve(int root, int mask) {
  if (d[root][mask] != INF)
    return d[root][mask];

  vector <int> v;

  for (int i = 0; i < n; ++i)
    if ((mask & (1 << i)) && i != root)
      v.push_back(i);

  for (int i = 1; i < (1 << (int)v.size()); ++i) {
    int newmask = 0;

    for (int j = 0; j < (int)v.size(); ++j)
      if (i & (1 << j))
        newmask |= (1 << v[j]);

    for (int j = 0; j < (int)v.size(); ++j)
      if (i & (1 << j))
        d[root][mask] = min(d[root][mask], max(c[root][v[j]] + solve(v[j], newmask), c[root][v[j]] + solve(root, mask ^ newmask)));
  }

  return d[root][mask];
}

int main() {
  freopen("cast.in", "r", stdin);
  freopen("cast.out", "w", stdout);

  int T;

  scanf("%d", &T);

  for (int i = 1; i <= T; ++i) {
    read();

    init();

    printf("%d\n", solve(0, (1 << n) - 1));
  }

  return 0;
}

