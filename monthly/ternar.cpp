#include <cstdio>
#include <cassert>
#include <queue>

using namespace std;

const int N = 1300, INF = 0x3f3f3f3f;

int maxx, maxy, minx, miny, nrp, n, m, a[N][N];

bool ok, f[N][N];

queue <pair <int, int> > Q;

int dx[] = {  0,  0,  1,  1,  1, -1, -1, -1};
int dy[] = { -1,  1, -1,  0,  1, -1,  0,  1};

inline int min(int x, int y) {
  return x < y ? x : y;
}

inline int max(int x, int y) {
  return x > y ? x : y;
}

void read() {
  assert(scanf("%d%d", &n, &m));
  assert(1 <= n && n <= 1234);
  assert(1 <= m && m <= 1234);

  for (int i = 1; i <= n; ++i) 
    for (int j = 1; j <= m; ++j) {
      assert(scanf("%d", &a[i][j]));
      assert(0 <= a[i][j] && a[i][j] <= 2);
    }
}

void bfs(int x, int y) {
  int i, j;
  
  Q.push(make_pair(x, y));
  f[x][y] = 1;
  nrp = 1;
  
  while (!Q.empty()) {
    i = Q.front().first;
    j = Q.front().second;
    Q.pop();

    minx = min(minx, i); miny = min(miny, j);
    maxx = max(maxx, i); maxy = max(maxy, j);

    for (int k = 0; k < 8; ++k)
      if (a[i + dx[k]][j + dy[k]] == 2 && !f[i + dx[k]][j + dy[k]]) {
        Q.push(make_pair(i + dx[k], j + dy[k]));
        f[i + dx[k]][j + dy[k]] = 1;
        ++nrp;
      } else if (a[i + dx[k]][j + dy[k]] == 0)
        ok = 0;
  }
}

void solve() {
  int rez = -1;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (a[i][j] == 2 && !f[i][j]) {
        nrp = 0;
        ok = 1;
        minx = maxx = i;
        miny = maxy = j;
        bfs(i, j);
        
        if ((maxx - minx + 1) * (maxy - miny + 1) == nrp && ok && (maxx - minx + 3) * (maxy - miny + 3) > rez)
          rez = (maxx - minx + 3) * (maxy - miny + 3);
      } 
  
  printf("%d", rez);
}

int main() {
  assert(freopen("ternar.in", "r", stdin));
  assert(freopen("ternar.out", "w", stdout));

  read();
  
  solve();

  return 0;
}

