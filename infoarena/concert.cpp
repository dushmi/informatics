#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

struct artist{
  int A, B, P, D1, D2;
};

const int kMaxN = 1005, coef = 2, INF = 0x3f3f3f3f;

int N, T[coef * kMaxN], d[kMaxN][coef * kMaxN][2];

artist v[kMaxN];

bool comp(artist x, artist y) {
  if (x.A < y.A)
    return 1;

  if (x.A > y.A)
    return 0;

  return x.B < y.B;
}

int main() {
  assert(freopen("concert.in", "r", stdin));
  assert(freopen("concert.out", "w", stdout));

  assert(scanf("%d", &N));

  for (int i = 1; i <= N; ++i) {
    assert(scanf("%d%d%d%d%d", &v[i].A, &v[i].B, &v[i].P, &v[i].D1, &v[i].D2));
    ++v[i].A; ++v[i].B;
    T[++T[0]] = v[i].A;
    T[++T[0]] = v[i].B;
  }

  sort(T + 1, T + T[0] + 1);

  sort(v + 1, v + N + 1, comp);

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= T[0]; ++j)
      for (int k = 0; k <= 1; ++k)
        d[i][j][k] = -INF;
  
  d[1][1][0] = 0;

  for (int i = 1; i <= N; ++i) 
    for (int j = 1; j <= T[0]; ++j) {
      if (d[i][j][0] != -INF) {
        d[i + 1][j][0] = max(d[i][j][0], d[i + 1][j][0]);
        
        if (v[i].A < T[j] && T[j] <= v[i].B)
          d[i][j][1] = max(d[i][j][1], d[i][j][0] - v[i].D1);
        else if (v[i].A == T[j])
          d[i][j][1] = max(d[i][j][1], d[i][j][0]);
      }

      if (d[i][j][1] != -INF) {
        if (T[j] < v[i].B)
          d[i + 1][j][0] = max(d[i + 1][j][0], d[i][j][1] - v[i].D2);
        else if (T[j] == v[i].B)
          d[i + 1][j][0] = max(d[i + 1][j][0], d[i][j][1]);

        if (v[i].A <= T[j + 1] && T[j + 1] <= v[i].B)
          d[i][j + 1][1] = max(d[i][j + 1][1], d[i][j][1] + v[i].P * (T[j + 1] - T[j]));
      }
    }

  int ans = 0;
  
  for (int j = 1; j <= T[0]; ++j)
    for (int k = 0; k <= 1; ++k)
      ans = max(ans, d[N + 1][j][k]);

  printf("%d\n", ans);

  return 0;
}
