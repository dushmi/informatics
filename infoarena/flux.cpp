#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

struct Edge {
  int x, y, c;

  Edge(int _x, int _y, int _c) {
    x = _x; y = _y; c = _c;
  }
};

const int kMaxN = 105;

vector <Edge> v;

vector <int> L[kMaxN];

bool used[kMaxN];

int N;

double gauss[kMaxN][kMaxN], init[kMaxN];

void read() {
  int M, x, y, c;

  assert(scanf("%d%d", &N, &M));

  for (int i = 0; i < M; ++i) {
    assert(scanf("%d%d%d", &x, &y, &c));
    v.push_back(Edge(x, y, c));
    L[x].push_back(y);
    L[y].push_back(x);
  }
}

void df(int nod) {
  used[nod] = 1;

  for (int i = 0; i < (int)L[nod].size(); ++i)
    if (!used[L[nod][i]])
      df(L[nod][i]);
}

void initGauss() {
  for (int i = 0; i < (int)v.size(); ++i) {
    ++gauss[v[i].x][v[i].x]; --gauss[v[i].x][v[i].y];
    ++gauss[v[i].y][v[i].y]; --gauss[v[i].y][v[i].x];
  }

  for (int i = 0; i <= N; ++i)
    gauss[1][i] = 0;

  gauss[1][1] = 1;
  gauss[N][0] = 1;
}

void _Gauss() {
  for (int j = 1; j <= N; ++j) {
    int i = 0;

    for (i = j; i <= N; ++i)
      if (gauss[i][j])
        break;
    
    if (i == N + 1)
      continue;

    if (i != j)
      swap(gauss[i], gauss[j]);
  
    for (i = i + 1; i <= N; ++i) {
      double x = - gauss[i][j] / gauss[j][j];

      for (int k = 0; k <= N; ++k)
        gauss[i][k] += x * gauss[j][k];
    }
  }

  for (int i = N; i >= 1; --i) 
    if (gauss[i][i] > 0.0001) {
      init[i] = gauss[i][0];
      for (int j = i + 1; j <= N; ++j)
        init[i] -= init[j] * gauss[i][j];  
      init[i] /= gauss[i][i];
    }
}

inline double modul(double x) {
  return x < 0 ? (-x) : x;
}

void solve() {
  double coef = -1;

  for (int i = 0; i < (int)v.size(); ++i) {
    double cc = v[i].c / modul(init[v[i].x] - init[v[i].y]);
      
    if (cc < coef || coef == -1)
      coef = cc;
  }

  printf("%lf\n", coef);
}

int main() {
  assert(freopen("flux.in", "r", stdin));
  assert(freopen("flux.out", "w", stdout));

  read();

  df(1);

  if (used[N]) {
    initGauss();
    _Gauss();

    solve();
    return 0;
  }

  printf("%lf\n", 0.0);

  return 0;
}
