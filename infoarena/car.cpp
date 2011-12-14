//Test graf
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct pct {
  short int x, y, d;
};

const short int N = 505, D = 8;

short int n, m, sx, sy, fx, fy, dist[N][N][D];

short int dx[D] = {-1,-1, 0, 1, 1, 1, 0,-1};
short int dy[D] = { 0, 1, 1, 1, 0,-1,-1,-1};

bool a[N][N];

void read() {
  char s[2 * N];

  scanf("%hd%hd\n", &n, &m);
  scanf("%hd%hd%hd%hd\n", &sx, &sy, &fx, &fy);

  for (short int i = 1; i <= n; ++i) {
    fgets(s, 2 * N, stdin);
    for (short int j = 1; j <= m; ++j)
      a[i][j] = s[2 * (j - 1)] - '0';
  }
}

pct node(short int x, short int y, short int d) {
  pct r;
  
  r.x = x;
  r.y = y;
  r.d = d;

  return r;
}

void bordeaza() {
  for (short int i = 0; i <= n + 1; ++i)
    a[i][0] = a[i][m + 1] = 1;
  
  for (short int j = 0; j <= m + 1; ++j)
    a[0][j] = a[n + 1][j] = 1;
}

inline short int mod8(short int x) {
  if (x >= 8)
    return x - 8;

  return x;
}

queue <pct> Q[2];

void solve() {
  pct nc, nn;

  for (short int i = 1; i <= n; ++i)
    for (short int j = 1; j <= m; ++j)
      for (short int d = 0; d <= 7; ++d)
        dist[i][j][d] = 32000;

  for (short int d = 0; d <= 7; ++d) {
    Q[0].push(node(sx, sy, d));
    dist[sx][sy][d] = 0;
  }

  bool p = 1;

  while (Q[0].size() + Q[1].size() > 0) {  
    p = 1 - p;

    while (!Q[p].empty()) {
      nc = Q[p].front();
      Q[p].pop();

      if (nc.x == fx && nc.y == fy) {
        printf("%hd\n", dist[nc.x][nc.y][nc.d]);
        return;
      }

      //next
      nn.x = nc.x;
      nn.y = nc.y;
      nn.d = mod8(nc.d + 1);
      if (dist[nn.x][nn.y][nn.d] > dist[nc.x][nc.y][nc.d] + 1) {
        dist[nn.x][nn.y][nn.d] = dist[nc.x][nc.y][nc.d] + 1;
        Q[1 - p].push(nn);
      }

      //previous
      nn.x = nc.x;
      nn.y = nc.y;
      nn.d = mod8(nc.d - 1 + 8);
      if (dist[nn.x][nn.y][nn.d] > dist[nc.x][nc.y][nc.d] + 1) {
        dist[nn.x][nn.y][nn.d] = dist[nc.x][nc.y][nc.d] + 1;
        Q[1 - p].push(nn);
      }

      //miscare
      nn.x = nc.x + dx[nc.d];
      nn.y = nc.y + dy[nc.d];
      nn.d = nc.d;
      if (!a[nn.x][nn.y] && dist[nn.x][nn.y][nn.d] > dist[nc.x][nc.y][nc.d]) {
        dist[nn.x][nn.y][nn.d] = dist[nc.x][nc.y][nc.d]; 
        Q[p].push(nn);
      }
    }
  }

  printf("-1\n");
}

int main() {
  freopen("car.in", "r", stdin);
  freopen("car.out", "w", stdout);

  read();

  bordeaza();

  solve();

  return 0;
} 
