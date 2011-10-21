#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int N = 20005;

vector <pair <int, int> > L[N];

int n, down[N], dad[N], up[N], val[N], M[N][2], v[N][2];

bool used[N];

void reset() {
  for (int i = 1; i <= n; ++i) {
    L[i].clear();
    down[i] = up[i] = val[i] = 0;
    M[i][0] = M[i][1] = v[i][0] = v[i][1] = 0;
  }
}

void reset(bool a[N]) {
  for (int i = 1; i <= n; ++i)
    used[i] = 0;
}

void read() {
  int x, y, p;

  scanf("%d", &n);

  for (int i = 1; i < n; ++i) {
    scanf("%d%d%d", &x, &y, &p);

    L[x].push_back(make_pair(y, p));
    L[y].push_back(make_pair(x, p));
  }
}

void df(int nod) {
  used[nod] = 1;

  for (int i = 0; i < (int)L[nod].size(); ++i)
    if (!used[L[nod][i].first]) {
      df(L[nod][i].first);
      down[nod] = max(down[nod], down[L[nod][i].first] + L[nod][i].second);
      dad[L[nod][i].first] = nod;
    }
}

void init() {
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j < (int)L[i].size(); ++j)
      if (L[i][j].first != dad[i] && v[i][0] < down[L[i][j].first] + L[i][j].second)
        M[i][0] = L[i][j].first, v[i][0] = down[L[i][j].first] + L[i][j].second;

  for (int i = 1; i <= n; ++i)
    for (int j = 0; j < (int)L[i].size(); ++j)
      if (L[i][j].first != dad[i] && L[i][j].first != M[i][0] && down[M[i][1]] < down[L[i][j].first] + L[i][j].second)
        M[i][1] = L[i][j].first, v[i][1] = down[L[i][j].first] + L[i][j].second;
}

void din(int nod, int lc) {
  used[nod] = 1;

  if (nod == M[dad[nod]][0])
    up[nod] = max(lc + up[dad[nod]], lc + v[dad[nod]][1]);
  else
    up[nod] = max(lc + up[dad[nod]], lc + v[dad[nod]][0]);

  for (int i = 0; i < (int)L[nod].size(); ++i)
    if (!used[L[nod][i].first])
      din(L[nod][i].first, L[nod][i].second);
}

void solve() {
  used[1] = 1;
  val[1] = down[1];

  for (int i = 0; i < (int)L[1].size(); ++i)
    din(L[1][i].first, L[1][i].second);
}

void print() {
  int m = 1 << 30;

  for (int i = 1; i <= n; ++i)
    val[i] = max(down[i], up[i]);

  for (int i = 1; i <= n; ++i)
    if (m > val[i])
      m = val[i];
 
  for (int i = 1; i <= n; ++i)
    if (val[i] == m)
      printf("%d\n", i);
}

int main() {
  freopen("razboi.in", "r", stdin);
  freopen("razboi.out", "w", stdout);

  int T = 0;

  scanf("%d", &T);

  for (int i = 1; i <= T; ++i) {
    printf("Testul nr #%d\n",i);

    reset();

    read();

    reset(used);

    df(1);

    reset(used);

    init();

    solve();
    
    print();
  }

  return 0;
}
