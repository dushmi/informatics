#include <cstdio>
#include <cstring>

const int N = 19, M = 30005;

char s[N][M];

int n, st, pi[M], len[N], much[N][N], pred[(1 << N)][N], d[(1 << N)][N];

const int INF = 0x3f3f3f3f;

void read() {
  scanf("%d\n", &n);

  for (int i = 1; i <= n; ++i)
    scanf("%s\n", s[i] + 1);
}

void prefix(int ind) {
  int q = 0;

  pi[1] = q;

  for (int i = 2; i <= len[ind]; ++i) {
    while (q && s[ind][i] != s[ind][q + 1])
      q = pi[q];

    if (s[ind][i] == s[ind][q + 1])
      ++q;

    pi[i] = q;
  }
}

int kmp(int i1, int i2) {
  int q = 0;

  for (int i = 1; i <= len[i1]; ++i) {
    while (q && s[i1][i] != s[i2][q + 1])
      q = pi[q];

    if (s[i1][i] == s[i2][q + 1])
      ++q;
    
    if (q == len[i2] && i < len[i1]) {
      st = st | (1 << (i2 - 1));
      q = 0;
      break;
    }
  }

  return q;
}

void init() {
  for (int i = 1; i <= n; ++i)
    len[i] = strlen(s[i] + 1);

  for (int j = 1; j <= n; ++j) {
    prefix(j);
    for (int i = 1; i <= n; ++i)
      if (j != i)
        much[i][j] = kmp(i, j);
  }
}

void afis(int i, int j) {
  if (i == st)
    return;

  afis(i - (1 << (j - 1)), pred[i][j]);

  for (int p = much[pred[i][j]][j] + 1; p <= len[j]; ++p)
    printf("%c", s[j][p]);
}

void solve() {
  for (int i = 0; i < (1 << n); ++i)
    for (int j = 0; j <= n; ++j)
      d[i][j] = INF;

  d[st][0] = 0;

  for (int i = 0; i < (1 << n); ++i)
    for (int j = 0; j <= n; ++j)
      if (d[i][j] != INF)
        for (int k = 1; k <= n; ++k)
          if (!(i & (1 << (k - 1))) && d[i + (1 << (k - 1))][k] > d[i][j] + len[k] - much[j][k]) {
              d[i + (1 << (k - 1))][k] = d[i][j] + len[k] - much[j][k];
              pred[i + (1 << (k - 1))][k] = j;
            }

  int rez = INF, prez;

  for (int j = 1; j <= n; ++j)
    if (rez > d[(1 << n) - 1][j])
      rez = d[(1 << n) - 1][j], prez = j;

  afis((1 << n) - 1, prez);
}

int main() {
  freopen("adn.in", "r", stdin);
  freopen("adn.out", "w", stdout);

  read();

  init();

  solve();

  return 0;
}
