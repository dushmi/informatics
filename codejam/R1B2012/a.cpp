#include <cstdio>

const int kMaxN = 205;

int N, X, J[kMaxN];

void read() {
  scanf("%d", &N);

  for (int i = 1; i <= N; ++i) {
    scanf("%d", &J[i]);
    X += J[i];
  }
}

const double eps = 0.00000001;

bool win(double x, int pos) {
  double newp = 1.0 * J[pos] + x * X, need = 0;

  for (int i = 1; i <= N; ++i)
    if (i != pos && J[i] + eps < newp)
      need += (newp + eps - 1.0 * J[i]) / X;

  if (need + x > 1 + eps)
    return 1;

  return 0;
}

double cbin(int pos) {
  double i = 0, step = 1.0;

  for (i = 0; step > eps; step *= 0.5)
    if (i + step <= 1.0 + eps && !win(i + step, pos))
      i += step;
  
  return i;
}

void solve() {
  for (int i = 1; i <= N; ++i)
    printf("%lf ", cbin(i) * 100.00); 
  printf("\n");
}

int main() {
  freopen("file.in", "r", stdin);
  freopen("file.out", "w", stdout);

  int T;

  scanf("%d", &T);

  for (int i = 1; i <= T; ++i) {
    X = 0;

    read();

    printf("Case #%d: ", i);

    solve();
  }

  return 0;
}
