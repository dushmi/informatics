#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

const int N = 16005, logN = 15;

int n, delay[N], ti[N], tf[N], dad[N], lvl[N], aib[N], p2[logN], elder[N][logN];

vector <int> v[N];

bool viz[N];

void read() {
  int a, b;
  
  assert(scanf("%d", &n));

  for (int i = 1; i <= n; ++i)
    assert(scanf("%d", &delay[i]));

  for (int i = 1; i < n; ++i) {
    assert(scanf("%d%d", &a, &b));
    v[a].push_back(b);
    v[b].push_back(a);
  }
}

int tc;

void df(int nod) {
  ++tc;
  ti[nod] = tc;

  for (int i = 0; i < (int)v[nod].size(); ++i)
    if (!viz[v[nod][i]]) {
      viz[v[nod][i]] = 1;
      df(v[nod][i]);
    }

  tf[nod] = tc;
}

void reset() {
  for (int i = 1; i <= n; ++i)
    viz[i] = 0;
}

inline int bit(int x) {
  return x & (-x);
}

void update(int val, int poz) {
  while (poz < N) {
    aib[poz] += val;
    poz += bit(poz);
  }
}

int query(int poz) {
  int rez = 0;

  while (poz) {
    rez += aib[poz];
    poz -= bit(poz);
  }

  return rez;
}

void stramosi(int nod) {
  elder[nod][0] = dad[nod];

  for (int i = 1; p2[i] <= lvl[nod]; ++i)
    elder[nod][i] = elder[elder[nod][i - 1]][i - 1];

  for (int i = 0; i < (int)v[nod].size(); ++i) 
    if (!viz[v[nod][i]]) {
      viz[v[nod][i]] = 1;
      dad[v[nod][i]] = nod;
      lvl[v[nod][i]] = lvl[nod] + 1;
      stramosi(v[nod][i]);
    }
}

void init() {
  viz[1] = 1;
  df(1);

  for (int i = 1; i <= n; ++i) {
    update(delay[i], ti[i]);
    update(-delay[i], tf[i] + 1);
  }

  p2[0] = 1;

  for (int i = 1; i < logN; ++i)
    p2[i] = (p2[i - 1] << 1);

  reset();

  lvl[0] = -1;
  viz[1] = 1;
  stramosi(1);
}

int lca(int a, int b) {
  for (int i = logN - 1; i >= 0; --i)
    if (lvl[elder[a][i]] >= lvl[b])
      a = elder[a][i];

  for (int i = logN - 1; i >= 0; --i)
    if (lvl[elder[b][i]] >= lvl[a])
      b = elder[b][i];

  if (a == b)
    return a;

  for (int i = logN - 1; i >= 0; --i)
    if (elder[a][i] != elder[b][i]) {
      a = elder[a][i];
      b = elder[b][i];
    }

  return dad[a];
}

void solve() {
  int m, a, b, c;

  assert(scanf("%d", &m));

  for (int i = 1; i <= m; ++i) {
    assert(scanf("%d%d%d", &a, &b, &c));

    if (a == 1) {
      update(-delay[b], ti[b]);
      update(delay[b], tf[b] + 1);
      
      delay[b] = c;

      update(delay[b], ti[b]);
      update(-delay[b], tf[b] + 1);
    } else {
      int d = lca(b, c);
      printf("%d\n", query(ti[b]) - query(ti[dad[d]]) + query(ti[c]) - query(ti[d]));
    }
  }
}

int main() {
  assert(freopen("delay.in", "r", stdin));
  assert(freopen("delay.out", "w", stdout));

  read();

  init();

  solve();

  return 0;
}
