#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

vector <int> v;

vector <long long> d;

int n;

long long ans = -1;

bool ok(long long a, long long b, long long c) {
  return (a + b > c && a + c > b && b + c > a);
}

void solve(long long sum, long long dif) {
  if ((sum + dif) & 1)
    return;

  long long c = sum - (sum + dif) / 2, i = sum - c;

  if (ok(n, c, i) && (c < ans || ans == -1))
    ans = c;
}

int main() {
  assert(freopen("pitagora2.in", "r", stdin));
  assert(freopen("pitagora2.out", "w", stdout));

  assert(scanf("%d", &n) == 1);

  for (int i = 1; i * i <= n; ++i)
    if (n % i == 0) {
      d.push_back(i);

      if (n / i != i)
        d.push_back(n / i);
    }

  for (size_t i = 0; i < d.size(); ++i)
    for (size_t j = i; j < d.size(); ++j)
      if ((1LL * n * n) % (1LL * d[i] * d[j]) == 0)
      v.push_back(1LL * d[i] * d[j]);

  for (size_t i = 0; i < v.size(); ++i)
    solve(v[i], 1LL * n * n / v[i]);

  printf("%lld\n", ans);

  return 0;
}
