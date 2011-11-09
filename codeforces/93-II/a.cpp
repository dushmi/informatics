#include <cstdio>
#include <cmath>

struct punct {
  int x, y;
};

const int N = 105;

int n, k;

punct a[N];

void read() {
  scanf("%d%d", &n, &k);

  for (int i = 1; i <= n; ++i)
    scanf("%d%d", &a[i].x, &a[i].y);
}

inline double dist(int x1, int y1, int x2, int y2) {
  return (double)sqrt((double)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))); 
}

void solve() {
  double rez = 0;

  for (int i = 1; i < n; ++i)
    rez += dist(a[i].x, a[i].y, a[i + 1].x, a[i + 1].y);

  rez = rez * (double) k / (double) 50;

  printf("%.9lf", rez);
}

int main() {
  read();

  solve();

  return 0;
}
