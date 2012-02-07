#include <cstdio>
#include <cassert>

const int N = 105;

typedef int Huge[N];

int L, LT, f[10];

Huge a, b, c, arez, brez, rez;

inline int max(int x, int y) {
  return x > y ? x : y;
}

void read() {
  assert(scanf("%d", &L));

  for (int i = 0; i <= 9; ++i)
    assert(scanf("%d", &f[i]));
}

inline void init() {
  for (int i = 0; i <= 9; ++i)
    LT += f[i];
}

inline bool verif(int L1, int L2) {
  int nri = 0;

  for (int i = 0; i <= 9; ++i)
    if (f[i] % 2 == 1)
      ++nri;

  if (L1 % 2 == 0 && L2 % 2 == 0) {
    if (nri == 0)
      return 1;

    return 0;
  } else if (L1 % 2 == 1 && L2 % 2 == 0) {
    if (nri == 1)
      return 1;

    return 0;
  } else if (L1 % 2 == 0 && L2 % 2 == 1) {
    if (nri == 1)
      return 1;

    return 0;
  } else if (L1 % 2 == 1 && L2 % 2 == 1) {
    if (nri == 2 || nri == 0)
      return 1;

    return 0;
  }
}

inline void edit_f(int pi, int pf, int c) {
  if (pi == pf)
    --f[c];
  else
    f[c] -= 2;
}

inline void restore_f(int pi, int pf, int c) {
  if (pi == pf)
    ++f[c];
  else
    f[c] += 2;
}

void adun(Huge r, Huge a, Huge b) {
  int i = 0, T = 0;

  for (i = 1; i <= a[0] || i <= b[0] || T; ++i) {
    r[i] = a[i] + b[i] + T;
    T = r[i] / 10;
    r[i] %= 10;
  }

  r[0] = i - 1;
}

bool compar(Huge a, Huge b) {
  if (a[0] < b[0])
    return 1;

  if (a[0] > b[0])
    return 0;

  for (int i = a[0]; i >= 1; --i)
    if (a[i] < b[i])
      return 1;
    else if (a[i] > b[i])
      return 0;

  return 0;
}

void atrib(Huge a, Huge b) {
  for (int i = b[0]; i >= 0; --i)
    a[i] = b[i];
}

void reset(Huge a) {
  for (int i = 0; i < N; ++i)
    a[i] = 0;
}

void check() {
  reset(c);

  adun(c, a, b);

  if (compar(c, rez) || rez[0] == 0) {
    atrib(rez, c);
    atrib(arez, a);
    atrib(brez, b);
  }
}

void solve(int pi1, int pf1, int pi2, int pf2) {
  if (pi1 > pf1 && pi2 > pf2) {
    check();
    return;
  }

  if (pi1 <= pf1 && (pf2 < pi2 || (pf1 > pf2 || (pf1 == pf2 && pi1 > pi2)))) {
    for (int i = 0; i <= 9; ++i)
      if (f[i]) {
        edit_f(pi1, pf1, i);

        if (f[i] < 0) {
            restore_f(pi1, pf1, i);
            continue;
        }

        if (verif(max(pf1 - pi1 - 2 + 1, 0), max(pf2 - pi2 + 1, 0))) {
          a[pi1] = a[pf1] = i;
          solve(pi1 + 1, pf1 - 1, pi2, pf2);
          restore_f(pi1, pf1, i);
          break;
        }

        restore_f(pi1, pf1, i);
      }
  } else {
    for (int i = 0; i <= 9; ++i)
      if (f[i]) {
        edit_f(pi2, pf2, i);

        if (f[i] < 0) {
            restore_f(pi2, pf2, i);
            continue;
        }

        if (verif(max(pf1 - pi1 + 1, 0), max(pf2 - pi2 - 2 + 1, 0))) {
          b[pi2] = b[pf2] = i;
          solve(pi1, pf1, pi2 + 1, pf2 - 1);
          restore_f(pi2, pf2, i);
          break;
        }

        restore_f(pi2, pf2, i);
      }
  }
}

void afis(Huge a) {
  for (int i = a[0]; i >= 1; --i)
    printf("%d", a[i]);

  printf("\n");
}

void solve() {
  for (L = L; L < LT; ++L)
    for (int p1 = 1; p1 <= 9; ++p1)
      if (f[p1]) {
        edit_f(1, L, p1);

        if (f[p1] < 0) {
          restore_f(1, L, p1);
          continue;
        }

        for (int p2 = 1; p2 <= 9; ++p2)
          if (f[p2]) {
            edit_f(1, LT - L, p2);

            if (f[p2] < 0) {
                restore_f(1, LT - L, p2);
                continue;
            }

            if (verif(max(L - 2, 0), max(LT - L - 2, 0))) {
              reset(a);
              a[0] = L;
              a[1] = a[L] = p1;
              reset(b);
              b[0] = LT - L;
              b[1] = b[LT - L] = p2;
              solve(2, L - 1, 2, LT - L - 1);
            }

            restore_f(1, LT - L, p2);
          }

        restore_f(1, L, p1);
      }

  afis(arez);
  afis(brez);
}

int main() {
  assert(freopen("pal.in", "r", stdin));
  assert(freopen("pal.out", "w", stdout));

  read();

  init();

  solve();

  return 0;
}
