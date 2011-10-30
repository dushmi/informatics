#include <cstdio>

const int N = 2005, MOD = 19997;

int n, k, val[N];

int solve(int n) {
  if (val[n] != 0)
    return val[n];

  int result = 0, aux = 1, lastd = 1;

  if (n < k) {
    for (int d = 2; d <= n; ++d)
      if (k % d == 0) {
        for (int i = n - lastd; i >= n - d + 1; --i) 
          aux = (aux * i) % MOD;
        
        result = (result + aux * solve(n - d)) % MOD; 

        lastd = d;
      }

    val[n] = (solve(n - 1) + result) % MOD;

    return val[n];
  }

  for (int d = 2; d <= k; ++d)
    if (k % d == 0) {
      for (int i = n - lastd; i >= n - d + 1; --i) 
        aux = (aux * i) % MOD;

      result = (result + aux * solve(n - d)) % MOD;

      lastd = d;
    }

  val[n] = (solve(n - 1) + result) % MOD;

  return val[n];
}

int main() {
  freopen("cifru.in", "r", stdin);
  freopen("cifru.out", "w", stdout);

  scanf("%d%d", &n, &k);
  
  val[0] = val[1] = 1;

  printf("%d\n", solve(n));

  return 0;
}
