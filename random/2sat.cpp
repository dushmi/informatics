#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

const int kMaxN = 200005;

vector <int> L[kMaxN], LT[kMaxN];

int N, ft[kMaxN], sol[kMaxN];

inline int non(int x) {
  return (x <= N) ? (x + N) : (x - N);
}

void read() {
  int M, a, b;

  assert(scanf("%d%d", &N, &M) == 2);

  for (int i = 1; i <= M; ++i) {
    assert(scanf("%d%d", &a, &b) == 2);

    if (a < 0)
      a = N + (- a);

    if (b < 0)
      b = N + (- b);

    L[non(a)].push_back(b);
    L[non(b)].push_back(a);
  
    LT[b].push_back(non(a));
    LT[a].push_back(non(b));
  }
}

bool impossible, viz[kMaxN];

void make_vec(int nod) {
  viz[nod] = 1;
  
  for (size_t i = 0; i < L[nod].size(); ++i)
    if (! viz[L[nod][i]])
      make_vec(L[nod][i]);

  ft[++ ft[0]] = nod;
}

void ctc(int nod) {
  if (sol[nod]) 
    impossible = 1;

  viz[nod] = 1;
  sol[non(nod)] = 1;
  
  for (size_t i = 0; i < LT[nod].size(); ++i)
    if (! viz[LT[nod][i]])
      ctc(LT[nod][i]);
}

void reset() {
  for (int i = 1; i <= 2 * N; ++i)
    viz[i] = 0;
}

void solve() {
  for (int i = 1; i <= 2 * N; ++i)
    if (! viz[i])
      make_vec(i);

  reset();
  
  for (int i = 2 * N; i >= 1; --i)
      if (!viz[ft[i]] && !viz[non(ft[i])])
        ctc(ft[i]);

  if (impossible) {
    printf("-1\n");
    return;
  }

  for (int i = 1; i <= N; ++i)
    printf("%d ", sol[i]);
}

int main() {
  assert(freopen("2sat.in", "r", stdin));
  assert(freopen("2sat.out", "w", stdout));

  read();
  solve();
  
  return 0;
}
