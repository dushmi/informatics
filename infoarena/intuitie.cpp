#include <cstdio>

const int MOD = 999017, N = 505;

int n, p, q, SA[2][N][3][N], SB[2][N][3][N];

//A[i][j][ind][l] = nr de permutari de ordinul i cu j maxime, ultimul
//element egal cu l in care penultimul element este < l

//B[i][j][ind][l] = nr de permutari de ordinul i cu j maxime, ultimul
//element egal cu l in care penultimul element este > l

//ind = 0 => k = j - 1
//ind = 1 => k = j
//ind = 2 => k = j + 1

int modul(int x) {
  return x < 0 ? (-x) : x;
}

void solve() {
  short int x;

  SA[0][0][1][2] = 1;
  SB[0][0][1][1] = SB[0][0][1][2] = 1;
  
  for (short int i = 3; i <= n; ++i)
    for (short int j = 0; j <= p; ++j) {
      x = i & 1;

      SA[x][j][0][0] = SA[x][j][1][0] = SA[x][j][2][0] = 0;
      SB[x][j][0][0] = SB[x][j][1][0] = SB[x][j][2][0] = 0;

      for (short int l = 1; l <= i; ++l) {
        if (l != 1) {
          if (j >= 1)
            SA[x][j][0][l] = (SA[x][j][0][l - 1] + SA[1 - x][j][0][l - 1]) % MOD;

          SA[x][j][1][l] = (SA[x][j][1][l - 1] + SA[1 - x][j][1][l - 1] + (j >= 1 ? SB[1 - x][j][0][l - 1] : 0)) % MOD;

          SA[x][j][2][l] = (SA[x][j][2][l - 1] + SA[1 - x][j][2][l - 1] + SB[1 - x][j][1][l - 1]) % MOD;
        } else {
          SA[x][j][0][l] = 0;
          SA[x][j][1][l] = 0;
          SA[x][j][2][l] = 0;
        }
        
        if (l != i) {
          if (j >= 1)
            SB[x][j][0][l] = (SB[x][j][0][l - 1] + SA[1 - x][j - 1][1][i - 1] - SA[1 - x][j - 1][1][l - 1] +
                            SB[1 - x][j][0][i - 1] - SB[1 - x][j][0][l - 1] + 2 * MOD) % MOD;

          SB[x][j][1][l] = (SB[x][j][1][l - 1] + (j >= 1 ? (SA[1 - x][j - 1][2][i - 1] - SA[1 - x][j - 1][2][l - 1]) : 0) +
                           SB[1 - x][j][1][i - 1] - SB[1 - x][j][1][l - 1] + 2 * MOD) % MOD;
      
          SB[x][j][2][l] = (SB[x][j][2][l - 1] + SB[(i - 1) & 1][j][2][i - 1] - SB[(i - 1) & 1][j][2][l - 1] + MOD) % MOD;
        } else {
          SB[x][j][0][l] = SB[x][j][0][l - 1];
          SB[x][j][1][l] = SB[x][j][1][l - 1];
          SB[x][j][2][l] = SB[x][j][2][l - 1];
        }
      }
    }

  if (q == p - 1) {
    printf("%d\n", (SA[n & 1][p][0][n] + SB[n & 1][p][0][n]) % MOD);
    return;
  }

  if (q == p) {
    printf("%d\n", (SA[n & 1][p][1][n] + SB[n & 1][p][1][n]) % MOD);
    return;
  }

  printf("%d\n", (SA[n & 1][p][2][n] + SB[n & 1][p][2][n]) % MOD);
  
}

int main() {
  freopen("intuitie.in", "r", stdin);
  freopen("intuitie.out", "w", stdout);

  scanf("%d%d%d", &n, &p, &q);

  if (modul(p - q) > 1) {
    printf("0\n");
    return 0;
  }

  solve();

  return 0;
}
