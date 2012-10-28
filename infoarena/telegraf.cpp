#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 38, INF = 2000000000;

vector <int> fr;

int ans = INF, d[kMaxN][kMaxN][kMaxN][kMaxN];

inline bool comp(const int &a, const int &b) {
  return a > b;
}

int main() {
  assert(freopen("telegraf.in", "r", stdin));
  assert(freopen("telegraf.out", "w", stdout));

  for (int i = 1; i <= 36; ++i) {
    int x;
    assert(scanf("%d", &x) == 1);
    
    if (x)
      fr.push_back(x);
  }

  sort(fr.begin(), fr.end(), comp);
  
  for (int lvl = 0; lvl < kMaxN; ++lvl)
    for (int sol = 0; sol < kMaxN; ++sol)
      for (int pn = 0; pn < kMaxN; ++pn)
        for (int cn = 0; cn < kMaxN; ++cn)
          d[lvl][sol][pn][cn] = INF;

  d[0][0][0][1] = 0;

  int N = (int)fr.size();
  
  for (int lvl = 0; lvl < kMaxN - 1; ++lvl)
    for (int sol = 0; sol <= N; ++sol)
      for (int pn = 0; pn <= N; ++pn)
        for (int cn = 0; cn <= N; ++cn)
          if (d[lvl][sol][pn][cn] != INF) {
            if (pn >= 1 && d[lvl][sol + 1][pn - 1][cn] > d[lvl][sol][pn][cn] + fr[sol] * (lvl - 1))
              d[lvl][sol + 1][pn - 1][cn] = d[lvl][sol][pn][cn] + fr[sol] * (lvl - 1);
          
            if (pn + cn <= N && d[lvl + 1][sol][pn + cn][pn] > d[lvl][sol][pn][cn])
              d[lvl + 1][sol][pn + cn][pn] = d[lvl][sol][pn][cn];
          }
  
  for (int lvl = 0; lvl < kMaxN; ++lvl)
    ans = min(ans, d[lvl][N][0][0]);

  printf("%d\n", ans);

  return 0;
}
