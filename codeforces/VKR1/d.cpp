#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

const int N = 50005, K = 505;

int n, k, d[N][K];

vector <int> L[N];

long long sol;

bool used[N];

void read() {
  int x, y;

  scanf("%d%d", &n, &k);

  for (int i = 1; i < n; ++i) {
    scanf("%d%d", &x, &y);
    L[x].push_back(y);
    L[y].push_back(x);
  }
}

void df(int nod) {
  used[nod] = 1;
  d[nod][0] = 1;

  for (int i = 0; i < (int)L[nod].size(); ++i)
    if (!used[L[nod][i]]) {
      df(L[nod][i]);
      
      for (int j = 0; j <= k; ++j)
        sol += (long long)d[L[nod][i]][j - 1] * d[nod][k - j];

      for (int j = 1; j <= k; ++j)
        d[nod][j] += d[L[nod][i]][j - 1];
    }
}

int main() {
  read();
  
  df(1);

  cout << sol;

  return 0;
}
