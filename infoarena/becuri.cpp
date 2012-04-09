#include <cstdio>
#include <vector>

using namespace std;

const int N = 505;

bool dif[N], mat[N][N];

vector <int> l[2], c[2];

int n, m;

void read() {
  int x;
  
  scanf("%d%d", &n, &m);

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &x);

      if (x)
        mat[i][j] = 1;
    } 
}

bool eq(bool a[N], bool b[N], bool x) {
  for (int i = 1; i <= m; ++i)
    if (a[i] != (b[i] ^ x))
      return 0;

  return 1;
}

bool verif() {
  for (int i = 1; i <= n; ++i)
    if (eq(mat[i], mat[1], 0))
      dif[i] = 0;
    else if (eq(mat[i], mat[1], 1))
      dif[i] = 1;
    else
      return 0;

  return 1;
}

inline int max(int x, int y) {
  return x < y ? y : x; 
}

int solve(bool x) {
  for (int i = 1; i <= n; ++i)
    if (dif[i] == !x)
      l[x].push_back(i);

  for (int j = 1; j <= m; ++j)
    if (mat[1][j] ^ x)
      c[x].push_back(j);

  if ((l[x].size() & 1) != (c[x].size() & 1))
    return -1;

  return max(l[x].size(), c[x].size());
}

void print(bool x, int rez) {
  if (rez == 0)
    return;

  if ((int)l[x].size() == 0)
    l[x].push_back(1);

  if ((int)c[x].size() == 0)
    c[x].push_back(1);

  for (int i = 0; i < rez; ++i)
    if (i >= (int)l[x].size())
      printf("%d %d\n", l[x][(int)l[x].size() - 1], c[x][i]);
    else if (i >= (int)c[x].size())
      printf("%d %d\n", l[x][i], c[x][(int)c[x].size() - 1]);
    else
      printf("%d %d\n", l[x][i], c[x][i]);
}

void solve() {
  if (!verif()) {
    printf("-1\n");
    return;
  }

  int r1 = solve(0), r2 = solve(1);

  if (r1 == -1 && r2 == -1) {
    printf("-1\n");
    return;
  }

  if (r1 == -1) {
    printf("%d\n", r2);
    print(1, r2);
    return;
  }
  
  if (r2 == -1) {
    printf("%d\n", r1);
    print(0, r1);
    return;
  }

  if (r1 < r2) {
    printf("%d\n", r1);
    print(0, r1);
    return;
  } 

  printf("%d\n", r2);
  print(1, r2);
}

int main() {
  freopen("becuri.in", "r", stdin);
  freopen("becuri.out", "w", stdout);

  read();

  solve();

  return 0;
}
