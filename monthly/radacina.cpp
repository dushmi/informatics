#include <cstdio>
#include <cassert>

using namespace std;

const int kMaxG = 10, INF = 1000000000;

const double eps = 0.00001;

int G;

double A[kMaxG];

void read() {
  assert(scanf("%d", &G) == 1);

  for (int i = 0; i <= G; ++i)
    assert(scanf("%lf", &A[i]) == 1);
}

double P(double x) {
  double R = 0;

  for (int i = 0; i <= G; ++i) {
    double RC = A[i];

    for (int j = 1; j <= i; ++j) 
      RC *= x;

    R += RC;
  }

  return R;
}

bool sgn(double x) {
  return (P(x) >= 0);
}

void solve() {
  double st = -20, dr = 20;
  
  while (st < dr - eps) {
    double mid = (st + dr) * 0.5;

    if (sgn(mid) == sgn(st))
      st = mid;
    else
      dr = mid;
  }

  printf("%lf\n", st);
}

int main() {
  assert(freopen("radacina.in", "r", stdin));
  assert(freopen("radacina.out", "w", stdout));

  read();

  solve();

  return 0;
}

