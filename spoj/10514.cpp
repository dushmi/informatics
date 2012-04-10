#include <cstdio>
#include <algorithm>

using namespace std;

struct building {
  int height, tax;

  bool operator<(const building &other) const {
    return height < other.height;
  }
};

const int N = 10005, INF = 0x3f3f3f3f;

building towers[N];

int n, sum[N][2], S[N];

void read() {
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i)
    scanf("%d", &towers[i].height);
  
  for (int i = 1; i <= n; ++i)
    scanf("%d", &towers[i].tax);
}

// sum[i][0] = total tax to make all towers before i of height 0
// sum[i][1] = total tax to make all towers before i of height hmax
void init() {
  sort(towers + 1, towers + n + 1);

  for (int i = 1; i <= n; ++i) {
    S[i] = S[i - 1] + towers[i].tax;
    sum[i][0] = sum[i - 1][0] + towers[i].height * towers[i].tax;
    sum[i][1] = sum[i - 1][1] + (towers[n].height - towers[i].height) * towers[i].tax;
  }
}

void solve() {
  int ans = INF;

  for (int i = 1; i <= n; ++i)
    ans = min(ans, sum[i - 1][1] + (towers[n].height - towers[i].height) * S[i - 1] + sum[n][0] - sum[i][0] + towers[i].height * (S[n] - S[i]));

  printf("%d\n", ans);
}

int main() {
  int T;

  scanf("%d", &T);
  
  for (int i = 1; i <= T; ++i) {
    read();

    init();

    solve();
  }

  return 0;
}
