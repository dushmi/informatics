#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 100005;

int n, m, x, y;

pair <int, int> a[N], b[N];

void read() {
  scanf("%d%d%d%d", &n, &m, &x, &y);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i].first);
    a[i].second = i;
  }

  for (int i = 1; i <= m; ++i) {
    scanf("%d", &b[i].first);
    b[i].second = i;
  }
}

vector <pair <int, int> > sol;

void solve() {
  sort(a + 1, a + n + 1);

  sort(b + 1, b + m + 1);

  for (int i = 1, j = 1; i <= n && j <= m;)
    if (a[i].first - x > b[j].first)
      ++j;
    else if (a[i].first + y < b[j].first)
      ++i;
    else {
      sol.push_back(make_pair(a[i].second, b[j].second));
      ++i;
      ++j;
    }

  printf("%d\n", (int)sol.size());

  for (int i = 0; i < (int)sol.size(); ++i)
    printf("%d %d\n", sol[i].first, sol[i].second);
}

int main() {
  read();
  
  solve();

  return 0;
}
