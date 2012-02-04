#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 25;

const double eps = 0.0001;

struct point {
  double x, y;
};

point origin, no, A[N], B[N], C[4 * N];

int n, m, l;

void read() {
  assert(scanf("%d", &n));

  for (int i = 1; i <= n; ++i)
    assert(scanf("%lf%lf", &A[i].x, &A[i].y));

  assert(scanf("%d", &m));

  for (int i = 1; i <= m; ++i)
    assert(scanf("%lf%lf", &B[i].x, &B[i].y));
}

inline double min(double x, double y) {
  return x < y ? x : y;
}

inline double max(double x, double y) {
  return x > y ? x : y;
}

inline double modul(double x) {
  return x < 0 ? (-x) : x;
}

point intersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
  double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

  if (modul(d) < eps)
    return no;

  point p;

  p.x = ((x3 - x4) * (x1 * y2 - y1 * x2) - (x1 - x2) * (x3 * y4 - y3 * x4)) / d;
  p.y = ((y3 - y4) * (x1 * y2 - y1 * x2) - (y1 - y2) * (x3 * y4 - y3 * x4)) / d;

  if (p.x < min(x1, x2) - eps || p.x < min(x3, x4) - eps || p.x > max(x1, x2) + eps || p.x > max(x3, x4) + eps)
    return no;

  if (p.y < min(y1, y2) - eps || p.y < min(y3, y4) - eps || p.y > max(y1, y2) + eps || p.y > max(y3, y4) + eps)
    return no;

  return p;
}

double arie_poligon(point *A, int l) {
  double s = 0;

  for (int i = 1; i <= l; ++i)
    s += (A[i].x * A[i + 1].y - A[i + 1].x * A[i].y);

  s *= 0.5;

  return modul(s);
}

double arie(double x1, double y1, double x2, double y2, double x3, double y3) {
  return 0.5 * modul(x1 * y2 + x2 * y3 + x3 * y1 - y2 * x3 - y3 * x1 - y1 * x2);
}

double suma_pct(double x, double y, point *A, int l) {
  double s = 0;

  for (int i = 1; i <= l; ++i)
    s += arie(x, y, A[i].x, A[i].y, A[i + 1].x, A[i + 1].y);

  return s;
}

bool in_poligon(double x, double y, point *A, int l) {
  if (modul(arie_poligon(A, l) - suma_pct(x, y, A, l)) < eps)
    return 1;

  return 0;
}

void init() {
  A[n + 1] = A[1];
  B[m + 1] = B[1];
  
  no.x = 51;
  no.y = 51;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      point newp = intersection(A[i].x, A[i].y, A[i + 1].x, A[i + 1].y, B[j].x, B[j].y, B[j + 1].x, B[j + 1].y);

      if (newp.x == no.x && newp.y == no.y)
        continue;

      C[++l] = newp;
    }
  
  for (int i = 1; i <= n; ++i)
    if (in_poligon(A[i].x, A[i].y, B, m))
      C[++l] = A[i];
  
  for (int i = 1; i <= m; ++i)
    if (in_poligon(B[i].x, B[i].y, A, n))
      C[++l] = B[i];
}

bool comp(point a, point b) {
  double a1 = atan2(a.y - origin.y, a.x - origin.x);
  double a2 = atan2(b.y - origin.y, b.x - origin.x);

  return (a1 < a2);
}

void solve() {
  for (int i = 1; i <= l; ++i)
    origin.x += C[i].x, origin.y += C[i].y;

  origin.x /= (double)l;
  origin.y /= (double)l;

  sort(C + 1, C + l + 1, comp);

  C[l + 1] = C[1];
  
  printf("%.3lf", arie_poligon(C, l)); 
}

int main() {
  assert(freopen("arie.in", "r", stdin));
  assert(freopen("arie.out", "w", stdout));

  read();

  init();

  solve();

  return 0;
}
