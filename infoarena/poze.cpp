#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 305;

struct Suffix_Array {
  int a, b, c, d;
  short int lin, col;

  Suffix_Array(int _a, int _b, int _c, int _d, short int _lin, short int _col) {
    a = _a; b = _b; c = _c; d = _d;
    lin = _lin; col = _col;
  }

  bool operator<(const Suffix_Array &other) const {
    if (a < other.a)
      return 1;

    if (a > other.a)
      return 0;

    if (b < other.b)
      return 1;

    if (b > other.b)
      return 0;

    if (c < other.c)
      return 1;

    if (c > other.c)
      return 0;

    return (d < other.d);
  }

  bool operator==(const Suffix_Array &other) const {
    return ((a == other.a) && (b == other.b) && (c == other.c) && (d == other.d));
  }
};

int n, m, k, log, a[N][N], d[N][N][9];

void read() {
  scanf("%d%d%d", &n, &m, &k);

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%d", &a[i][j]);
}

void init() {
  vector <Suffix_Array> v;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      v.push_back(Suffix_Array(a[i][j], 0, 0, 0, i, j));

  sort(v.begin(), v.end());

  int q = 1;
  d[v[0].lin][v[0].col][0] = q;

  for (int i = 1; i < (int)v.size(); ++i) {
    if (!(v[i] == v[i - 1]))
      ++q;

    d[v[i].lin][v[i].col][0] = q;
  }
  
  int k, c = 1, lc = 1;

  for (k = 1, c = 2; c <= min(n, m); ++k, c <<= 1, lc <<= 1) {
    v.clear();

    for (int i = 1; i <= n - c + 1; ++i)
      for (int j = 1; j <= m - c + 1; ++j)
        v.push_back(Suffix_Array(d[i][j][k - 1], d[i][j + lc][k - 1], d[i + lc][j][k - 1], 
                                 d[i + lc][j + lc][k - 1], i, j));
  
    sort(v.begin(), v.end());
    
    int q = 1;
    d[v[0].lin][v[0].col][k] = q;

    for (int i = 1; i < (int)v.size(); ++i) {
      if (!(v[i] == v[i - 1]))
        ++q;

      d[v[i].lin][v[i].col][k] = q;
    }  
  }

  log = k - 1;
}

int compute(int lat) {
  vector <Suffix_Array> v;

  int logc = 0;

  while ((1 << logc) <= lat)
    ++logc;

  --logc;

  int c = (1 << logc);

  for (int i = 1; i <= n - lat + 1; ++i)
    for (int j = 1; j <= m - lat + 1; ++j)
      v.push_back(Suffix_Array(d[i][j][logc], d[i][j + lat - c][logc], d[i + lat - c][j][logc], 
                               d[i + lat - c][j + lat - c][logc], 0, 0));
  
  sort(v.begin(), v.end());

  int lc = 1, rez = 1;

  for (int i = 1; i < (int)v.size(); ++i) {
    if (v[i] == v[i - 1]) {
      ++lc; 
      if (lc > rez)
        rez = lc;
      continue;
    }

    lc = 1;
  }

  return rez;
}

void solve() {
  int i = 0, pas = (1 << log);

  for (i = 0; pas; pas >>= 1)
    if (compute(i + pas) >= k)
      i += pas;
  
  printf("%d\n", i);
}

int main() {
  freopen("poze.in", "r", stdin);
  freopen("poze.out", "w", stdout);
  
  int T;

  scanf("%d\n", &T);

  for (int i = 1; i <= T; ++i) {
    read();

    init();

    solve();
  }

  return 0;
}
