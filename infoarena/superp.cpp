#include <cstdio>
#include <queue>
#include <cassert>

using namespace std;

const int N = 20;

struct elem {
  long long val;
  int f[10];
};

int n, f[10];

long long rc;

queue <elem> Q;

inline int min(int x, int y) {
  return x < y ? x : y;
}

bool prim(long long x) {
  for (int i = 2; (long long)i * i <= x; ++i)
    if (x % i == 0)
      return 0;

  return 1;
}

void init(long long x) {
  for (int i = 0; i <= 9; ++i)
    f[i] = 0;

  while (x) {
    ++f[x % 10];
    x /= 10;
  }

  rc = 0;

  elem newn;

  for (int i = 0; i <= 9; ++i)
    newn.f[i] = 0;

  for (int i = 2; i <= 9; ++i)
    if (f[i] && prim(i)) {
      newn.val = i;
      ++newn.f[i];
      Q.push(newn);
      --newn.f[i];
      if (i > rc)
        rc = i;
    }
}

void bfs() {
  elem nc;

  while (!Q.empty()) {
    nc = Q.front();
    Q.pop();

    for (int i = 1; i <= 9; ++i)
      if (i % 2 != 0 && i % 5 != 0 && nc.f[i] < f[i] && prim(nc.val * 10 + i)) {
        if (nc.val * 10 + i > rc)
          rc = nc.val * 10 + i;
        nc.val = nc.val * 10 + i;
        ++nc.f[i];
        Q.push(nc);
        --nc.f[i];
        nc.val = (nc.val - i) / 10;
      }
  }

  printf("%lld\n", rc);
}

int main() {
  assert(freopen("superp.in", "r", stdin));
  assert(freopen("superp.out", "w", stdout));

  long long a;

  assert(scanf("%d", &n));

  for (int i = 1; i <= n; ++i) {
    assert(scanf("%lld", &a));

    init(a);

    bfs();
  }

  return 0;
}
