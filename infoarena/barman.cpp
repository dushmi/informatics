#include <cstdio>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

const int N = 605;

int n, rez = 0x3f3f3f3f, a[N], b[N << 1];

void read() {
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
}

void init() {
  for (int i = 1; i <= n; ++i)
    b[i] = a[i];

  sort(b + 1, b + n + 1);

  for (int i = 1; i <= n; ++i)
    b[n + i] = b[i];
}

inline int abs(int x) {
  return x > 0 ? x : (-x);
}

void solve(int *a, int *b) {
  int c = 0, nr = 0;

  map<int, list <int> > v;

  for (int i = 1; i <= n; ++i)
    if (a[i] != b[i]) {
      ++nr;
      v[a[i]].push_back(i);
    }

  c = 20 * nr;

  for (int i = 1; i <= n; ++i)
    if (a[i] != b[i]) {
      c += abs(i - *v[b[i]].begin());
      v[b[i]].pop_front();
    }

  if (c < rez)
    rez = c;
}

void solve() {
  for (int i = 1; i <= n; ++i)
    solve(a, b + i - 1);

  printf("%d\n", rez);
}

int main() {
  freopen("barman.in", "r", stdin);
  freopen("barman.out", "w", stdout);

  read();

  init();

  solve();

  return 0;
}
