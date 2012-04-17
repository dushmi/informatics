#include <cstdio>
#include <vector>

using namespace std;

const int N = 2000005;

int A, B, f[N];

void read() {
  scanf("%d%d", &A, &B);
}

int query(int x) {
  int aux = x, oldx = x, p10 = 1, a[20];

  for (int i = 0 ; i < 20; ++i)
    a[i] = 0;

  while (aux) {
    a[++a[0]] = aux % 10;
    p10 *= 10;
    aux /= 10;
  }

  p10 /= 10;

  vector <int> v;
  
  for (int i = 1; i <= a[0]; ++i) {
    x = x / 10 + a[i] * p10;
    
    if (x <= oldx || x > B)
      continue;

    if (f[x] != oldx) {
      v.push_back(x);
      f[x] = oldx;
    }
  }

  return (int)v.size();
}

int solve() {
  int sol = 0;

  for (int i = A; i <= B; ++i) 
      sol += query(i);

  return sol;
}

int main() {
  //freopen("data.in", "r", stdin);
  //freopen("data.out", "w", stdout);
  
  int T;

  scanf("%d\n", &T);

  for (int i = 1; i <= T; ++i) {
    read();
    
    for (int j = 0; j < N; ++j)
      f[j] = 0;

    printf("Case #%d: %d\n", i, solve());
  }
  
  return 0;
}
