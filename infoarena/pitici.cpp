#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int Nmax = 1030;

priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > H;

vector <pair <int, int> > next[Nmax], prev[Nmax];

queue <int> Q;

vector <int> dist[Nmax];

int n, k, deg[Nmax];

void read() {
  int m, x, y, c;

  scanf("%d%d%d", &n, &m, &k);

  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &x, &y, &c);
    
    next[x].push_back(make_pair(y, c));
    prev[y].push_back(make_pair(x, c));
    deg[y]++;
  }
}

void solve() {
  dist[1].push_back(0);
  Q.push(1);

  while (!Q.empty()) {
    int nod = Q.front(); Q.pop();

    for (int i = 0; i < (int)next[nod].size(); ++i) {
      --deg[next[nod][i].first];

      if (!deg[next[nod][i].first])
        Q.push(next[nod][i].first);
    }
    
    while(!H.empty())
      H.pop();

    for (int i = 0; i < (int)prev[nod].size(); ++i)
      H.push(make_pair(dist[prev[nod][i].first][0] + prev[nod][i].second, (prev[nod][i].first << 11)));
    
    while (!H.empty() && (int)dist[nod].size() < k) {
      int nc = H.top().first, ind = (H.top().second >> 11), ord = (H.top().second & ((1 << 11) - 1)); H.pop();
      
      dist[nod].push_back(nc);

      if (ord + 1 < (int)dist[ind].size())
        H.push(make_pair(nc - dist[ind][ord] + dist[ind][ord + 1], (ind << 11) + ord + 1));
    }
  }
}

void print() {
  for (int j = 0; j < k; ++j)
    printf("%d ", dist[n][j]);
}

int main() {
  freopen("pitici.in", "r", stdin);
  freopen("pitici.out", "w", stdout);

  read();

  solve();

  print();

  return 0;
}
