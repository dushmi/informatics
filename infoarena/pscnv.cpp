#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

const int N = 250005, K = 1005;

vector <pair <int, int> > L[N];

queue <int> Q[K];

int n, S, D, d[N];

char s[30];

bool cif(char ch) {
  return '0' <= ch && ch <= '9';
}

void read() {
  int m, x, y, p, poz;

  scanf("%d%d%d%d\n", &n, &m, &S, &D);

  for (int i = 1; i <= m; ++i) {
    fgets(s, 30, stdin);

    x = y = p = poz = 0;

    while (cif(s[poz]))
      x = x * 10 + s[poz] - '0', ++poz;
    
    ++poz;

    while (cif(s[poz]))
      y = y * 10 + s[poz] - '0', ++poz;

    ++poz;
    
    while (cif(s[poz]))
      p = p * 10 + s[poz] - '0', ++poz;

    L[x].push_back(make_pair(y, p));
  }
}

inline int maxim(int x, int y) {
  return x > y ?  x : y;
}

void dijkstra() {
  int nc, cc;

  for (int i = 1; i <= n; ++i)
    d[i] = K;

  Q[0].push(S);
  d[S] = 0;
  
  for (int c = 0; c <= K - 5 && d[D] > c; ++c)
    while (!Q[c].empty()) {
      nc = Q[c].front();
      Q[c].pop();

      if (d[nc] != c)
        continue;

      for (int j = 0; j < (int)L[nc].size(); ++j) {
        cc = maxim(d[nc], L[nc][j].second);

        if (d[L[nc][j].first] > cc) {
          d[L[nc][j].first] = cc;
          Q[cc].push(L[nc][j].first);
        }
      }
    }

  printf("%d\n", d[D]);
}

int main() {
  freopen("pscnv.in", "r", stdin);
  freopen("pscnv.out", "w", stdout);

  read();

  dijkstra();

  return 0;
}

