#include <cstdio>
#include <vector>

using namespace std;

struct Square {
  int x, y, lat;

  Square(int _x, int _y, int _lat) {
    x = _x; y = _y; lat = _lat;
  }
};

const int N = 1025;

int k, a[N][N];

vector <Square> v;

void read() {
  int n, x, y;

  scanf("%d%d", &n, &k);

  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &x, &y);
    ++a[x][y];
  }
}

void init() {
  for (int i = 1; i < N; ++i)
    for (int j = 1; j < N; ++j)
      a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
}

void solve(int x, int y, int lat) {
  int pct = a[x + lat - 1][y + lat - 1] - a[x - 1][y + lat - 1] - a[x + lat - 1][y - 1] + a[x - 1][y - 1];
  
  if (!pct || !lat)
    return;

  if (pct * k < lat * lat) {
    solve(x, y, lat >> 1);
    solve(x + (lat >> 1), y, lat >> 1);
    solve(x, y + (lat >> 1), lat >> 1);
    solve(x + (lat >> 1), y + (lat >> 1), lat >> 1);
    return;
  }
  
  v.push_back(Square(x, y, lat));
}

void afis() {
  printf("%d\n", (int)v.size());

  for (int i = 0; i < (int)v.size(); ++i)
    printf("%d %d %d\n", v[i].x, v[i].y, v[i].lat);
}

int main() {
  freopen("patrate4.in", "r", stdin);
  freopen("patrate4.out", "w", stdout);

  read();

  init();

  solve(1, 1, N - 1);

  afis();

  return 0;
}
