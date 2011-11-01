#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1005, INF = 1000000000;

int n, d[N][2], din[N][N];

vector <int> L[N];

void read() {
  int x;

  scanf("%d", &n);

  for (int i = 2; i <= n; ++i) {
    scanf("%d", &x);
    L[x].push_back(i);
  }
}

//d[i][0] = valoarea maxima pe care o pot obtine pe subarborele lui i, fara i
//d[i][1] = valoarea maxima pe care o pot obtine pe subarborele lui i, inclusiv i
//din[i][j] = valoarea maxima pe care o pot obtine formand grupe intre poz i si j
void solve(int nod) {
  vector <int> v;

  for (int i = 0; i < (int)L[nod].size(); ++i)
    v.push_back(L[nod][i]);
  
  sort(v.begin(), v.end());

  for (int i = (int)v.size() - 1; i >= 0; --i) {
    din[i][i] = max(d[v[i]][1], d[v[i]][0]);
    
    for (int j = i + 1; j < (int)v.size(); ++j)
      din[i][j] = max(max(v[j] - v[i] + d[v[j]][0] + d[v[i]][0] + din[i + 1][j - 1], 
                      max(d[v[i]][1], d[v[i]][0]) + din[i + 1][j]), max(d[v[j]][1], d[v[j]][0]) + din[i][j - 1]);
  }

  d[nod][0] = din[0][v.size() - 1];

  v.push_back(nod);

  sort(v.begin(), v.end());

  for (int i = (int)v.size() - 1; i >= 0; --i) {
    if (v[i] == nod) {
      din[i][i] = -INF;

      for (int j = i + 1; j < (int)v.size(); ++j)
        din[i][j] = max(v[j] - v[i] + d[v[j]][0] + din[i + 1][j - 1],
                        max(d[v[j]][1], d[v[j]][0]) + din[i][j - 1]);

      continue;
    }

    din[i][i] = max(d[v[i]][1], d[v[i]][0]);

    for (int j = i + 1; j < (int)v.size(); ++j)
      if (v[j] != nod)
        din[i][j] = max(max(v[j] - v[i] + d[v[j]][0] + d[v[i]][0] + din[i + 1][j - 1],
                        max(d[v[i]][1], d[v[i]][0]) + din[i + 1][j]), max(d[v[j]][1], d[v[j]][0]) + din[i][j - 1]);
      else
        din[i][j] = max(v[j] - v[i] + d[v[i]][0] + din[i + 1][j - 1],
                        max(d[v[i]][1], d[v[i]][0]) + din[i + 1][j]);
  }

  d[nod][1] = din[0][v.size() - 1];
}

void df(int nod) {
  if (L[nod].size() == 0) {
    d[nod][0] = 0;
    d[nod][1] = 0;
    
    return;
  }
  
  for (int i = 0; i < (int)L[nod].size(); ++i)
    df(L[nod][i]);

  solve(nod);
}

int main() {
  freopen("petsoft.in", "r", stdin);
  freopen("petsoft.out", "w", stdout);

  read();

  df(1);

  printf("%d\n", d[1][0]);

  return 0;
}
