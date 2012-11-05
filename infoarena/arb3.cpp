#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

const int kMaxN = 100005, INF = (1LL << 31) - 1;

vector <int> L[kMaxN], SP[kMaxN];

int N, M, value[kMaxN], father[kMaxN];

void read() {
  scanf("%d%d", &N, &M);

  for (int i = 2; i <= N; ++i) {
    scanf("%d", &father[i]);
    L[father[i]].push_back(i);
  }

  for (int i = 1; i <= N; ++i)
    scanf("%d", &value[i]);
}

inline bool comp(const int &x, const int &y) {
  return value[x] < value[y];
}

void init() {
  value[0] = -INF;

  for (int i = 1; i <= N; ++i) {
    L[i].push_back(0);
    sort(L[i].begin(), L[i].end(), comp);
  }

  for (int i = 1; i <= N; ++i) 
    if (!L[i].empty()) {
      SP[i].push_back(value[L[i][0]]);

      for (int j = 1; j < (int)L[i].size(); ++j)
        SP[i].push_back(SP[i][j - 1] + value[L[i][j]]);
    }
}

int binary_search(int node, int x) {
  int pas = (1 << 16), i = 0;

  for (i = 0; pas; pas >>= 1) 
    if (i + pas < (int)L[node].size() && value[L[node][i + pas]] <= x)
      i += pas;

  return i;
}

int change(int node, int child, int nb) {
  int pos = binary_search(node, value[child]), length = L[node].size() - 1, res = nb;

  res += (SP[node][length] - SP[node][pos]) - value[child] * (length - pos) + (length - pos) * nb;

  int posn = binary_search(node, value[child] - nb + 1);
  
  res += (SP[node][pos - 1] - SP[node][posn]) - (value[child] - nb + 1) * (pos - 1 - posn);
  
  return res;
}

int go_back(int node, int child, int nb) {
  if (node == 0)
    return nb;
  return go_back(father[node], node, change(node, child, nb));
}

void solve() {
  int x, y;

  for (int i = 1; i <= M; ++i) {
    scanf("%d%d", &x, &y);
    printf("%d\n", go_back(father[x], x, y));
  }
}

int main() {
  freopen("arb3.in", "r", stdin);
  freopen("arb3.out", "w", stdout);

  read();

  init();
  
  solve();

  return 0;
}
