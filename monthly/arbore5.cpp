#include <cstdio>
#include <vector>

using namespace std;

const int N = 100005;

vector <int> L[N];

int sol;

bool used[N], nr[N];

void read() {
  int n, m, x, y;

  scanf("%d%d", &n, &m);
  
  for (int i = 1; i < n; ++i) {
    scanf("%d%d", &x, &y);
    L[x].push_back(y);
    L[y].push_back(x);
  }

  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    nr[x] ^= 1;
    nr[y] ^= 1;
  }
}

int df(int nod) {
  used[nod] = 1;

  for (int j = 0; j < L[nod].size(); ++j)
    if (!used[L[nod][j]]) {
      df(L[nod][j]);
      nr[nod] ^= nr[L[nod][j]];
    }

  if (nr[nod] == 0 && nod != 1)
    ++sol;
}

int main() {
  freopen("arbore5.in", "r", stdin);
  freopen("arbore5.out", "w", stdout);

  read();

  df(1);

  printf("%d\n", sol);

  return 0;
}
