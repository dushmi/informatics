#include <cstdio>
#include <vector>
#include <cassert>
#include <map>

using namespace std;

const int N = 260;

int n, profit[N], d1[N * N], d2[N * N], l1[N * N], l2[N * N];

map <int, vector <int> > v;

vector <int> rez[N * N], nrez[N * N];

void read() {
  int m, a, b;

  pair <int, vector <int> > newn;

  assert(scanf("%d%d", &n, &m));

  for (int i = 1; i <= n; ++i) {
    assert(scanf("%d", &profit[i]));
    newn.first = i;
    v.insert(newn);
  }

  for (int i = 1; i <= m; ++i) {
    assert(scanf("%d%d", &a, &b));
    v[a].push_back(b);
    v[b].push_back(a);
  }
}

void reset(int a[N]) {
  for (int i = 1; i <= n; ++i)
    a[i] = 0;
}

void df(int nod, int cc, int f[N], map <int, vector <int> > v) {
  f[nod] = cc;

  for (int i = 0; i < (int)v[nod].size(); ++i)
    if (!f[v[nod][i]])
      df(v[nod][i], cc, f, v);
}

int nc;

void solve(map <int, vector <int> > v) {
  if (v.size() == 1) {
    d1[nc] = d2[nc] = profit[v.begin()->first];
    l1[nc] = l2[nc] = 1;
    rez[nc].push_back(v.begin()->first);
    nrez[nc].push_back(v.begin()->first);
    return;
  }

  int fr[N], cc = 0, curent = nc, son;

  reset(fr);

  for (map <int, vector <int> > :: iterator it = v.begin(); it != v.end(); ++it)
    if (!fr[it->first]) {
      ++cc;
      df(it->first, cc, fr, v);
    }

  if (cc == 1) {
    map <int, vector <int> > newv;

    pair <int, vector <int> > a;

    for (map <int, vector <int> > :: iterator it = v.begin(); it != v.end(); ++it) {
      int fr2[N];

      reset(fr2);

      a.first = it->first;

      newv.insert(a);

      for (int i = 0; i < (int)v[it->first].size(); ++i)
        fr2[v[it->first][i]] = 1;

      for (int i = 1; i <= n; ++i)
        if (!fr2[i] && fr[i] && i != it->first)
          newv[it->first].push_back(i);
    }

    son = ++nc;
    solve(newv);

    d1[curent] = d2[son];
    l1[curent] = l2[son];
    d2[curent] = d1[son];
    l2[curent] = l1[son];

    for (int i = 0; i < (int)nrez[son].size(); ++i)
        rez[curent].push_back(nrez[son][i]);

    for (int i = 0; i < (int)rez[son].size(); ++i)
        nrez[curent].push_back(rez[son][i]);
  } else {
    map <int, vector <int> > newv;

    for (int i = 1; i <= cc; ++i) {
      newv.clear();

      for (map <int, vector <int> > :: iterator it = v.begin(); it != v.end(); ++it)
        if (fr[it->first] == i)
          newv.insert(*it);

      son = ++nc;
      solve(newv);

      if (d1[son] > d1[curent]) {
        d1[curent] = d1[son];
        l1[curent] = l1[son];

        rez[curent].clear();

        for (int j = 0; j < (int)rez[son].size(); ++j)
          rez[curent].push_back(rez[son][j]);
      }
      d2[curent] += d2[son];
      l2[curent] += l2[son];

      for (int j = 0;j < (int)nrez[son].size(); ++j)
        nrez[curent].push_back(nrez[son][j]);
    }
  }
}

int main() {
  assert(freopen("soc.in", "r", stdin));
  assert(freopen("soc.out", "w", stdout));

  read();

  solve(v);

  printf("%d\n%d\n", d1[0], l1[0]);

  for (int i = 0; i < (int)rez[0].size(); ++i)
    printf("%d ", rez[0][i]);

  return 0;
}
