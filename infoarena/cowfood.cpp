#include <cstdio>

const int K = 35, N = 25, S = 10005, MOD = 3210121;

int result, k, s, n, nb1, sum, missed[K][N], din[S];

inline int max(int x, int y) {
  return x < y ? y : x;
}

//missed[i] = the ith missed experiment
void read() {
  scanf("%d%d%d", &k, &s, &n);

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= k; ++j)
      scanf("%d", &missed[i][j]);
}

//din[i][j] = number of i-tuples with sum <= j
//din[i][j] = din[i][j - 1] + din[i - 1][j]
void init() {
  for (int j = 0; j <= s; ++j)
    din[j] = din[j - 1] + 1;

  for (int  i = 2; i <= k; ++i)
    for (int j = 1; j <= s; ++j)
      din[j] = (din[j - 1] + din[j]) % MOD;
}

void back(int poz, int v[K]) {
  if (poz == n + 1) {
    if (s >= sum) {
      if (nb1 & 1) 
        result = (result - din[s - sum] + MOD) % MOD; 
      else
        result = (result + din[s - sum]) % MOD;
    }

    return;
  }

  back(poz + 1, v);

  int vaux[K];
  
  sum = 0;

  for (int i = 1; i <= k; ++i) {
    vaux[i] = v[i];
    v[i] = max(v[i], missed[poz][i]);
    sum += v[i];
  }

  ++nb1;

  back(poz + 1, v);

  sum = 0;

  for (int i = 1; i <= k; ++i) {
    v[i] = vaux[i];
    sum += v[i];
  }

  --nb1;
}

int main() {
  freopen("cowfood.in", "r", stdin);
  freopen("cowfood.out", "w", stdout);

  read();

  init();

  int v[K];

  for (int i = 1; i <= k; ++i)
    v[i] = 0;
  
  back(1, v);

  printf("%d\n", result - k * s - 1);

  return 0;
}
