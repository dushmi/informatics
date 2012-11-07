#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 100005;

int ans, N, d[kMaxN];

vector <int> L[kMaxN];

void edit(int node, int dad) {
  for (size_t i = 0; i < L[node].size(); ++i)
    if (L[node][i] == dad) {
      swap(L[node][i], L[node][L[node].size() - 1]);
      L[node].pop_back();
    } 

  for (size_t i = 0; i < L[node].size(); ++i)
    edit(L[node][i], node);
}

bool comp(const int &x, const int &y) {
  return d[x] < d[y];
}

void compute(int node) {
  d[node] = 1;

  for (size_t i = 0; i < L[node].size(); ++i)
    compute(L[node][i]);

  sort(L[node].begin(), L[node].end(), comp);

  for (size_t i = 0; i < L[node].size(); ++i)
    if (d[L[node][i]] >= d[node])
      ++d[node];
}

inline void test(int &value, int &maximumValue, int x) {
  if (x >= value)
    ++value;
  else
    maximumValue = x;
}

void solve(int node, int dadValue) {
  int value = 1, maximumValue = -1;
  bool ok = 0;
  
  for (size_t i = 0; i < L[node].size(); ++i) {
    if (d[L[node][i]] > dadValue && !ok) {
      ok = 1;
      test(value, maximumValue, dadValue);
    }
    
    test(value, maximumValue, d[L[node][i]]);
  }

  if (!ok)
    test(value, maximumValue, dadValue);
  
  if (value > ans)
    ans = value;

  for (size_t i = 0; i < L[node].size(); ++i)
    if (d[L[node][i]] <= maximumValue)
      solve(L[node][i], value);
    else
      solve(L[node][i], value - 1);
}

int main() {
  assert(freopen("trib.in", "r", stdin));
  assert(freopen("trib.out", "w", stdout));

  //read the tree
  int x, y;
  assert(scanf("%d", &N) == 1);
  for (int i = 1; i < N; ++i) {
    assert(scanf("%d%d", &x, &y) == 2);
    L[x].push_back(y);
    L[y].push_back(x);
  }

  //remove the duplicate edges
  edit(1, 0);
  
  //compute d[i] = maximum table at which i sits if everybody
  //               from his sub-tree must come before him.
  compute(1);
  
  //solve for each node
  ans = d[1];
  solve(1, 0);
  printf("%d\n", ans);
  
  return 0;
}
