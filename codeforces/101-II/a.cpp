#include <cstdio>

const int N = 105;

int f1[26], f2[26];

char a[N], b[N], c[N];

void read() {
  gets(a);
  gets(b);
  gets(c);
}

void solve() {
  for (int i = 0; a[i]; ++i)
    ++f1[a[i] - 'A'];
  for (int i = 0; b[i]; ++i)
    ++f1[b[i] - 'A'];
  for (int i = 0; c[i]; ++i)
    ++f2[c[i] - 'A'];

  for (int i = 0; i < 26; ++i)
    if (f1[i] != f2[i]) {
      printf("NO\n");
      return;
    }
 
  printf("YES"); 
}

int main() {
  read();

  solve();

  return 0;
}
