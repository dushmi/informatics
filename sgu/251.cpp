#include <cstdio>

const int N = 10;

int n;

double r[N];

void read() {
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i)
    scanf("%lf", &r[i]);
}

void solve3() {
  double b = r[1] + r[2];
  double h = (r[1] + r[2] + r[3]) * 2.0 / b;

  printf("%.4lf %.4lf\n", 0.0, 0.0);
  printf("%.4lf %.4lf\n", 0.0, b);
  printf("%.4lf %.4lf\n", h, 0.0);
}

void solve4() {
  if (r[1] == r[2]) {
    double b = r[1] + r[2];
    double h = (r[1] + r[2] + r[3]) * 2.0 / b;

    printf("%.4lf %.4lf\n", 0.0, 0.0);
    printf("%.4lf %.4lf\n", 0.0, b);
    printf("%.4lf %.4lf\n", h, 0.0);
    printf("%.4lf %.4lf\n", h, (r[1] + r[3] + r[4]) * 2.0 / h);
  } else {
    double b = r[1] + r[2];
    double h = (r[1] + r[2] + r[3]) * 2.0 / b;

    printf("%.4lf %.4lf\n", 0.0, 0.0);
    printf("%.4lf %.4lf\n", 0.0, b);
    printf("%.4lf %.4lf\n", -h, (r[1] + r[3] + r[4]) / h);
    printf("%.4lf %.4lf\n", h, (r[1] + r[3] + r[4]) / h);
  }
}

int main() {
  read();

  if (n >= 5 || (n == 4 && !(r[1] == r[2] || r[1] + r[2] == r[3] + r[4]))) {
    printf("NO\n");
    return 0;
  }

  printf("YES\n");

  if (n == 3)
    solve3();
  else
    solve4();

  return 0;
}
