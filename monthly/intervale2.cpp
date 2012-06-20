#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

const int kMaxN = 100005, INF = 2000000000;

int N, res[kMaxN], A[kMaxN], newpos[kMaxN], P[kMaxN], aib[kMaxN];

void read() {
  assert(scanf("%d", &N) == 1);
  assert(1 <= N && N <= kMaxN);

  for (int i = 1; i <= N; ++i) {
    assert(scanf("%d", &A[i]) == 1);
    assert(-INF <= A[i] && A[i] <= INF);
  }

  for (int i = 1; i <= N; ++i) {
    assert(scanf("%d", &P[i]) == 1);
    assert(1 <= P[i] && P[i] <= i);
  }
}

inline int bit(int x) {
  return (x & (-x));
}

inline bool comp(const int &x, const int &y) {
  return (A[x] > A[y]);
}

int query(int p) {
  int ans = 0;

  while (p) {
    ans += aib[p];
    p -= bit(p);
  }

  return ans;
}

void insert(int p) {
  while (p <= N) {
    ++aib[p];
    p += bit(p);
  }
}

void solve() {
  for (int i = 1; i <= N; ++i)
    newpos[i] = i;
  
  sort(newpos + 1, newpos + N + 1, comp);

  for (int i = 1; i <= N; ++i) {
    res[newpos[i]] = query(newpos[i]) - query(P[newpos[i]] - 1);
    insert(newpos[i]);
  }

  for (int i = 1; i <= N; ++i)
    printf("%d ", res[i]);
}

int main () {
  assert(freopen("intervale2.in", "r", stdin));
  assert(freopen("intervale2.out", "w", stdout));

  read();

  solve();

  return 0;
}
