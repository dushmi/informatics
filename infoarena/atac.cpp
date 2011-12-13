#include <cstdio>
#include <vector>

using namespace std;

const int N = 32005, logN = 18, INF = 2000000000;

int n, m, p, X, Y, A, B, C, D, lvl[N], dad[N], cdad[N], d[N][logN], rez[N][logN];

vector< pair <int, int> > L[N];

bool f[N];

void read() {
  int x, d;

  scanf("%d%d%d", &n, &m, &p);

  for (int i = 2; i <= n; ++i) {
    scanf("%d%d", &x, &d);
    L[x].push_back(make_pair(i, d));
    L[i].push_back(make_pair(x, d));
  }

  scanf("%d%d%d%d%d%d", &X, &Y, &A, &B, &C, &D);
}

void init(int node) {
  f[node] = 1;

  for (int i = 0; i < (int)L[node].size(); ++i)
    if (!f[L[node][i].first]) {
      dad[L[node][i].first] = node;
      cdad[L[node][i].first] = L[node][i].second;
      lvl[L[node][i].first] = lvl[node] + 1;
      init(L[node][i].first);
    }
}

void reset() {
  for (int i = 1; i <= n; ++i)
    f[i] = 0;
}

void din(int node) {
  f[node] = 1;

  d[node][0] = dad[node];
  rez[node][0] = cdad[node];

  for (int j = 1; j <= 16; ++j) {
    d[node][j] = d[d[node][j - 1]][j - 1];
    rez[node][j] = min(rez[node][j - 1], rez[d[node][j - 1]][j - 1]);
  }

  for (int i = 0; i < (int)L[node].size(); ++i)
    if (!f[L[node][i].first]) 
      din(L[node][i].first);
}

int solution(int x, int y) {
  if (lvl[x] < lvl[y])
    swap(x, y);
  
  int sol = INF;

  for (int i = 16; i >= 0; --i)
    if (d[x][i] && lvl[d[x][i]] >= lvl[y]) {
      sol = min(sol, rez[x][i]);
      x = d[x][i];
    }
  
  if (x == y)
    return sol;

  for (int i = 16; i >= 0; --i)
    if (d[x][i] && d[y][i] && d[x][i] != d[y][i]) {
      sol = min(sol, rez[x][i]);
      x = d[x][i];
      sol = min(sol, rez[y][i]);
      y = d[y][i];
    }

  sol = min(sol, cdad[x]);
  sol = min(sol, cdad[y]);

  return sol;
}

void solve() {
  int auxX, auxY;
  
  for (int i = 1; i <= m; ++i) {
    int sol = solution(X, Y);

    if (X == Y)
      sol = 0;
    
    if (i >= m - p + 1)
      printf("%d\n", sol);
  
    auxX = X; auxY = Y;

    X = (auxX * A + auxY * B) % n + 1;
    Y = (auxY * C + sol * D) % n + 1;
  }
}

int main() {
  freopen("atac.in", "r", stdin);
  freopen("atac.out", "w", stdout);

  read();
  
  cdad[1] = INF;

  init(1);

  reset();

  din(1);

  solve();

  return 0;
}
