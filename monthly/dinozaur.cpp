#include <cstdio>
#include <cassert>

const int kMaxN = 100005;

char s[kMaxN];

int f[30];

int main() {
  assert(freopen("dinozaur.in", "r", stdin));
  assert(freopen("dinozaur.out", "w", stdout));

  assert(fgets(s, sizeof(s), stdin));

  for (int i = 0; 'a' <= s[i] && s[i] <= 'z'; ++i) {
    int letter = s[i] - 'a';

    if (f[letter]) {
      printf("1\n");
      return 0;
    }

    f[letter] = i;
  }

  printf("0\n");

  return 0;
}
