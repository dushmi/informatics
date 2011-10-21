#include <cstdio>

const short int N = 1002, INF = 8100;

short int q, L, C, rez,  dqm[N], dqM[N], a[N][N], m[N][N], M[N][N], dm[N][N], dM[N][N];

int nrs;

inline bool cif(char ch) {
  return ('0' <= ch && ch <= '9');
}

void read() {
  short int poz;

  char s[5 * N];
  
  scanf("%hd%hd%hd\n", &L, &C, &q);
  
  for (short int i = 1; i <= L; ++i) { 
    fgets(s, 5 * N, stdin);

    poz = 0;

    for (int j = 1; j <= C; ++j) {
      while (cif(s[poz]))
        a[i][j] = a[i][j] * 10 + s[poz] - '0', ++poz;

      ++poz;
    }
  }
}

void solve(short int lin, short int col) {
  short int stm, drm, stM, drM;

  for (short int i = 1; i <= L; ++i) {
    stm = drm = 1, dqm[1] = 1, m[i][1] = a[i][1];
    stM = drM = 1, dqM[1] = 1, M[i][1] = a[i][1];

    for (short int j = 2; j <= C; ++j)  {
      if (j - dqm[stm] + 1 > col)
        ++stm;
      while (a[i][dqm[drm]] > a[i][j] && drm >= stm)
        --drm;
      dqm[++drm] = j;
      m[i][j] = a[i][dqm[stm]];

      if (j - dqM[stM] + 1 > col)
        ++stM;
      while (a[i][dqM[drM]] < a[i][j] && drM >= stM)
        --drM;
      dqM[++drM] = j;
      M[i][j] = a[i][dqM[stM]];
    }
  }

  for (short int j = 1; j <= C; ++j) {
    stm = drm = 1, dqm[1] = 1, dm[1][j] = m[1][j];
    stM = drM = 1, dqM[1] = 1, dM[1][j] = M[1][j];
    
    for (short int i = 2; i <= L; ++i) {
      if (i - dqm[stm] + 1 > lin)
        ++stm;
      while (m[dqm[drm]][j] > m[i][j] && drm >= stm)
        --drm;
      dqm[++drm] = i;
      dm[i][j] = m[dqm[stm]][j];

      if (i - dqM[stM] + 1 > lin)
        ++stM;
      while (M[dqM[drM]][j] < M[i][j] && drM >= stM)
        --drM;
      dqM[++drM] = i;
      dM[i][j] = M[dqM[stM]][j];
    }
  }

  for (short int i = lin; i <= L; ++i)
    for (short int j = col; j <= C; ++j) 
      if (dM[i][j] - dm[i][j] < rez)
        rez = dM[i][j] - dm[i][j], nrs = 1;
      else if (dM[i][j] - dm[i][j] == rez)
        ++nrs;
}

void solve() {
  short int x, y, poz;
  
  char s[15];

  for (int i = 1; i <= q; ++i) {
    x = y = poz = 0;

    fgets(s, 15, stdin);

    while (cif(s[poz]))
      x = x * 10 + s[poz] - '0', ++poz;

    ++poz;

    while (cif(s[poz]))
      y = y * 10 + s[poz] - '0', ++poz;
    
    rez = INF, nrs = 0;

    solve(x, y);
    
    if (x != y)
      solve(y, x);
  
    printf("%hd %d\n", rez, nrs);
  }
}

int main() {
  freopen("struti.in", "r", stdin);
  freopen("struti.out", "w", stdout);

  read();

  solve();

  return 0;
}


