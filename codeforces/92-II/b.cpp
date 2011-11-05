#include <cstdio>

int n, k, res, perm[10], f[10], v[10], a[10][10];

void verif() {
  for (int i = 1; i <= n; ++i) {
    v[i] = 0;

    for (int j = 1; j <= k; ++j)
      v[i] = v[i] * 10 + a[i][perm[j]];
  }

  int mc = 1000000000, MC = -1;

  for (int i = 1; i <= n; ++i) {
    if (v[i] < mc)
      mc = v[i];

    if (v[i] > MC)
      MC = v[i];
  }

  if (MC - mc < res)
    res = MC - mc;
}

void back(int poz) {
  if (poz == k + 1) {
    verif();
    return;
  }

  for (int i = 1; i <= k; ++i)
    if (!f[i]) {
      f[i] = 1;
      perm[poz] = i;
      back(poz + 1);
      f[i] = 0;
    }
}

int main() {
  int x;

  scanf("%d%d", &n, &k);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
   
    while(x)
      a[i][++a[i][0]] = x % 10, x /= 10;
  }
  
  res = 1000000000;

  back(1);

  printf("%d\n", res);

  return 0;
}
