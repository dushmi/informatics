#include <cstdio>

const int N = 17;

int n, m, nb, a[N][N], s[N][N], d[N][N * N][N][N][2][2];

struct elem {
  unsigned char i, j, k, l;
  bool x1, x2;
};

elem pred[N][N * N][N][N][2][2];

void read() {
  scanf("%d%d%d", &n, &m, &nb);

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%d", &a[i][j]);
}

// s[i][j] = sum of the first j elements from the ith line
void init() {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      s[i][j] = s[i][j - 1] + a[i][j];
}

void max(int i, int j, int k, int l, int x1, int x2, int ia, int ja, int ka,
                                             int la, int x1a, int x2a, int y) {
  if (d[i][j][k][l][x1][x2] < y) {
    d[i][j][k][l][x1][x2] = y;
    elem aux;
    aux.i = ia;
    aux.j = ja;
    aux.k = ka;
    aux.l = la;
    aux.x1 = x1a;
    aux.x2 = x2a;
    pred[i][j][k][l][x1][x2] = aux;
  }
}

void solve(int line, int x, int k, int l, int left, int right) {
  if (left == 0 && right == 0) {
    for (int kp = k; kp >= 0; --kp)
      for (int lp = l; lp <= m; ++lp)
        if (x + lp - kp + 1 <= nb) {
          max(line + 1, x + lp - kp + 1, kp, lp, 0, 0, line, x, k, l, 0, 0,
                     d[line][x][k][l][0][0] + s[line][lp] - s[line][kp - 1]);
          max(line + 1, x + lp - kp + 1, kp, lp, 0, 1, line, x, k, l, 0, 0,
                     d[line][x][k][l][0][0] + s[line][lp] - s[line][kp - 1]);
          max(line + 1, x + lp - kp + 1, kp, lp, 1, 0, line, x, k, l, 0, 0,
                     d[line][x][k][l][0][0] + s[line][lp] - s[line][kp - 1]);
          max(line + 1, x + lp - kp + 1, kp, lp, 1, 1, line, x, k, l, 0, 0,
                     d[line][x][k][l][0][0] + s[line][lp] - s[line][kp - 1]);
        }
    return;
  }

  if (left == 0 && right == 1) {
    for (int kp = k; kp >= 0; --kp)
      for (int lp = l; lp >= k; --lp)
        if (x + lp - kp + 1 <= nb) {
          max(line + 1, x + lp - kp + 1, kp, lp, 0, 1, line, x, k, l, 0, 1, 
                     d[line][x][k][l][0][1] + s[line][lp] - s[line][kp - 1]);
          max(line + 1, x + lp - kp + 1, kp, lp, 1, 1, line, x, k, l, 0, 1, 
                     d[line][x][k][l][0][1] + s[line][lp] - s[line][kp - 1]);
	      }
    return;
  }

  if (left == 1 && right == 0) {
    for (int kp = k; kp <= l; ++kp)
      for (int lp = l; lp <= m; ++lp)
        if (x + lp - kp + 1 <= nb) {
          max(line + 1, x + lp - kp + 1, kp, lp, 1, 0, line, x, k, l, 1, 0, 
                     d[line][x][k][l][1][0] + s[line][lp] - s[line][kp - 1]);
          max(line + 1, x + lp - kp + 1, kp, lp, 1, 1, line, x, k, l, 1, 0, 
                     d[line][x][k][l][1][0] + s[line][lp] - s[line][kp - 1]);
        }
    return;
  }

  for (int kp = k; kp <= l; ++kp)
    for (int lp = l; lp >= kp; --lp)
      if (x + lp - kp + 1 <= nb)
        max(line + 1, x + lp - kp + 1, kp, lp, 1, 1, line, x, k, l, 1, 1, 
                   d[line][x][k][l][1][1] + s[line][lp] - s[line][kp - 1]);
}

// d[i][j][k][l][0/1][0/1] = at the ith line, j territories already taken 
// and on the (i - 1)th line the sequence was between k and l
void solve() {
  for (int i = 1; i <= n; ++i) {
    for (int k = 1; k <= m; ++k)
      for (int l = k; l <= m; ++l)
        for (int x1 = 0; x1 <= 1; ++x1)
          for (int x2 = 0; x2 <= 1; ++x2)
            if (l - k + 1 <= nb)
              max(i + 1, l - k + 1, k, l, x1, x2, 0, 0, 0, 0, 0, 0,
                                              s[i][l] - s[i][k - 1]); 
    for (int j = 0; j <= nb; ++j)
      for (int k = 1; k <= m; ++k)
        for (int l = k; l <= m; ++l)
          for (int x1 = 0; x1 <= 1; ++x1)
            for (int x2 = 0; x2 <= 1; ++x2) 
              if (d[i][j][k][l][x1][x2])
                solve(i, j, k, l, x1, x2);
  }
}

void remake(elem a) {
  if (a.i == 0)
    return;

  remake(pred[a.i][a.j][a.k][a.l][a.x1][a.x2]);

  for (int j = a.k; j <= a.l; ++j)
    printf("%d %d\n", a.i - 1, j);
}

void afis() {
  int rez = 0;
  elem adr;

  for (int i = 1; i <= n + 1; ++i)
    for (int k = 1; k <= m; ++k)
      for (int l = k; l <= m; ++l)
        for (int x1 = 0; x1 <= 1; ++x1)
          for (int x2 = 0; x2 <= 1; ++x2)
            if (d[i][nb][k][l][x1][x2] > rez) {
              rez = d[i][nb][k][l][x1][x2];
              adr.i = i;
              adr.j = nb;
              adr.k = k;
              adr.l = l;
              adr.x1 = x1;
              adr.x2 = x2;
            }

  printf("Oil:%d\n", rez);
  
  remake(adr);
}

int main() {
  read();

  init();

  solve();

  afis();

  return 0;
}
