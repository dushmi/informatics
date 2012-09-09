#include <cstdio>
#include <cassert>

const int kMaxN = 25;

const double coef = (double)1 / 6;

int N;

double expected[kMaxN];

int main() {
  assert(freopen("zaruri.in", "r", stdin));
  assert(freopen("zaruri.out", "w", stdout));

  assert(scanf("%d", &N) == 1);

  expected[1] = 3.5;

  for (int i = 2; i <= N; ++i)
    for (int j = 1; j <= 6; ++j)
      expected[i] += (j < expected[i - 1]) ? (expected[i - 1] * coef) : (j * coef);
  
  printf("%.7lf", expected[N]);

  return 0;       
}
