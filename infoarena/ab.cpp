#include <cstdio>
#include <algorithm>

using namespace std;

const int K = 1005, N = 30005, INF = 0x3f3f3f3f;

int m, n, k, price[K], last[N];

void read() {
  scanf("%d%d%d", &m, &n, &k);

  for (int i = 1; i <= k; ++i)
    scanf("%d", &price[i]);

  scanf("%d", &last[1]);

  int x;

  for (int i = 2; i <= m; ++i) {
    scanf("%d", &x);
    last[i] = last[i - 1] + x;
  }
}

void solve() {
  int rez = INF;
  
  sort(price + 1, price + k + 1);

  if (k == 2) {
    printf("%d\n", max(m + (n - last[m]), last[m]) * price[1] + min(m + (n - last[m]), last[m]) * price[2]);

    return;
  }

  for (int nra = 0; nra <= m; ++nra)
    rez = min(rez, (nra + (n - last[nra])) * price[1] + max(last[nra], m - nra) * price[2] + min(last[nra], m - nra) * price[3]); 

  printf("%d\n", rez);
}

int main() {
  freopen("ab.in", "r", stdin);
  freopen("ab.out", "w", stdout);

  int t;

  scanf("%d", &t);

  for (int i = 1; i <= t; ++i) {
    read();

    solve();
  }

  return 0;
}
