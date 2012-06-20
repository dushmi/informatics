#include <cstdio>
#include <cassert>

const int kMaxN = 100005;

char s[kMaxN];

inline bool is_letter(char x) {
  return ('a' <= x && x <= 'z');
}

int main() {
  assert(freopen("compress.in", "r", stdin));
  assert(freopen("compress.out", "w", stdout));

  assert(fgets(s, sizeof(s), stdin));

  int count = 1, i;

  for (i = 1; is_letter(s[i]); ++i) {
    if (s[i] == s[i - 1]) {
      ++count;
      continue;
    }
   
    printf("%c%d", s[i - 1], count);
    count = 1;
  }

  printf("%c%d", s[i - 1], count);

  return 0;
}
