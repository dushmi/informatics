#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int P = 55, N = 505, INF = 100 * 100 * 100 * 100;

int p, n, poz[P], dist[P][P], d[P][P][P];

vector <pair <int, int> > L[N];

priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > Q;

void read() {
  int m, x, y, c;

  scanf("%d%d%d", &p, &n, &m);

  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &x, &y, &c);
    L[x].push_back(make_pair(y, c));
    L[y].push_back(make_pair(x, c));
  }

  for (int i = 1; i <= p; ++i)
    scanf("%d", &poz[i]);
}

inline int min(int x, int y) {
  return x < y ? x : y;
}

void BF(int nod, int pc) {
  int d[N];

  bool used[N];

  memset(used, 0, sizeof(used));

  for (int i = 0; i < N; ++i)
    d[i] = INF;
  
  d[nod] = 0;
  
  for (int i = 1; i <= n; ++i) {
    int nc = 0;
    
    for (int j = 1; j <= n; ++j)
      if (!used[j] && d[j] < d[nc])
        nc = j;

    used[nc] = 1;

    for (int j = 0; j < (int)L[nc].size(); ++j)
      if (d[nc] + L[nc][j].second < d[L[nc][j].first])
        d[L[nc][j].first] = d[nc] + L[nc][j].second;
  }

  for (int i = 0; i <= p; ++i)
    dist[pc][i] = d[poz[i]];
}

void init() {
  poz[0] = 1;
  for (int i = 0; i <= p; ++i)
    BF(poz[i], i);
}

int solve(int l, int r, int nod) {
  if (l > r)
    return 0;

  if (d[l][r][nod] != INF)
    return d[l][r][nod];

  for (int i = l; i <= r; ++i)
    d[l][r][nod] = min(d[l][r][nod], solve(l, i - 1, i) + solve(i + 1, r, i) + dist[nod][i]);

  return d[l][r][nod];
}

int main() {
  freopen("team.in", "r", stdin);
  freopen("team.out", "w", stdout);

  read();

  init();

  for (int i = 0; i < P; ++i)
    for (int j = 0; j < P; ++j)
      for (int k = 0; k < P; ++k)
        d[i][j][k] = INF;

  printf("%d\n", solve(1, p, 0));

  return 0;
}

