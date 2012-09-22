#include <cstdio>
#include <bitset>
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

typedef int Huge[105];

const int kMaxL = 505, kMaxK = 105;

const double INF = 2000000000;

vector <int> primes;

Huge result;

double ans[2 * kMaxK], d[kMaxK][2 * kMaxK];

int K, pos[2 * kMaxK], pred[kMaxK][2 * kMaxK], req[kMaxK][2 * kMaxK];

void _Sieve_Of_Eratosthenes() {
  bitset <kMaxL> sieve;
  sieve[0] = sieve[1] = 1;
  primes.push_back(-1);

  for (int i = 1; i < kMaxL; ++i)
    if (!sieve[i]) {
      primes.push_back(i);

      for (int j = i * i; j < kMaxL; j += i)
        sieve[j] = 1;
    }
}

void init() {
  for (int i = 0; i < (int)primes.size(); ++i)
    for (int j = 0; j <= 2 * K; ++j)
      d[i][j] = INF;

  for (int j = 0; j <= 2 * K; ++j)
    ans[j] = INF;
}

void multiply(Huge A, int x) {
  int i = 1, T = 0;

  for (i = 1; i <= A[0] || T; ++i) {
    A[i] = A[i] * x + T;
    T = A[i] / 10;
    A[i] %= 10;
  }

  A[0] = i - 1;
}

void rebuild(int i, int j) {
  if (i == 1)
    return;

  for (int k = 1; k <= req[i][j]; ++k)
    multiply(result, primes[i]);
  //fprintf(stderr, "Required %d of %d to get from %lf, %d %d to %lf, %d %d\n", req[i][j], primes[i], d[i][j], i, j, d[i - 1][pred[i][j]], i - 1, pred[i][j]);
  
  rebuild(i - 1, pred[i][j]);
}

void print(Huge A) {
  for (int i = A[0]; i >= 1; --i)
    printf("%d", A[i]);
}

int main() {
  assert(freopen("trapeze.in", "r", stdin));
  assert(freopen("trapeze.out", "w", stdout));

  assert(scanf("%d", &K) == 1);

  _Sieve_Of_Eratosthenes(); 

  // d[i][j] = smallest number which has only one factor of 2, all prime divisors lesser than 
  //           the i-th prime number and j divisors overall
  init();
  d[1][2] = log10(2);
  ans[2] = log10(2);

  for (int i = 1; i < (int)primes.size() - 1; ++i)
    for (int j = 1; j <= 2 * K; ++j)
      if (d[i][j] != INF) {
        double val = d[i][j];
        
        for (int k = 1; j * k <= 2 * K; ++k) {
          if (d[i + 1][j * k] > val) {
            d[i + 1][j * k] = val, pred[i + 1][j * k] = j, req[i + 1][j * k] = k - 1;
            
            if (ans[j * k] > d[i + 1][j * k]) {
              ans[j * k] = d[i + 1][j * k];
              pos[j * k] = i + 1;
            }
          }
          
          val += log10(primes[i + 1]);
        }
      }
  
  result[++result[0]] = 1;
  rebuild(pos[2 * K], 2 * K);
  
  print(result);

  return 0;
}
