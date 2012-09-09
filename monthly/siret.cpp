#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>

using namespace std;

const int kMaxN = 305;

int N, in[kMaxN], length[kMaxN], prev[kMaxN], sorted[kMaxN], d[kMaxN][kMaxN];

vector <int> L[kMaxN];

void sortaret() {
  queue <int> Q;
  
  for (int i = 1; i <= N; ++i)
    if (in[i] == 0) {
      Q.push(i);

    while (!Q.empty()) {
      int nc = Q.front(); Q.pop();

      sorted[++sorted[0]] = nc;

      for (size_t i = 0; i < L[nc].size(); ++i) {
        --in[L[nc][i]];

        if (in[L[nc][i]] == 0)
          Q.push(L[nc][i]);
      }
    }
  }
}

void print(int x) {
  if (x == 0)
    return;

  printf("%d ", sorted[x]);
  print(prev[x]);
}

void scmax() {
  sorted[0] = N + 1;

  for (int i = 1; i <= N; ++i)
    for (int j = 0; j < i; ++j)
      if (sorted[i] < sorted[j] && length[j] + 1 > length[i]) {
        length[i] = length[j] + 1;
        prev[i] = j;
      }

  int ans = 0, pos = 0;

  for (int i = 1; i <= N; ++i)
    if (length[i] > ans) {
      ans = length[i];
      pos = i;
    }
  
  printf("%d\n", ans);

  print(pos);
}

int main() {
  assert(freopen("siret.in", "r", stdin));
  assert(freopen("siret.out", "w", stdout));

  int M;

  assert(scanf("%d%d", &N, &M) == 2);

  for (int i = 1; i <= M; ++i) {
    int x, y;
    assert(scanf("%d%d", &x, &y) == 2);
    d[x][y] = d[y][x] = 1;
  }

  for (int i = 1; i <= N; ++i)
    for (int j = i + 1; j <= N; ++j)
      if (d[i][j]) {
        L[j].push_back(i);
        ++in[i];
      } else {
        L[i].push_back(j);
        ++in[j];
      }
   
  sortaret();

  scmax();

  return 0;
}
