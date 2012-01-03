#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 1505;

const double eps = 0.0001, sin60 = sqrt(3.0) / 2.0, cos60 = 0.5;

pair <double, double> v[N];

int n;

double modul(double x) {
  return x < 0 ? (-x) : x;
}

void read() {
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i)
    scanf("%lf%lf", &v[i].first, &v[i].second);
}

bool cb(int pi, double x, double y) {
  int i = 0, pas = 1 << 10;

  for (i = pi; pas; pas >>= 1)
    if (i + pas <= n && (v[i + pas].first <= x + eps || (modul(v[i + pas].first - x) <= eps && v[i + pas].second <= y + eps)))
      i += pas;

  if (modul(v[i].first - x) <= eps && modul(v[i].second - y) <= eps)
    return 1;

  return 0;
}

void solve() {
  int rez = 0;

  double x, y;

  sort(v + 1, v + n + 1);

  for (int i = 1; i < n - 1; ++i)
    for (int j = i + 1; j < n; ++j) {
      x = v[i].first + (v[j].first - v[i].first) * cos60 + (v[j].second - v[i].second) * sin60;
      y = v[i].second + (v[j].second - v[i].second) * cos60 - (v[j].first - v[i].first) * sin60;
      rez += cb(j + 1, x, y);

      x = v[i].first + (v[j].first - v[i].first) * cos60 - (v[j].second - v[i].second) * sin60;
      y = v[i].second + (v[j].second - v[i].second) * cos60 + (v[j].first - v[i].first) * sin60;
      rez += cb(j + 1, x, y);
    }

  printf("%d\n", rez);
}

int main() {
  freopen("triang.in", "r", stdin);
  freopen("triang.out", "w", stdout);

  read();

  solve();

  return 0;
}
