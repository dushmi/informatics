#include <cstdio>

const int N = 35, L = 105;

char s[N][L];

int n, cor[256];

void read() {
  scanf("%d\n", &n);

  for (int i = 1; i <= n; ++i)
    fgets(s[i], sizeof(s[i]), stdin);
}

void init() {
  cor['a'] = 'y';
  cor['b'] = 'h';
  cor['c'] = 'e';
  cor['d'] = 's';
  cor['e'] = 'o';
  cor['f'] = 'c';
  cor['g'] = 'v';
  cor['h'] = 'x';
  cor['i'] = 'd';
  cor['j'] = 'u';
  cor['k'] = 'i';
  cor['l'] = 'g';
  cor['m'] = 'l';
  cor['n'] = 'b';
  cor['o'] = 'k';
  cor['p'] = 'r';
  cor['q'] = 'z';
  cor['r'] = 't';
  cor['s'] = 'n';
  cor['t'] = 'w';
  cor['u'] = 'j';
  cor['v'] = 'p';
  cor['w'] = 'f';
  cor['x'] = 'm';
  cor['y'] = 'a';
  cor['z'] = 'q';
}

void solve() {
  for (int i = 1; i <= n; ++i) {
    printf("Case #%d: ", i);

    for (int j = 0; s[i][j] == ' ' || (s[i][j] >= 'a' && s[i][j] <= 'z'); ++j)
      if (s[i][j] == ' ')
        printf(" ");
      else
        printf("%c", cor[s[i][j]]);

    printf("\n");
  }
}

int main() {
  //freopen("data.in", "r", stdin);
  //freopen("data.out", "w", stdout);
  
  read();

  init();

  solve();

  return 0;
}
