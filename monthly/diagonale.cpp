#include <cstdio>

const int N = 1005;

int n, a[N][N];

void read() {
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      scanf("%d", &a[i][j]);
}

void solve() {
  long long sol = (long long)N * 1000000000 * (-1);
  
  int i, j, auxi, auxj;

  for (auxi = 1; auxi <= n; ++auxi) {
    // dp
    i = auxi;
    j = 1;
    
    long long sc = 0;

    while (i <= n && j <= n) {
      sc += (long long)a[i][j];
      ++i;
      ++j;
    }

    if (sc > sol)
      sol = sc;
    
    // ds
    i = auxi;
    j = n;

    sc = 0;

    while (i <= n && j > 0) {
      sc += (long long)a[i][j];
      ++i;
      --j;
    }

    if (sc > sol)
      sol = sc;
  }

  for (auxj = 1; auxj <= n; ++auxj) {
    //dp
    i = 1;
    j = auxj;

    long long sc = 0;

    while (i <= n && j <= n) {
      sc += (long long)a[i][j];
      ++i;
      ++j;
    }

    if (sc > sol)
      sol = sc;
  
    //ds
    i = 1;
    j = auxj;

    sc = 0;

    while (i <= n && j > 0) {
      sc += (long long)a[i][j];
      ++i;
      --j;
    }

    if (sc > sol)
      sol = sc;
  }

  printf("%lld\n", sol);
}

int main() {
  freopen("diagonale.in", "r", stdin);
  freopen("diagonale.out", "w", stdout);

  read();

  solve();

  return 0;
}
