#include <cstdio>
#include <cmath>

const int N = 100005, MOD = 666013;

int rez, v[N], d[N];

double val[N];

inline int modul(int x) {
  return x < 0 ? (-x) : x;
}

void read() {
  int n, x;

  scanf("%d", &n);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);

    if (x)
      v[++v[0]] = modul(x);
  }
}

void solve() {
  d[0] = 0;
  val[0] = 0;

  for (int i = 1; i <= v[0]; ++i) {
    d[i] = 1;
    val[i] = val[i - 1] + log(v[i]);

    if (i - 2 >= 0 && val[i - 2] + log(v[i - 1] + v[i]) > val[i]) {
      d[i] = 2;
      val[i] = val[i - 2] + log(v[i - 1] + v[i]);
    }

    if (i - 3 >= 0 && val[i - 3] + log(v[i - 2] + v[i - 1] + v[i]) > val[i]) {
      d[i] = 3;
      val[i] = val[i - 3] + log(v[i - 2] + v[i - 1] + v[i]);
    }
  }
}

void compute(int poz) {
  if (poz == 0)
    return;

  if (d[poz] == 1)
    rez *= v[poz];

  if (d[poz] == 2)
    rez *= (v[poz - 1] + v[poz]);

  if (d[poz] == 3)
    rez *= (v[poz - 2] + v[poz - 1] + v[poz]);

  if (rez >= MOD)
    rez %= MOD;

  compute(poz - d[poz]);
}

int main() {
  freopen("emax.in", "r", stdin);
  freopen("emax.out", "w", stdout);

  read();

  solve();
  
  rez = 1;

  compute(v[0]);

  printf("%d\n", rez);

  return 0;
}
