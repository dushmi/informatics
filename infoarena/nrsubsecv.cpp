#include <cstdio>

const int N = 1000005, INF = 0x3f3f3f3f;

long long sum[N];

int n, m, st, a[N], nrst[N], nrdr[N], s[N], stack[N];

inline int min(int x, int y) {
  return x < y ? x : y;
}

inline int max(int x, int y) {
  return x > y ? x : y;
}

void read() {
  char s[7 * N];
  int poz = 0;

  scanf("%d%d\n", &n, &m);

  fgets(s, sizeof(s), stdin);

  for (int i = 1; i <= n; ++i) {
    while (s[poz] >= '0' && s[poz] <= '9')
      a[i] = a[i] * 10 + s[poz++] - '0';
    ++poz;

    ++a[i];
  }
}

void insert_stack(int val, int poz) {
  while (st > 0 && a[stack[st]] >= val)
    --st;

  stack[++st] = poz;
}

int query_stack(int val) {
  int pas = 1 << 20, i = 0;

  for (i = 0; pas; pas >>= 1)
    if (i + pas <= st && a[stack[i + pas]] <= val)
      i += pas;
  
  return stack[i];
}

void init() {
  a[n + 1] = 0;
  st = 0;
  stack[++st] = n + 1;

  for (int i = n; i >= 1; --i) {
    nrdr[i] = query_stack(a[i] - 1) - i;
    insert_stack(a[i], i);
  }

  a[0] = INF;
  st = 0;
  stack[++st] = 0;
  
  for (int i = 1; i <= n; ++i) {
    nrst[i] = i - query_stack(a[i]);
    insert_stack(a[i], i);
  }

  for (int i = 1; i <= n; ++i)
    sum[a[i]] += 1LL * nrst[i] * nrdr[i];

  for (int i = 1; i < N; ++i)
    sum[i] += sum[i - 1]; 
}

void solve() {
  char s[30];
  
  for (int i = 1; i <= m; ++i) {
    fgets(s, sizeof(s), stdin);
    
    int poz = 0, x = 0, y = 0;

    while (s[poz] >= '0' && s[poz] <= '9')
      x = x * 10 + s[poz++] - '0';
    ++poz;

    while (s[poz] >= '0' && s[poz] <= '9')
      y = y * 10 + s[poz++] - '0';

    ++x, ++y;
  
    printf("%lld\n", sum[y] - sum[x - 1]);
  }
}

int main() {
  freopen("nrsubsecv.in", "r", stdin);
  freopen("nrsubsecv.out", "w", stdout);

  read();

  init();

  solve();

  return 0;
}
