#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 515;

struct zmeu {
  int a, b, f, r;
};

int n, mg, rmax, poz[N], force[N], risk[N], d[N];

zmeu v[N];

vector <int> ev;

void read() {
  scanf("%d%d", &n, &rmax);

  for (int i = 1; i <= n; ++i)
    scanf("%d%d%d%d", &v[i].a, &v[i].b, &v[i].f, &v[i].r);
}

int din(int t1, int t2) {
  int nr = 0;

  for (int i = 1; i <= n; ++ i) 
    if (v[i].a <= t1 && t2 <= v[i].b) {
      force[++nr] = v[i].f;
      risk[nr] = v[i].r;
    }


  d[0] = 0;

  for (int j = 1; j <= rmax; ++j)
    d[j] = -1;
  
  for (int i = 1; i <= nr; ++i)
    for (int j = rmax - risk[i]; j >= 0; --j)
      if (d[j] >= 0 && d[j] + force[i] > d[j + risk[i]])
        d[j + risk[i]] = d[j] + force[i];

  int rez = 0;

  for (int j = 0; j <= rmax; ++j)
    rez = max(rez, d[j]);
  
  return rez;
}

void solve() {
  long long ft = 0;

  for (int i = 1; i <= n; ++i) {
    ev.push_back(v[i].a);
    ++v[i].b;
    ev.push_back(v[i].b);
  }

  sort(ev.begin(), ev.end());

  for (int i = 0; i < (int)ev.size() - 1; ++i)
    if (ev[i] < ev[i + 1])
      ft += (long long)din(ev[i], ev[i + 1]) * (ev[i + 1] - ev[i]);

  printf("%lld", ft);
}

int main() {
  freopen("praslea.in", "r", stdin);
  freopen("praslea.out", "w", stdout);

  read();

  solve();

  return 0;
}
