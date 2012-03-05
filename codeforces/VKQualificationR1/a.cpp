#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 55;

int n, k, a[N];

int main() {
  scanf("%d%d", &n, &k);

  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  
  sort(a + 1, a + n + 1);

  int lim = a[n - k + 1] > 0 ? a[n - k + 1] : 1, ans = 0;
  
  for (int i = 1; i <= n; ++i)
    if (a[i] >= lim)
      ++ans;

  printf("%d", ans);

  return 0;
}
