#include <cstdio>
#include <vector>

using namespace std;

const int N = 1000005, INF = 2000000005;

int dr, n, stack[N], a[N], f[N], pos[N], s[N], sz[N];

vector <int> elim[N];

inline int number(char ch[15]) {
  int x = 0, pos = 0; 
  
  while (ch[pos] >= '0' && ch[pos] <= '9')
    x =  x * 10 + ch[pos++] - '0';
  
  return x;
}

void read() {
  char s[15];

  fgets(s, sizeof(s), stdin);
  n = number(s);
  
  for (int i = 1; i <= n; ++i) {
    fgets(s, sizeof(s), stdin);
    a[i] = number(s);
  }
}

void insert_stack(int pos) {
  while (dr >= 1 && a[stack[dr]] <= a[pos]) {
    elim[pos].push_back(stack[dr]);
    --dr;
  }
  
  sz[pos] = elim[pos].size();
  stack[++dr] = pos;
}

void solve() {
  long long res = 0;
  int ind;

  dr = 0;
  f[0] = 1;

  for (int i = 1; i <= n; ++i) {
    insert_stack(i);
    ind = f[i] = stack[dr - 1];
    if (dr - 1 == 0)
      f[i] = 1;

    while (pos[ind] < sz[ind] && a[elim[ind][pos[ind]]] < a[i])
      ++pos[ind];

    if (pos[ind] < sz[ind])
      s[i] = elim[ind][pos[ind]];
    else
      s[i] = f[ind];
  }
  
  for (int i = 2; i <= n; ++i)
    res += 1LL * (i - f[i]) * (n - i + f[i] - 1) + 1LL * (i - f[i] - 1) * (i - f[i] - 1) + (i - s[i] - 1);

  printf("%lld\n", res);
}

int main() {
  freopen("turnuri.in", "r", stdin);
  freopen("turnuri.out", "w", stdout);

  read();

  solve();

  return 0;
}
