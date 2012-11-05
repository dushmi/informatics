#include <cstdio>

const int kMaxN = 1000005;

int N, pos[kMaxN], aib[kMaxN];

void read() {
  int x;

  scanf("%d", &N);

  for (int i = 1; i <= N; ++i) {
    scanf("%d", &x);
    pos[x] = i;
  }
}

inline int bit(int x) {
  return (x & (-x));
}

void update_aib(int pos, int val) {
  while (pos <= N) {
    aib[pos] += val;
    pos += bit(pos);
  }
}

int query_aib(int pos) {
  int res = 0;

  while (pos) {
    res += aib[pos];
    pos -= bit(pos);
  }

  return res;
}

void init() {
  for (int i = 1; i <= N; ++i)
    update_aib(i, 1);
}

void solve() {
  long long S = pos[1];
  update_aib(pos[1], -1);

  for (int i = 2; i <= N; ++i)
    if (pos[i] > pos[i - 1]) {
      S += query_aib(pos[i]) - query_aib(pos[i - 1]);
      update_aib(pos[i], -1);
    } else {
      S += query_aib(pos[i])  + query_aib(N) - query_aib(pos[i - 1]);
      update_aib(pos[i], -1);
    }

  printf("%lld\n", S);
}

int main() {
  freopen("permsort.in", "r", stdin);
  freopen("permsort.out", "w", stdout);

  read();

  init();

  solve();

  return 0;
}
