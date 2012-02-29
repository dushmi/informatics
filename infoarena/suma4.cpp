#include <cstdio>
#include <cassert>

const int N = 63370, NRN = 70, INF = 0x3f3f3f3f;

int nrn, n, c[N], ind[NRN][NRN][NRN], mat[NRN][NRN][NRN];

int dx[] = { -1, -1,  0, 0};
int dy[] = { -1,  0, -1, 0};

void read() {
  assert(scanf("%d", &n));

  for (int i = 1; i <= n; ++i)
    assert(scanf("%d", &c[i]));
}

void solve_a() {
  int sc = 0;

  for (nrn = 1; sc + nrn * nrn <= n; ++nrn)
    sc += nrn * nrn;

  --nrn;

  printf("%d ", nrn);
}

void init() {
  int t = 0;

  for (int niv = 1; niv <= nrn; ++niv)
    for (int i = 1; i <= niv; ++i)
      for (int j = 1; j <= niv; ++j)
        ind[niv][i][j] = ++t;
}

inline int min(int x, int y) {
  return x < y ? x : y;
}

void afis(int niv, int i, int j) {
  if (niv == 0)
    return;
  
  int newi = 0, newj = 0;
  for (int d = 0; d < 4; ++d) {
    newi = i + dx[d];
    newj = j + dy[d];

    if (newi > 0 && newi < niv && newj > 0 && newj < niv && mat[niv][i][j] - mat[niv - 1][newi][newj] == c[ind[niv][i][j]]) {
      afis(niv - 1, newi, newj);
      break;
    }
  }

  printf("%d ", ind[niv][i][j]);
}

void solve_b() {
  mat[1][1][1] = c[1];

  for (int niv = 1; niv < nrn; ++niv) {
    for (int i = 1; i <= niv + 1; ++i)
      for (int j = 1; j <= niv + 1; ++j)
        mat[niv + 1][i][j] = INF;

    for (int i = 1; i <= niv; ++i)
      for (int j = 1; j <= niv; ++j) {
        mat[niv + 1][i][j] = min(mat[niv + 1][i][j], mat[niv][i][j] + c[ind[niv + 1][i][j]]);
        mat[niv + 1][i + 1][j] = min(mat[niv + 1][i + 1][j], mat[niv][i][j] + c[ind[niv + 1][i + 1][j]]);
        mat[niv + 1][i][j + 1] = min(mat[niv + 1][i][j + 1], mat[niv][i][j] + c[ind[niv + 1][i][j + 1]]);
        mat[niv + 1][i + 1][j + 1] = min(mat[niv + 1][i + 1][j + 1], mat[niv][i][j] + c[ind[niv + 1][i + 1][j + 1]]);
      }
  }

  int rez = INF, linr = 0, colr = 0;

  for (int i = 1; i <= nrn; ++i)
    for (int j = 1; j <= nrn; ++j)
      if (mat[nrn][i][j] < rez) {
        rez = mat[nrn][i][j];
        linr = i;
        colr = j;
      }
  
  printf("%d\n", rez); 

  afis(nrn, linr, colr);
}

int main() {
  assert(freopen("suma4.in", "r", stdin));
  assert(freopen("suma4.out", "w", stdout));

  read();

  solve_a();

  init();

  solve_b();

  return 0;
}
