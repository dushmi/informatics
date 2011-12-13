#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

struct pct {
  int x, y;
};

const int N = 2005;

const double INF = 2000000000;

vector<int> v;

int n, m, dminm[N];
//n = nr centrale
//m = nr orase;

bool f[N];

pct c[N], town[N];

double d[N], minm[N];

void read() {
  scanf("%d%d", &n, &m);

  for (int i = 1; i <= n; ++i)
    scanf("%d%d", &c[i].x, &c[i].y);

  for (int i = 1; i <= m; ++i)
    scanf("%d%d", &town[i].x, &town[i].y);
}

double dist(double x1, double y1, double x2, double y2) {
  return (double)sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void init() {
  for (int j = 1; j <= m; ++j)
    d[j] = INF;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      d[j] = min(d[j], dist(c[i].x, c[i].y, town[j].x, town[j].y));

  for (int j = 1; j <= m + 1; ++j)
    minm[j] = INF;

  for (int j = 1; j <= m; ++j)
    if (d[j] < minm[m + 1])
      minm[m + 1] = d[j], dminm[m + 1] = j;

  double dc = 0;

  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= m; ++j) 
      if (i != j) {
        dc = dist(town[i].x, town[i].y, town[j].x, town[j].y);
        
        if (minm[i] > dc) {
          minm[i] = dc;
          dminm[i] = j;
        }
      }
}

void remake() {
  if (f[dminm[m + 1]]) {
    minm[m + 1] = INF;

    for (int j = 1; j <= m; ++j)
      if (!f[j] && minm[m + 1] > d[j]) {
        minm[m + 1] = d[j];
        dminm[m + 1] = j;
      }
  }

  double dc;

  for (int i = 1; i <= m; ++i)
    if (f[dminm[i]]) {
      minm[i] = INF;

      for (int j = 1; j <= m; ++j)
        if (!f[j] && i != j) {
          dc = dist(town[i].x, town[i].y, town[j].x, town[j].y);
          
          if (minm[i] > dc) {
            minm[i] = dc;
            dminm[i] = j;
          }
        }
    }

}

void solve() {
  double mc, ct = 0;
  
  int st, dmc;
  
  st = m + 1;
  v.push_back(st);
  f[st] = 1;
  mc = minm[st];
  dmc = dminm[st];
  
  for (int i = 1; i <= m; ++i) {
    v.push_back(dmc);
    f[dmc] = 1;
    ct += mc;

    remake();

    mc = INF;
    dmc = 0;

    for (int j = 0; j < (int)v.size(); ++j) 
      if (mc > minm[v[j]]) {
        mc = minm[v[j]];
        dmc = dminm[v[j]];
      }  
  }

  printf("%lf\n", ct);
}

int main() {
  freopen("retea2.in", "r", stdin);
  freopen("retea2.out", "w", stdout);

  read();

  init();

  solve();

  return 0;
}
