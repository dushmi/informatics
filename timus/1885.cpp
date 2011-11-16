#include <cstdio>

double h, t, v, x;

inline double min(double x, double y) {
  return x < y ? x : y;
}

inline double max(double x, double y) {
  return x > y ? x : y;
}

int main() {
  scanf("%lf%lf%lf%lf", &h, &t, &v, &x);
  
  printf("%.7lf %.7lf\n", max(0, t - (h - t * v) / (x - v)), min(t, h / x));

  return 0;
}
