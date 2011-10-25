#include <cstdio>

const int N = 255, M = 2005, K = 31;

int n, m, nrb[1 << 16], a[N][M / K + 1];

void read() {
  char s[2 * M];

  scanf("%d%d\n", &n, &m);

  for (int i = 1; i <= n; ++i) {
    fgets(s, 2 * M, stdin);

    for (int j = 0; j < m; ++j)
      if (s[2 * j] - '0' == 1) 
        a[i][j / 31] += (1 << (j % 31));
  }

  m = (m - 1) / 31;
}

void pregen() {
  for (int i = 1; i < (1 << 16); ++i)
    if (i & 1)
      nrb[i] = nrb[i >> 1] + 1;
    else
      nrb[i] = nrb[i >> 1];
}

void solve() {
  int nrp, rez[M / K  + 1]; //nrp = numar potriviri intre liniile l1 si l2
  
  long long sol = 0;

  for (int l1 = 1; l1 <= n; ++l1)
    for (int l2 = l1 + 1; l2 <= n; ++l2) {
      for (int j = 0; j <= m; ++j)
        rez[j] = a[l1][j] & a[l2][j];
      
      nrp = 0;

      for (int j = 0; j <= m; ++j)
        nrp += nrb[(rez[j] & ((1 << 16) - 1))] + nrb[(rez[j] >> 16)];
      
      sol += (long long)nrp * (nrp - 1) / 2;
    }

  printf("%lld\n", sol);
}

int main() {
  freopen("fold.in", "r", stdin);
  freopen("fold.out", "w", stdout);

  read();

  pregen();

  solve();

  return 0;
}
