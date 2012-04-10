#include <cstdio>

const int N = 257;

bool fr[N], L[N][N];

int n, v[N];

void reset() {
  for (int i = 1; i <= n; ++i) {
    fr[i] = 0;
    for (int j = 1; j <= n; ++j)
      L[i][j] = 0;
  }
}

void read() {
  int m, x, y;

  scanf("%d%d", &n, &m);

  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    
    L[x][y] = L[y][x] = 1;
  }
}

bool valid(int x, int y) {
  for (int i = 1; i <= n; ++i) 
    if (L[y][i] && !fr[i] && i != x)
      if (!L[x][i])
        return 0;
  
  return 1;
}

void solve() {
  bool ok = 1;
  
  int size = n;

  while (size >= 2 && ok) {
    ok = 0;

    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        if (!fr[i] && !fr[j] && L[i][j] && valid(i, j)) {
          --size;
          fr[j] = 1;
          ok = 1;

          for (int k = 1; k <= n; ++k)
            L[k][j] = 0;
        }
  }

  if (size > 1) 
    printf("NU\n");
  else
    printf("DA\n");
}

int main() {
  freopen("tj.in", "r", stdin);
  freopen("tj.out", "w", stdout);

  int T;

  scanf("%d", &T);

  for (int i = 1; i <= T; ++i) {
    reset();

    read();

    solve();
  }

  return 0;
}
