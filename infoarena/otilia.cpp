#include <cstdio>
#include <algorithm>

using namespace std;

const int M = 30005, N = 5000005;

struct query {
  int n, k, p, poz;
  bool rez;
};

int m, dr, d[N];

pair <int, int> st[N];

query v[M];

void read() {
  scanf("%d", &m);

  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &v[i].n, &v[i].k, &v[i].p);
    v[i].poz = i;
  }
}

inline void elim_dr1(int i) {
  while (st[dr].second < i && dr >= 1)
    --dr;
}

inline void elim_dr2(int i, int end) {
  while (st[dr].second <= end && dr >= 1)
    --dr;
  
  st[++dr] = make_pair(i, end);
}

void init(int p) {
  dr = 0;

  for (int i = 1; i < N - 5; ++i) {
    elim_dr1(i);
    
    if (dr == 0) {
      d[i] = N;
      elim_dr2(i, N);
    } else {
      d[i] = i - st[dr].first;
      elim_dr2(i, i + (d[i] - 1) / p);
    }
  }
}

bool comp_p(query a, query b) {
  return a.p < b.p;
}

void solve() {
  sort(v + 1, v + m + 1, comp_p);

  for (int i = 1; i <= m; ++i) {
    if (v[i].p != v[i - 1].p)
      init(v[i].p);

    if (d[v[i].n] <= v[i].k)
      v[i].rez = 1;
  }
}

bool comp_poz(query a, query b) {
  return a.poz < b.poz;
}

void print() {
  sort(v + 1, v + m + 1, comp_poz);

  for (int i = 1; i <= m; ++i)
    printf("%d\n", v[i].rez);
}

int main() {
  freopen("otilia.in", "r", stdin);
  freopen("otilia.out", "w", stdout);

  read();

  solve();

  print();

  return 0;
}
