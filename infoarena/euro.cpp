#include <cstdio>
#include <utility>
#define LL long long

using namespace std;

const double eps = 0.0001;

const int N = 35000;

const LL INF =  ((LL)1 << 62);

LL t, st, dr, a[N], v[N], pf[N], s[N], d[N];

pair <LL, LL> dq[N];

void read() {
  scanf("%lld%lld", &a[0], &t);

  for (int i = 1; i <= a[0]; ++i)
    scanf("%lld", &a[i]);
}

void compress() {
  int s = 0;

  for (int i = 1; i <= a[0]; ++i) {
    s += a[i];

    if (s < 0) {
      v[++v[0]] = s;
      pf[++pf[0]] = i;
      s = 0;
    }
  }

  if (pf[pf[0]] == a[0])
    return;

  v[++v[0]] = s;
  pf[++pf[0]] = a[0];
}

void init() {
  for (int i = 1; i <= v[0]; ++i)
    s[i] = s[i - 1] + v[i];
}

inline double inters(pair <LL, LL> a, pair <LL, LL> b) {
  return 1.0 * (a.first - b.first) / (b.second - a.second);
}

inline LL max(LL x, LL y) {
  return x > y ? x : y;
}

void elimst(int time) {
  while (st < dr && inters(dq[st + 1], dq[st]) <= eps + time)
    ++st;
}

void elimdr(pair <LL, LL> c) {
  while (dr > st && inters(c, dq[dr]) < inters(dq[dr], dq[dr - 1]))
    --dr;

  dq[++dr] = c;
}

void solve() {
  st = dr = 1;
  dq[0] = make_pair(d[0], -s[0]);

  for (int i = 1; i < v[0]; ++i) {
    elimst(pf[i]);

    d[i] = s[i] * pf[i] - t + dq[st].first + dq[st].second * pf[i];
    
    elimdr(make_pair(d[i], -s[i]));
  }

  d[v[0]] = -INF;

  for (int i = 0; i < v[0]; ++i)
    d[v[0]] = max(d[v[0]], d[i] + (s[v[0]] - s[i]) * pf[v[0]] - t); 

  printf("%lld\n", d[v[0]]);
}

int main() {
  freopen("euro.in", "r", stdin);
  freopen("euro.out", "w", stdout);
  
  read();
  
  compress();

  init();

  solve();

  return 0;
}
