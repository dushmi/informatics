#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

const int MOD = 666013;

int T, P, G, Y;

vector <pair <int, int> > hash[MOD];

int lgput(int x, int p, int MOD) {
  int a = x, rez = 1;

  while (p) {
    if (p & 1)
      rez = (1LL * rez * a) % MOD;

    a = (1LL * a * a) % MOD;
    p >>= 1;
  }

  return rez;
}

void insert_hash(int val, int i) {
  hash[val % MOD].push_back(make_pair(val, i));
}

int query_hash(int val) {
  for (int j = 0; j < (int)hash[val % MOD].size(); ++j)
    if (hash[val % MOD][j].first == val)
      return hash[val % MOD][j].second;

  return -1;
}

int solve() {
  int sq = sqrt(P), vc = 1;
  
  if (sq * sq < P)
    ++sq;

  for (int i = 1; i <= sq; ++i) {
    vc = (1LL * vc * G) % P;
    insert_hash(vc, i);
  }

  int im = lgput(vc, P - 2, P), cc = Y;

  for (int i = 0; i <= sq; ++i) {
    int j = query_hash(cc);

    if (j != -1)
      return (i * sq + j) % (P - 1);

    cc = (1LL * cc * im) % P;
  }
}

void reset() {
  int vc = 1, sq = sqrt(P);

  if (sq * sq < P)
    ++sq;

  for (int i = 1; i <= sq; ++i) {
    vc = (1LL * vc * G) % P;
    hash[vc % MOD].clear();
  }
}

int main() {
  freopen("dlog.in", "r", stdin);
  freopen("dlog.out", "w", stdout);

  scanf("%d", &T);

  for (int i = 1; i <= T; ++i) {
    scanf("%d%d%d", &P, &G, &Y);

    if (Y == 1)
      printf("0\n");
    else
      printf("%d\n", solve());
  
    reset();
  }

  return 0;
}
