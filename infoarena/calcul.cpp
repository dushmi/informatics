#include <cstdio>
#include <cstring>
#include <cassert>

const int N = 100005;

char a[N], b[N];

int c, lp;

long long A, mod;

bool p[4 * N];

void read() {
  assert(scanf("%s", a));
  assert(scanf("%s", b));
  assert(scanf("%d", &c));
}

inline int max(int x, int y) {
  return x < y ? y : x;
}

void init() {
  mod = 1;

  for (int i = 1; i <= c; ++i)
    mod *= (long long)10;

  int n = strlen(a) - 1;

  for (int i = max(n - 8, 0); i <= n; ++i)
    A = A * 10 + a[i] - '0';
  
  A %= mod;
  
  n = strlen(b) - 1;

  for (int i = n; i >= 0; --i) {
    int x;

    if (b[i] >= 'A')
      x = b[i] - 'A' + 10;
    else
      x = b[i] - '0';
  
    p[++lp] = x & 1;
    p[++lp] = x & 2;
    p[++lp] = x & 4;
    p[++lp] = x & 8;
  }
}

void inm(long long r[2][2], long long a[2][2], long long b[2][2]) {
  long long c[2][2];

  for (int i = 0; i <= 1; ++i)
    for (int k = 0; k <= 1; ++k) {
      c[i][k] = 0;
      for (int j = 0; j <= 1; ++j)
        c[i][k] = (c[i][k] + (a[i][j] * b[j][k]) % mod) % mod;
    }
  
  for (int i = 0; i <= 1; ++i)
    for (int j = 0; j <= 1; ++j)
      r[i][j] = c[i][j];
}

void solve() {
  long long rez[2][2], mat[2][2];

  rez[0][0] = 1; rez[0][1] = 0;
  rez[1][0] = 0; rez[1][1] = 1;

  mat[0][0] = A; mat[0][1] = 0;
  mat[1][0] = 1; mat[1][1] = 1;

  for (int i = 1; i <= lp; ++i) {
    if (p[i]) 
      inm(rez, rez, mat);
    inm(mat, mat, mat);
  }

  long long sol = (rez[0][0] + rez[1][0] - 1) % mod;

  if (sol < 0)
    sol += mod;
  
  long long aux = sol;

  if (!aux)
    aux = 1;

  while (aux * 10 < mod) {
    aux *= 10;
    printf("0");
  }

  printf("%lld\n", sol);
}

int main() {
  assert(freopen("calcul.in", "r", stdin));
  assert(freopen("calcul.out", "w", stdout));

  read();
 
  init();

  solve();

  return 0;
}
