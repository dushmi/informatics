#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

vector <pair <long long, int> > v;

long long N, A = 1, ans = 1;

void dfp(long long N) {
  for (int i = 2; 1LL * i * i <= N; ++i)
    if (N % i == 0) {
      int pc = 0;

      while (N % i == 0) {
        N /= i;
        ++pc;
      }

      v.push_back(make_pair(i, pc));
    }

  if (N > 1)
    v.push_back(make_pair(N, 1));
}

inline long long pow(long long x, int p) {
  long long rez = 1;

  for (int i = 1; i <= p; ++i)
    rez *= x;

  return rez;
}

void solve() {
  for (int i = 0; i < (int)v.size(); ++i) {
    if (v[i].second & 1)
      ans <<= 1;

    A *= pow(v[i].first, v[i].second / 2);
  }

  printf("%lld %lld\n", N / A, A);
  printf("%lld\n", ans);
}

int main() {
  assert(freopen("prodiv.in", "r", stdin));
  assert(freopen("prodiv.out", "w", stdout));

  scanf("%lld", &N);

  dfp(N);

  solve();

  return 0;
}
