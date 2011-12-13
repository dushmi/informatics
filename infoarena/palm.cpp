#include <cstdio>
#include <cstring>

using namespace std;

const int N = 505, A = 30;

char s[N];

int n, d[N][N][A];

inline int max(int x, int y) {
  return x > y ? x : y;
}

int solve() {
  n = strlen(s + 1);

  for (int i = n; i >= 1; --i) {
    d[i][i][s[i] - 'a'] = 1;
    
    for (int k = 24; k >= 0; --k)
      d[i][i][k] = max(d[i][i][k], d[i][i][k + 1]);
    
    for (int j = i + 1; j <= n; ++j) {
      for (int k = 0; k < 26; ++k) {
        d[i][j][k] = max(d[i][j - 1][k], d[i + 1][j][k]);

        if (s[i] == s[j] && s[i] - 'a' == k)
          d[i][j][k] = (d[i + 1][j - 1][k] + 2);
      }

      for (int k = 24; k >= 0; --k)
        d[i][j][k] = max(d[i][j][k], d[i][j][k + 1]);
    }
  }

  return d[1][n][0];
}


int main() {
  freopen("palm.in", "r", stdin);
  freopen("palm.out", "w", stdout);

  gets(s + 1);

  printf("%d", solve());

  return 0;
}
