#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

struct circle {
  int x, y, r;
};

struct slope {
  int dy, dx;
};

const int N = 2005;

circle v[N];

int n, ans[N];

vector <pair <slope, vector <int> > > L;

void read() {
  assert(scanf("%d", &n));
  
  for (int i = 1; i <= n; ++i)
    assert(scanf("%d%d%d", &v[i].x, &v[i].y, &v[i].r));
}

inline int cmmdc(int x, int y)  {
  int r = x % y;

  while (r) {
    x = y;
    y = r;
    r = x % y;
  }

  return y;
}

bool comp(int a, int b) {
  if (v[a].x < v[b].x)
    return 1;

  if (v[a].x > v[b].x)
    return 0;

  return v[a].y < v[b].y;
}

void init() {
  for (int i = 1; i <= n; ++i) {
    slope c;
    c.dx = v[i].x; c.dy = v[i].y;
    int nc = cmmdc(c.dx, c.dy);
    c.dx /= nc; c.dy /= nc;

    bool ok = 0;
    for (int j = 0; j < (int)L.size(); ++j)
      if (c.dx == L[j].first.dx && c.dy == L[j].first.dy) {
        ok = 1;
        L[j].second.push_back(i);
        break;
      }

    if (!ok) {
      vector <int> now;
      now.push_back(i);
      L.push_back(make_pair(c, now));
    }
  }

  for (int i = 0; i < (int)L.size(); ++i)
    sort(L[i].second.begin(), L[i].second.end(), comp);

  printf("%d ", (int)L.size());
}

inline int dist(int a, int b) {
  return (v[a].x - v[b].x) * (v[a].x - v[b].x) + (v[a].y - v[b].y) * (v[a].y - v[b].y);
}

void solve() {
  int d[N];
  
  for (int i = 0; i < (int)L.size(); ++i) {
    for (int j = 0; j < (int)L[i].second.size(); ++j)
      d[j] = 1;

    for (int j = 1; j < (int)L[i].second.size(); ++j)
      for (int k = 0; k < j; ++k)
        if (dist(L[i].second[j], L[i].second[k]) > (v[L[i].second[j]].r + v[L[i].second[k]].r) * (v[L[i].second[j]].r + v[L[i].second[k]].r))
          d[j] = max(d[j], d[k] + 1);
 
    for (int j = 0; j < (int)L[i].second.size(); ++j)
      ans[i] = max(ans[i], d[j]);
  }

  int rez = 0, nre = 0;

  for (int i = 0; i < (int)L.size(); ++i)
    if (ans[i] > rez) {
      rez = ans[i];
      nre = 1;
    } else if (ans[i] == rez)
      ++nre;

  printf("%d %d\n", rez, nre);
}

int main() {
  assert(freopen("cerc3.in", "r", stdin));
  assert(freopen("cerc3.out","w", stdout));

  read();

  init();

  solve();

  return 0;
}
