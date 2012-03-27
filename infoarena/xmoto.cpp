#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct tronson {
  double a, b, k, q, v;
};

const int N = 50005;

const double eps = 0.0000001;

tronson T[N];

int n;

vector <double> sol;

double lim, Sa[N], Sb[N], Sk[N], Sq[N];

void read() {
  scanf("%d%lf", &n, &lim);

  for (int i = 1; i <= n; ++i) 
    scanf("%lf%lf%lf%lf%lf", &T[i].a, &T[i].b, &T[i].k, &T[i].q, &T[i].v);
}

bool comp(tronson a, tronson b) {
  return a.v < b.v;
}

void init() {
  sort(T + 1, T + n + 1, comp);

  for (int i = 1; i <= n; ++i) {
    Sa[i] = Sa[i - 1] + T[i].a;
    Sb[i] = Sb[i - 1] + T[i].b;
    Sk[i] = Sk[i - 1] + T[i].k;
    Sq[i] = Sq[i - 1] + T[i].q;
  }

  T[0].v = 0;
  T[n + 1].v = 10000;
}

double modul(double x) {
  return x < 0 ? (-x) : x;
}

void solve() {
  for (int i = 0; i <= n; ++i) {
    double sc = lim;
    sc -= (Sq[i] + (Sk[n] - Sk[i]));
    sc /= (Sb[i] + (Sa[n] - Sa[i]));
    
    if (sc > T[i].v && (sc < T[i + 1].v || modul(sc - T[i + 1].v) < eps))
      sol.push_back(sc);
  }

  printf("%d\n", sol.size());

  for (int i = 0; i < (int)sol.size(); ++i)
    printf("%lf\n", sol[i]);
}

int main() {
  freopen("xmoto.in", "r", stdin);
  freopen("xmoto.out", "w", stdout);

  read();

  init();

  solve();

  return 0;
}
