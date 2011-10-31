#include <cstdio>

const int N = 100005;

inline int max(int x, int y) {
  return x > y ? x : y;
}

//t[i] = timpul minim la care pleaca soldatul i
void solve() {
  char s[N];

  int n = 0, pos, lastpos = 0, rez = 0, t[N];

  bool v[N];
  
  gets(s);

  for (int i = 0; s[i]; ++i) {
    n = i + 1;

    v[i + 1] = 0;
    t[i + 1] = 0;
    
    if (s[i] == '>') {
      v[i + 1] = 1;

      if (i + 1 > lastpos)
        lastpos = i + 1;
    }
  }

  if (lastpos == 0) {
    printf("0\n");
    return;
  }

  t[lastpos] = 0;
  pos = n;
  rez = pos - lastpos;
  --pos;

  for (int i = lastpos - 1; i >= 1; --i)
    if (v[i]) {
      if (lastpos != pos + 1 && t[lastpos] >= lastpos - i - 1)
        t[i] = t[lastpos] - (lastpos - i - 1) + 1;

      if (pos != i)
        rez = max(rez, t[i] + pos - i);
      
      lastpos = i;
      --pos;
    }
  
  printf("%d\n", rez);
}

int main() {
  freopen("soldati.in", "r", stdin);
  freopen("soldati.out", "w", stdout);

  int T;

  scanf("%d\n", &T);

  for (int i = 1; i <= T; ++i)
    solve();

  return 0;
}
