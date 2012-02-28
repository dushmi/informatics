#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>

using namespace std;

const int N = 2005, K = 17, INF = 0x3f3f3f3f;

int n, k, tar[K], dist[K][K], din[1 << K][K];

vector <pair <int, int> > L[N];

void read() {
  int m, x, y, c;

  assert(scanf("%d%d", &n, &m));

  assert(scanf("%d", &k));

  for (int i = 1; i <= k; ++i)
    assert(scanf("%d", &tar[i]));

  for (int i = 1; i <= m; ++i) {
    assert(scanf("%d%d%d", &x, &y, &c));
    L[x].push_back(make_pair(y, c));
    L[y].push_back(make_pair(x, c));
  }
}

void dijkstra(int st, int v[K]) {
  int d[N];

  bool proc[N];

  for (int i = 1; i < N; ++i)
    d[i] = INF, proc[i] = 0;

  d[st] = 0;

  priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > H;

  H.push(make_pair(0, st));

  int nc, dc;

  while (!H.empty()) {
    nc = H.top().second;
    dc = H.top().first;
    H.pop();

    if (proc[nc])
      continue;

    proc[nc] = 1;
    d[nc] = dc;

    for (int i = 0; i < (int)L[nc].size(); ++i)
      if (!proc[L[nc][i].first])
        H.push(make_pair(d[nc] + L[nc][i].second, L[nc][i].first));
  }

  for (int i = 0; i <= k + 1; ++i)
    v[i] = d[tar[i]];
}

void init() {
  tar[0] = 1;
  tar[k + 1] = n;

  for (int i = 0; i <= k + 1; ++i)
    dijkstra(tar[i], dist[i]);
}

inline int min(int x, int y) {
  return x < y ? x : y;
}

void solve() {
  din[0][0] = 1;

  for (int i = 0; i < (1 << k); ++i)
    for (int j = 0; j <= k; ++j)
      if (din[i][j])
        for (int aux = 1; aux <= k; ++aux)
          if (!(i & (1 << (aux - 1))) && (din[i + (1 << (aux - 1))][aux] == 0 || din[i + (1 << (aux - 1))][aux] > din[i][j] + dist[j][aux]))
              din[i + (1 << (aux - 1))][aux] = din[i][j] + dist[j][aux];

  int rez = INF;

  for (int j = 1; j <= k; ++j)
    if (din[(1 << k) - 1][j])
      rez = min(rez, din[(1 << k) - 1][j] + dist[j][k + 1]);

  if (k == 0)
    rez = min(rez, din[(1 << k) - 1][0] + dist[0][k + 1]);

  printf("%d\n", rez - 1);
}

int main() {
  assert(freopen("ubuntzei.in", "r", stdin));
  assert(freopen("ubuntzei.out", "w", stdout));

  read();

  init();

  solve();

  return 0;
}
