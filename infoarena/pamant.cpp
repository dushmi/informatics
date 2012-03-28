#include <cstdio>
#include <vector>

using namespace std;

const int N = 100005;

int n, nrc, low[N], lvl[N], rep[N];

bool critf[N];

vector <int> crit, L[N];

void read() {
  int m, x, y;

  scanf("%d%d", &n, &m);

  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    
    L[x].push_back(y);
    L[y].push_back(x);
  }
}

void df(int node, int dad, int lvlc) {
  int nrchilds = 0;

  lvl[node] = low[node] = lvlc;

  for (int i = 0; i < (int)L[node].size(); ++i) {
    if (L[node][i] == dad)
      continue;

    if (lvl[L[node][i]] == -1) {
      df(L[node][i], node, lvlc + 1);

      ++nrchilds;

      low[node] = min(low[node], low[L[node][i]]);

      if (low[L[node][i]] >= lvl[node] && dad != 0)
        critf[node] = 1;
    } else
      low[node] = min(low[node], lvl[L[node][i]]);
  }

  if (dad == 0 && nrchilds > 1)
    critf[node] = 1;
}

void print() {
  printf("%d\n", nrc);

  for (int i = 1; i <= nrc; ++i)
    printf("%d ", rep[i]);
  printf("\n");
  
  for (int i = 1; i <= n; ++i)
    if (critf[i])
      crit.push_back(i);

  printf("%d\n", (int)crit.size());

  for (int i = 0; i < (int)crit.size(); ++i)
    printf("%d ", crit[i]);
  printf("\n");
}

int main() {
  freopen("pamant.in", "r", stdin);
  freopen("pamant.out", "w", stdout);

  read();

  for (int i = 1; i <= n; ++i)
    lvl[i] = -1;

  for (int i = 1; i <= n; ++i) 
    if (lvl[i] == -1) {
      ++nrc;
      rep[nrc] = i;

      df(i, 0, 0);
    }

  print();

  return 0;
}
