#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int M = 30005, N = 15005, logN = 15;

struct muchie {
  int a, b, c;
};

muchie v[M];

int n, m, k, rez, lung[N], niv[N], tata[N], a[N][logN], d[N][logN];

bool used[N];

int size[N], dad[N]; //apm

vector < pair <int, int> > L[N];

void read() {
  scanf("%d%d%d", &n, &m, &k);

  for (int i = 1; i <= m; ++i) 
    scanf("%d%d%d", &v[i].a, &v[i].b, &v[i].c);
}

bool comp(const muchie &A, const muchie &B) {
  return A.c < B.c;
}

int compress(int nod) {
  if (dad[nod] == 0)
    return nod;

  return (dad[nod] = compress(dad[nod]));
}

void apm() {
  int rx, ry;
  
  sort(v + 1, v + m + 1, comp);

  for (int i = 1; i <= m; ++i) {
    rx = compress(v[i].a);
    ry = compress(v[i].b);

    if (rx != ry) {
      L[v[i].a].push_back(make_pair(v[i].b, v[i].c));
      L[v[i].b].push_back(make_pair(v[i].a, v[i].c));

      if (size[rx] > size[ry]) {
        dad[ry] = rx;
        size[rx] += size[ry];
      } else {
        dad[rx] = ry;
        size[ry] += size[rx];
      }
    }
  }
}

//a[i][j] = stramosul de ordin (2 ^ j) al lui i
void stramosi(int nod, int lvl) {
  used[nod] = 1;
  
  niv[nod] = lvl;

  if (!tata[nod]) {
    lung[nod] = -1;
  } else {
    a[nod][0] = tata[nod];
    lung[nod] = 0;

    for (int j = 1, pas = 2; pas <= lvl; ++j, pas *= 2)
      a[nod][j] = a[a[nod][j - 1]][j - 1], lung[nod] = j;
  }

  for (int i = 0; i < (int)L[nod].size(); ++i)
    if (!used[L[nod][i].first]) {
      tata[L[nod][i].first] = nod;
      stramosi(L[nod][i].first, lvl + 1);
    }
}

void din(int c, int nod, int lvl) {
  used[nod] = 1;
  
  d[nod][0] = c;

  for (int j = 1, pas = 2; j <= lung[nod]; ++j, pas *= 2)
    d[nod][j] = max(d[nod][j - 1], d[a[nod][j - 1]][j - 1]);

  for (int i = 0; i < (int)L[nod].size(); ++i)
    if (!used[L[nod][i].first])
      din(L[nod][i].second, L[nod][i].first, lvl + 1);
}

void init() {
  for (int i = 1; i <= n; ++i)
    used[i] = 0;
  
  for (int i = 1; i <= n; ++i)
    if (!used[i])
      stramosi(i, 0);
  
  for (int i = 1; i <= n; ++i)
    used[i] = 0;

  for (int i = 1; i <= n; ++i)
    if (!used[i])
      din(0, i, 0);
}

void lca(int x, int y) {
  if (niv[x] < niv[y]) 
    swap(x, y);

  for (int i = lung[x]; i >= 0; --i)
    if (niv[x] - (1 << i) >= niv[y]) {
      rez = max(rez, d[x][i]);
      x = a[x][i];
    }
  
  if (x == y)
    return;

  for (int i = lung[y]; i >= 0; -- i)
    if (a[x][i] && a[x][i] != a[y][i]) {
      rez = max(rez, d[x][i]);
      rez = max(rez, d[y][i]);

      x = a[x][i];
      y = a[y][i];
    }

  rez = max(rez, d[x][0]);
  rez = max(rez, d[y][0]);
}

void solve() {
  int x, y;

  for (int i = 1; i <= k; ++i) {
    scanf("%d%d", &x, &y);

    rez = 0;

    lca(x, y);

    printf("%d\n", rez);
  }
}

int main() {
  freopen("radiatie.in", "r", stdin);
  freopen("radiatie.out", "w" ,stdout);

  read();

  apm();

  init();

  solve();

  return 0;
}
