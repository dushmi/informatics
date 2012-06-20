#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

const int kMaxN = 10005;

int N, M, pos[kMaxN], D[kMaxN], T[kMaxN];

void read() {
  assert(scanf("%d%d", &N, &M) == 2);
  
  for (int i = 1; i <= N; ++i) {
    assert(scanf("%d%d", &D[i], &T[i]) == 2);
    assert(D[i] <= M && T[i] <= M);
  }
}

inline bool comp(const int a, const int b) {
  return (D[a] + T[a] < D[b] + T[b]);
}

void solve() {
  for (int i = 1; i <= N; ++i)
    pos[i] = i;

  sort(pos + 1, pos + N + 1, comp);

  for (int i = 1; i <= N; ++i) {
    if (M < D[pos[i]] + T[pos[i]]) {
      printf("%d\n", i - 1);
      return;
    }

    M -= (D[pos[i]] + T[pos[i]]);
  }

  printf("%d\n", N);
}

int main() {
  assert(freopen("filme.in", "r", stdin));
  assert(freopen("filme.out", "w", stdout));

  read();

  solve();

  return 0;
}
