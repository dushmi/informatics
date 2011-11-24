#include <fstream>

using namespace std;

ifstream in("kreg.in");
ofstream out("kreg.out");

int l, k, n;

char s[10000000];

inline void add(int x) {
  if (x == 0)
    return;

  add(x / 10);
  s[l++] = x % 10 + '0';
}

void solve() {
  int next;

  k /= 2;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= k; ++j) {
      next = i + j;

      if (next > n)
        next -= n;

      add(i);
      s[l++] = ' ';
      add(next);
      s[l++] = '\n';
    }
 
  printf("%s", s);
}

int main() {
  freopen("kreg.in", "r", stdin);
  freopen("kreg.out", "w", stdout);
  
  scanf("%d%d", &k, &n);

  solve();

  return 0;
}
