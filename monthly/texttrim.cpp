#include <cstdio>
#include <cassert>
#include <cstdlib>

const int N = 1000005;

int lung, len[27];

char s[N];

void read() {
  scanf("%d", &len[26]);
  for (int i = 0; i < 26; ++i)
    scanf("%d", &len[i]);
  scanf("\n");

  fgets(s, sizeof(s), stdin);

  scanf("%d", &lung);
}

inline int code(char ch) {
  if (ch >= 'a' && ch <= 'z')
    return ch - 'a';

  return 26;
}

void init() {
  int lt = 0;

  for (int i = 0; (s[i] >= 'a' && s[i] <= 'z') || s[i] == ' '; ++i) {
    lt += len[code(s[i])];
    if (lt > lung)
      return;
  }

  if (lt == lung) {
    puts(s);
    exit(0);
  }
}

void solve() {
  if (len[code(s[0])] > lung) {
    printf("...");
    exit(0);
  }

  int lc = len[code(s[0])];

  printf("%c", s[0]);

  for (int i = 1; (s[i] >= 'a' && s[i] <= 'z' ) || s[i] == ' '; ++i) {
    if (lc + len[code(s[i])] > lung - 3) {
      printf("...");
      exit(0);
    }

    lc += len[code(s[i])];
    printf("%c", s[i]);
  }
}

int main() {
  assert(freopen("texttrim.in", "r", stdin));
  assert(freopen("texttrim.out", "w", stdout));

  read();

  init();

  solve();

  return 0;
}
