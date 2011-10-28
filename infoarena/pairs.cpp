#include <cstdio>

const int N = 1000005;

int n, mv, f[N], nbf[N];

bool sieve[N], fsq[N];

void read() {
  int x;

  scanf("%d", &n);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    ++f[x];

    if (x > mv)
      mv = x;
  }
}

//sieve[i] = 1 if i is prime or 0 otherwise
//nbf[i] = number of different prime factors of i
//fsq[i] = 1 if i is free of cubes or 0 otherwise
void sieve_of_eratosthenes() {
  for (int i = 2; i <= mv; ++i)
    fsq[i] = 1;

  for (int i = 2; i <= mv; ++i)
    if (!sieve[i]) {
      for (int j = i; j <= mv; j += i) {
        if (j != i)
          sieve[j] = 1;
        
        ++nbf[j];
        
        if ((j / i) % i == 0)
          fsq[j] = 0;
      }
    }
}

void solve() {
  long long result = (long long)n * (n - 1) / 2;
  int c;

  for (int i = 2; i <= mv; ++i)
    if (fsq[i]) {
      c = 0;

      for (int j = i; j <= mv; j += i)
        c += f[j];
      
      if (nbf[i] & 1)
        result -= (long long)c * (c - 1) / 2;
      else
        result += (long long)c * (c - 1) / 2;
    }

  printf("%lld\n", result);
}

int main() {
  freopen("pairs.in", "r", stdin);
  freopen("pairs.out", "w", stdout);

  read();
  
  sieve_of_eratosthenes();

  solve();

  return 0;
}
