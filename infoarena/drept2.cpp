#include <cstdio>
#include <utility>

using namespace std;

const int N = 2000200;

int maxst, maxdr, minst, mindr, a, b, n, m, pi[N], pf[N], maxdq[N], mindq[N];

long long rez;

void read() {
  scanf("%d%d%d%d", &m, &n, &a, &b);

  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &pi[i], &pf[i]);
    pf[i] += pf[i - 1];
  }

  for (int i = 1; i <= n; ++i)
    pf[i] = pi[i] + pf[i] - 1;
}

void max_elim_dr(int poz) {
  while (maxdr >= maxst && pi[poz] > pi[maxdq[maxdr]])
    --maxdr;

  maxdq[++maxdr] = poz;
}

void max_elim_st(int poz) {
  if (maxst <= maxdr && poz - maxdq[maxst] >= a)
    ++maxst;
}

void min_elim_dr(int poz) {
  while (mindr >= minst && pf[poz] < pf[mindq[mindr]])
    --mindr;

  mindq[++mindr] = poz;
}

void min_elim_st(int poz) {
  if (minst <= mindr && poz - mindq[minst] >= a)
    ++minst;
}

void solve() {
  maxst = 1; maxdr = 0;
  minst = 1; mindr = 0;

  for (int i = 1; i < a; ++i) {
    max_elim_dr(i);
    min_elim_dr(i);
  }

  for (int i = a; i <= n; ++i) {
    max_elim_st(i);
    max_elim_dr(i);

    min_elim_st(i);
    min_elim_dr(i);
    
    //fprintf(stderr, "%d : %d %d WAIT FOR IT ", i, pi[maxdq[maxst]], pf[mindq[minst]]);

    if (pf[mindq[minst]] - pi[maxdq[maxst]] + 1 >= b)
      rez = rez + pf[mindq[minst]] - pi[maxdq[maxst]] + 1 - b + 1;
    
    //fprintf(stderr, "%d\n", rez);
  }
}

int main() {
  freopen("drept2.in", "r", stdin);
  freopen("drept2.out", "w", stdout);

  read();

  solve();
  
  if (a != b) {
    swap(a, b);
    solve();
  }
  
  printf("%lld\n", rez);

  return 0;
}

