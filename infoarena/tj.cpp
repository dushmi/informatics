#include <cstdio>

const int N = 257;

bool L[N][N];

short int n, v[N], deg[N], tri[N][N];

void reset() {
  for (short int i = 0; i <= n; ++i) {
    deg[i] = 0;

    for (short int j = 0; j <= n; ++j) {
      L[i][j] = 0;
      tri[i][j] = 0;
    }
  }
}

void read() {
  int m, x, y;

  scanf("%hd%d", &n, &m);

  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &x, &y);

    L[x][y] = L[y][x] = 1;
    ++deg[x];
    ++deg[y];
  }
}

void init() {
  for (short int i = 1; i <= n; ++i)
    for (short int j = i + 1; j <= n; ++j)
      if (L[i][j])
        for (short int k = 1; k <= n; ++k)
          if (i != k && j != k && L[i][k] && L[j][k])
            ++tri[i][j], ++tri[j][i];
}

void solve() {
  short int size = 0;
  
  for (short int i = 1; i <= n; ++i)
    v[size++] = i;
  
  bool ok = 1;

  while (size >= 2 && ok) {
    ok = 0;

    for (short int i = 0; i < size && !ok; ++i)
      for (short int j = 0; j < size && !ok; ++j)
        if (v[i] != v[j] && L[v[i]][v[j]]) {
          if (tri[v[i]][v[j]] == deg[v[i]] - 1) {
            for (short int k = 0; k < size; ++k)
              if (L[v[i]][v[k]])
                --deg[v[k]];
            
            for (short int k = 0; k < size; ++k)
              for (short int l = k + 1; l < size; ++l)
                if (L[v[k]][v[l]] && L[v[i]][v[k]] && L[v[i]][v[l]])
                  --tri[v[k]][v[l]], --tri[v[l]][v[k]];

            ok = 1;
            v[i] = v[size - 1];
            --size;
          }
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

  short int T;

  scanf("%hd", &T);

  for (short int i = 1; i <= T; ++i) {
    reset();

    read();

    init();

    solve();
  }

  return 0;
}
