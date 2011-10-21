#include <cstdio>
#include <cmath>
#include <cstring>

const int N = 500005;

char s[N];

int n, a[N], f[1 << 20];

void read() {
  scanf("%d\n", &n);

  gets(s + 1);
}

void edit() {
  for (int i = 1; i <= n; ++i)
    a[i] = s[i] - 'a';
}

void post(int, int);

void solve() {
  int lun = (int)log2(n) + 1, nc = 0;
  
  for (int l = 1; l <= lun; ++l) {
    nc = 0;

    memset(f, 0, (1 << 20) * sizeof(int));

    for (int i = 1; i <= l; ++i)
      nc = (nc << 1) + a[i];
    
    f[nc] = 1;

    for (int i = l + 1; i <= n; ++i) {
      if (nc & (1 << (l - 1))) 
        nc -= (1 << (l - 1));

      nc = (nc << 1) + a[i];
      
      f[nc] = 1;
   }

   for (int i = 0; i < (1 << l); ++i)
     if (!f[i]) {
       printf("%d\n", l);
       post(i, l);
       return;
     }
  }
}

void post(int x, int lung) {
  if (lung == 0)
    return;

  post(x >> 1, lung - 1);

  printf("%c", (x & 1) + 'a');
}

int main() {
  freopen("string.in", "r", stdin);
  freopen("string.out", "w", stdout);

  read();

  edit();
  
  solve();

  return 0;
}
