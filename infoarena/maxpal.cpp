#include <cstdio>

const int N = 2005;

int n, a[N], d[2][N], nr[2][N];

void read() {
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
}

void reset(int a[N]) {
  for (int i = 1; i <= n; ++i)
    a[N] = 0;
}


// d[i][j] = lungimea maxima a unui palindrom intre poz i si j
// nr[i][j] = nr de palindroame de lungime d[i][j] intre poz i si j
void solve() {
  d[n & 1][n] = 1;

  for (int i = n - 1; i >= 1; --i) {
    reset(d[i & 1]);
    reset(nr[i & 1]);

   d[i & 1][i] = nr[i & 1][i] = 1;

   if (a[i] == a[i +  1])
     d[i & 1][i + 1] = 2, nr[i & 1][i + 1] = 1;
   else
     d[i & 1][i + 1] = 1, nr[i & 1][i + 1] = 2;
   
   for (int j = i + 2; j <= n; ++j) {
     if (a[i] != a[j]) {
       if (d[i & 1][j - 1] == d[(i + 1) & 1][j]) {
        d[i & 1][j] = d[i & 1][j - 1];
        nr[i & 1][j] = nr[i & 1][j - 1] + nr[(i + 1) & 1][j];
        
        if (d[i & 1][j] == d[(i + 1) & 1][j - 1])
          nr[i & 1][j] -= nr[(i + 1) & 1][j - 1];
       } else {
        if (d[i & 1][j - 1] > d[(i + 1) & 1][j])
          d[i & 1][j] = d[i & 1][j - 1], nr[i & 1][j] = nr[i & 1][j - 1];
        else
          d[i & 1][j] = d[(i + 1) & 1][j], nr[i & 1][j] = nr[(i + 1) & 1][j];
       }
     } else {
       d[i & 1][j] = 2 + d[(i + 1) & 1][j - 1];
       nr[i & 1][j] = nr[(i + 1) & 1][j - 1];

       if (d[i & 1][j] == d[i & 1][j - 1])
         nr[i & 1][j] += nr[i & 1][j - 1];

       if (d[i & 1][j] == d[(i + 1) & 1][j])
         nr[i & 1][j] += nr[(i + 1) & 1][j];
     }

     nr[i & 1][j] %= 666013;

     if (nr[i & 1][j] < 0)
       nr[i & 1][j] += 666013;
   }
  }
}

int main() {
  freopen("maxpal.in", "r", stdin);
  freopen("maxpal.out", "w", stdout);

  read();

  solve();

  printf("%d %d\n", d[1][n], nr[1][n]);

  return 0;
}
