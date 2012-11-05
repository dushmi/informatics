#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

const int N = 100005;

pair <int, int> v[N];

multiset <int> s;

int n, k;

void read() {
  scanf("%d%d", &n, &k);
  
  for (int i = 1; i <= n; ++i)
    scanf("%d%d", &v[i].first, &v[i].second);
}

bool comp(pair <int, int> a, pair <int, int> b) {
  return a.second < b.second;
}

void init() {
  sort(v + 1, v + n + 1, comp);

  for (int i = 1; i <= k; ++i)
    s.insert(0);
}

void solve() {
  int rez = 0;
  
  multiset <int> :: iterator it;


  for (int i = 1; i <= n; ++i) {
    it = s.lower_bound(v[i].first);
  
    if (it != s.end() && *it == v[i].first) {
      s.erase(it);
      s.insert(v[i].second);
      ++rez;
    } else {
      if (it == s.begin())
        continue;

      --it;

      s.erase(it);
      s.insert(v[i].second);
      ++rez;
      
    }
  }

  printf("%d\n", rez);
}

int main() {
  freopen("planificare.in", "r", stdin);
  freopen("planificare.out", "w", stdout);

  read();

  init();

  solve();

  return 0;
}
