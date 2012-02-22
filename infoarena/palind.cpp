#include <cstdio>
#include <cassert>

int T, n;

char s[105];

bool verif() {
  int f[26];

  for (int i = 0; i < 26; ++i)
    f[i] = 0;

  for (int i = 0; s[i] >= 'a' && s[i] <= 'z'; ++i)
    ++f[s[i] - 'a'];

  int nri = 0;

  for (int i = 0; i < 26; ++i)
    if (f[i] & 1)
      ++nri;

  if (nri > 1)
    return 0;

  return 1;
}

void move_pf(int pi, int pf, int poz) {
  for (int i = poz; i >= pi + 1; --i)
    s[i] = s[i - 1];
  
  s[pi] = s[pf];
}

void move_pi(int pi, int pf, int poz) {
  for (int i = poz; i < pf; ++i)
    s[i] = s[i + 1];

  s[pf] = s[pi];
}

int edit(int pi, int pf) {
  int poz_pi = -1, poz_pf = -1;

  //keep pi in it's place
  for (int i = pf; i > pi; --i)
    if (s[i] == s[pi]) {
      poz_pi = i;
      break;
    }

  //keep pf in it's place
  for (int i = pi; i < pf; ++i)
    if (s[i] == s[pf]) {
      poz_pf = i;
      break;
    }

  //printf("%d %d; poz_pi : %d; poz_pf : %d\n", pi, pf, poz_pi, poz_pf);

  if (poz_pi == -1) {
    move_pf(pi, pf, poz_pf);
    return poz_pf - pi;
  }
  
  if (poz_pf == -1) {
    move_pi(pi, pf, poz_pi);
    return pf - poz_pi;
  }

  if (pf - poz_pi < poz_pf - pi) {
    move_pf(pi, pf, poz_pf);
    return poz_pf - pi;
  }

  move_pi(pi, pf, poz_pi);
  return pf - poz_pi;
}

void solve() {
  if (!verif()) {
    printf("-1\n");
    return;
  }

  int n = 0;

  for (n = 0; s[n] >= 'a' && s[n] <= 'z'; ++n);
  
  --n;

  int rez = 0;

  for (int i = 0; i <= (n - 1) / 2; ++i)
    if (s[i] != s[n - i])
      rez += edit(i, n - i);
  
  printf("%d\n", rez);
}

int main() {
  assert(freopen("palind.in" ,"r", stdin));
  assert(freopen("palind.out", "w", stdout));

  assert(scanf("%d\n", &T));
  
  for (int i = 1; i <= T; ++i) {
    assert(fgets(s, sizeof(s), stdin));

    solve();
  }

  return 0;
}
