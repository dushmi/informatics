#include <cstdio>
#include <vector>
#include <set>

using namespace std;

const int N = 50105, INF = 2147483647;

int n, m, d[N], val[N];

vector <int> L[N];

struct special_set {
  multiset <int> S;
  
  int res;

  special_set(int x) {
    res = INF;
    S.insert(x);
  }

  void change(multiset <int> :: iterator x) {
    res = min(res, *x - *(--x));
  }
};

void read() {
  int dad;

  scanf("%d%d", &n, &m);
  
  for (int i = 2; i <= n; ++i) {
    scanf("%d", &dad);
    L[dad].push_back(i);
  }

  for (int i = n - m + 1; i <= n; ++i)
    scanf("%d", &val[i]);
}

special_set* dfs(int node) {
  if (node >= n - m + 1) {
    d[node] = INF;

    return new special_set(val[node]);
  }

  special_set *now = dfs(L[node][0]);

  for (int i = 1; i < (int)L[node].size(); ++i) {
    special_set *add = dfs(L[node][i]);

    if (add->S.size() > now->S.size())
      swap(add, now);

    for (multiset <int> :: iterator it = add->S.begin(), bs; it != add->S.end(); ++it) {
      bs = now->S.insert(*it);

      if (bs != now->S.begin())
        now->change(bs);
      
      ++bs;

      if (bs != now->S.end())
        now->change(bs);
    }

    delete add;
  }

  d[node] = now->res;

  return now;
}

void solve() {
  dfs(1);

  for (int i = 1; i < n - m + 1; ++i)
    printf("%d ", d[i]);
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("data.in", "r", stdin);
#endif

  read();

  solve();

  return 0;
}
