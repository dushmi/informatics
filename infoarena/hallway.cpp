#include <cassert>
#include <cstdio>

using namespace std;

const int N = 1005;

const double eps = 1e-9;

int n, m, k, x[N], y[N];

bool ok, up, down, viz[N];

double R;

inline double modul(double x) {
  return x < 0 ? (-x) : x;
}

void read() {
  assert(scanf("%d%d%d", &n, &m, &k));
  
  for (int i = 1; i <= k; ++i)
    assert(scanf("%d%d", &x[i], &y[i]));
}

void init() {
  int j = 0;

  for (int i = 1; i <= k; ++i)
    if (x[i] >= 0 && x[i] <= n && y[i] >= 0 && y[i] <= m) {
      ++j;
      x[j] = x[i];
      y[j] = y[i];
    }

  k = j;
}

void df(int nod) {
  viz[nod] = 1;
  
  if ((double)y[nod] - R < R || modul((double)y[nod] - R - R) < eps)
    down = 1;
  if ((double)y[nod] + R > (double)m - R || modul(y[nod] + R - ((double)m - R)) < eps)
    up = 1;
  
  if (up && down) {
    ok = 0;
    return;
  }

  double d;

  for (int i = 1; i <= k && ok; ++i)
    if (!viz[i]) {
      d = (x[i] - x[nod]) * (x[i] - x[nod]) + (y[i] - y[nod]) * (y[i] - y[nod]);

      if (d < 4.0 * R * R || modul(d - 4.0 * R * R) < eps)
        df(i);
    }
}

void cb() {
  double st = 0, dr = 0.5 * m;
  
  while (modul(dr - st) > eps) {
    R = (st + dr) * 0.5;

    for (int i = 1; i <= k; ++i)
      viz[i] = 0;
    
    ok = 1;

    for (int i = 1; i <= k && ok; ++i)
      if (!viz[i]) {
        up = down = 0;
        df(i);
      }

    if (ok) 
      st = R;
    else
      dr = R;
  }

  printf("%.8lf\n", R);
}

int main() {
  assert(freopen("hallway.in", "r", stdin));
  assert(freopen("hallway.out", "w", stdout));

  read();

  init();

  cb();

  return 0;
}
