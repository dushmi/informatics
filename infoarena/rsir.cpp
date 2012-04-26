#include <cstdio>
#include <utility>

using namespace std;

const int kMaxM = 7005;

int a, b, x, y, z, T0, T1, M, v1[kMaxM], v2[kMaxM];

long long n;

inline void next(pair <int, int> &a) {
  int x = v1[a.first] + v2[a.second];
  if (x >= M)
    x -= M;
  
  a.second = a.first;
  a.first = x;
}

void read() {
  scanf("%d%d%d%d%d%d%d%d%lld", &T0, &T1, &a, &b, &x, &y, &z, &M, &n);
  T0 %= M;
  T1 %= M;
}

void init() {
  int aux;
  
  for (int i = 0; i < M; ++i) {
    aux = (i * i) % M;
    v1[i] = (b * aux + y * i) % M;
    v2[i] = (a * aux + x * i + z) % M;
  }
}

void solve() {
  pair <int, int> p1, p2;

  p1.first = p2.first = T1;
  p1.second = p2.second = T0;

  do {
    next(p1);
    next(p2); next(p2);
  } while (p1 != p2);

  // determin lungimea ciclului
  int lciclu = 0;

  do {
    next(p2);
    ++lciclu;
  } while (p1 != p2);

  // determin lungimea unei cozi posibile 
  int lcoada = 0;

  p2.first = T1;
  p2.second = T0;
  
  while (p1 != p2) {
    next(p2);
    ++lcoada;
  }

  // rezolv
  p2.first = T1;
  p2.second = T0;

  --n;

  if (n < lcoada)
    lcoada = n;

  for (int i = 1; i <= lcoada; ++i)
    next(p2);

  n -= lcoada;
  if (n > 0) {
    n %= lciclu;
    for (int i = 1; i <= n; ++i)
      next(p2);
  }

  printf("%d\n", p2.first);
}

int main() {
  freopen("rsir.in", "r", stdin);
  freopen("rsir.out", "w", stdout);

  read();

  init();

  solve();

  return 0;
}
