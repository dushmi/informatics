#include <cstdio>

const int N = 1005, INF = 2000000000;

int n, k, l, st, sl[N][N], sc[N][N], sd[N][N], d[N][N], a[N][N];

void read() {
  scanf("%d%d", &n, &k);
  
  l = n - k;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= i; ++j) {
      scanf("%d", &a[i][j]);
      st += a[i][j];
    }
}

// sl[i][j] = suma pe linia i pana la elementul j
// sc[i][j] = suma pe coloana j pana la elementul i
// sd[i][j] = suma pe diagonale paralele cu diagonala principala pana
// la elementul (i, j)
void init() {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= i; ++j)
      sl[i][j] = sl[i][j - 1] + a[i][j];
  
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= i; ++j)
      sc[i][j] = sc[i - 1][j] + a[i][j];

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= i; ++j)
      sd[i][j] = sd[i - 1][j - 1] + a[i][j];
}

void init_din(int lin) {
  int sum = 0;
  
  for (int j = 1; j <= l; ++j)
    sum += sc[lin][j];

  for (int j = 1; j <= l; ++j) {
    d[lin][j] = sum;
    sum -= sc[lin][j];
  }
}

inline int min(int x, int y) {
  return x < y ? x : y;
}

// d[i][j] = suma tringhiului de latura n - k ce are coltul stanga jos 
// in (i, j)
void solve() {
  init_din(l);

  for (int i = l + 1; i <= n; ++i)
    for (int j = 1; j <= i; ++j) {
      d[i][j] = d[i - 1][j] + (sl[i][min(j + l - 1, i)] - sl[i][j - 1]);
      if (j + l - 1 <= i - 1)
        d[i][j] -= (sd[i - 1][j + l - 1] - sd[i - l - 1][j - 1]);
    }
}

void print() {
  int rez = INF;

  for (int i = l; i <= n; ++i)
    for (int j = 1; j + l - 1 <= i; ++j)
      if (d[i][j] < rez)
        rez = d[i][j];
  
  rez = st - rez;

  printf("%d\n", rez);
}

int main() {
  freopen("ferma2.in", "r", stdin);
  freopen("ferma2.out", "w", stdout);

  read();
 
  if (l == 0) {
    printf("%d\n", st);
    return 0;
  }

  if (l == n) {
    printf("0\n");
    return 0;
  }

  init();

  solve();

  print();

  return 0;
}

