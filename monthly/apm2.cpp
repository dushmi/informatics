#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

struct muchie {
  int x, y, cost;
};

const int INF = 0x3f3f3f3f, M = 100005, N = 10005;

muchie vi[M], v[N];

int n, m, q, dad[N];

void read() {
  assert(scanf("%d%d%d", &n, &m, &q));
  
  for (int i = 1; i <= m; ++i)
    assert(scanf("%d%d%d", &vi[i].x, &vi[i].y, &vi[i].cost));
}

bool comp(muchie a, muchie b) {
  return a.cost < b.cost;
}

int compress(int nod) {
  if (dad[nod] == 0)
    return nod;

  return (dad[nod] = compress(dad[nod]));
}

void init() {
  int rx, ry, l = 0;

  for (int i = 1; i <= n; ++i) 
    dad[i] = 0;

  for (int i = 1; i <= m; ++i) {
    rx = compress(vi[i].x);
    ry = compress(vi[i].y);

    if (rx != ry) {
      dad[rx] = ry;
      v[++l] = vi[i];
    }
  }
}

int query(int x, int y) {
  int rx, ry;
  
  for (int i = 1; i <= n; ++i)
    dad[i] = 0;

  for (int i = 1; i <= n; ++i) {
    rx = compress(v[i].x);
    ry = compress(v[i].y);

    dad[rx] = ry;
    
    if (compress(x) == compress(y))
      return v[i].cost - 1;
  }

  return INF;
}

void solve() {
  int x, y;

  for (int i = 1; i <= q; ++i) {
    assert(scanf("%d%d", &x, &y));
    printf("%d\n", query(x, y));
  }
}

int main() {
  assert(freopen("apm2.in", "r", stdin));
  assert(freopen("apm2.out", "w", stdout));

  read();
  
  sort(vi + 1, vi + m + 1, comp);

  init();

  solve();

  return 0;
}
