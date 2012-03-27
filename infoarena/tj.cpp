#include <cstdio>

const int N = 257;

bool L[N][N];

short int n, v[N], deg[N];

void reset() {
  for (short int i = 0; i <= n; ++i) {
    deg[i] = 0;

    for (short int j = 0; j <= n; ++j)
      L[i][j] = 0;
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

bool nrtri(short int x, short int size) {
  for (short int i = 0; i < size; ++i) 
    if (L[x][v[i]]) {
      short int rez = 0;

      for (short int j = 0; j < size; ++j)
        if (L[x][v[j]] && L[v[i]][v[j]])
          ++rez;
    
      if (rez == deg[x] - 1)
        return 1;
    }
  
  return 0;
}

void solve() {
  short int size = 0;
  
  for (short int i = 1; i <= n; ++i)
    v[size++] = i;
  
  bool ok = 1;

  while (size >= 2 && ok) {
    ok = 0;

    for (short int i = 0; i < size && !ok; ++i)
      if (nrtri(v[i], size)) {
        for (short int k = 0; k < size; ++k)
          if (L[v[i]][v[k]])
            --deg[v[k]];
            
        ok = 1;
        v[i] = v[size - 1];
        --size;
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

    solve();
  }

  return 0;
}
