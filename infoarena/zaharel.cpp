#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

const int N = 1005;

int n, st, link[2 * N], d[2 * N];

vector <pair <int, int> > v[2];

bool f[2 * N];

void read() {
  int m, x, y;

  char c;

  assert(scanf("%d%d", &n, &m));

  for (int i = 1; i <= m; ++i) {
    assert(scanf("%d %d %c", &x, &y, &c));

    if (c == 'R' && !link[x])  
      link[x] = n + y;

    if (c == 'A' && !link[n + y])
      link[n + y] = x;
  }
}

void solve(int nod) {
  f[nod] = 1;

  if (f[link[nod]]) {
    st = link[nod];
    printf("%d\n", (d[nod] - d[link[nod]] + 1) / 2);
    return;
  }

  d[link[nod]] = d[nod] + 1;
  solve(link[nod]);
}

void gen(int nod) {
  f[nod] = 1;

  if (nod <= n)
    v[0].push_back(make_pair(nod, link[nod] - n));
  else
    v[1].push_back(make_pair(link[nod], nod - n));

  if (f[link[nod]])
    return;

  gen(link[nod]);
}

int main() {
  assert(freopen("zaharel.in", "r", stdin));
  assert(freopen("zaharel.out", "w", stdout));

  read();

  solve(1);

  for (int i = 1; i <= 2 * n; ++i)
    f[i] = 0;
  
  gen(st);

  for (int i = 0; i <= 1; ++i, printf("\n")) 
    for (int j = 0; j < (int)v[i].size(); ++j)
      printf("%d %d ", v[i][j].first, v[i][j].second);

  return 0;
}
