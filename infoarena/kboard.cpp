#include <cstdio>
#include <cassert>

int t, n, k, pref[15], per[15], a[15], b[15], sg[3005];

void compute_grundy(int lung) {
  bool fgrc[3005];

  for (int i = 0; i < 3005; ++i)
    fgrc[i] = 0;

  for (int pstart = 1; pstart <= lung - k + 1; ++pstart)
    fgrc[sg[pstart - 1] ^ sg[lung - (pstart + k - 1)]] = 1;

  for (int i = 0; i < 3005; ++i)
    if (!fgrc[i]) {
      sg[lung] = i;
      break;
    }
}

void init() {
  if (k == 2) {
    pref[0] = 4; pref[1] = 4; pref[2] = 6; pref[3] = 6;
    pref[4] = 4; pref[5] = 4; pref[6] = 6; pref[7] = 4;
    per[0] = 4; per[1] = 12; per[2] = 4; per[3] = 4; per[4] = 10;
  }

  if (k > 2 && k <= 43) {
    for (int i = 0; i <= k - 1; ++i)
      sg[i] = 0;

    for (int i = k; i <= 3000; ++i)
      compute_grundy(i);
  }

  if (k >= 44) {
    a[0] = 2; b[0] = 0;
    a[1] = 2; b[1] = 0;
    a[2] = 4; b[2] = -2;
    a[3] = 4; b[3] = -2;
    a[4] = 4; b[4] = 0;
    a[5] = 4; b[5] = -2;
    a[6] = 8; b[6] = -2;
    a[7] = 4; b[7] = -2;
    a[8] = 8; b[8] = 0;
    a[9] = 8; b[9] = -2;
    a[10] = 16; b[10] = -6;
    a[11] = 4; b[11] = 0;
  }
}

void solve_1() {
  if (n % 2 == 1)
    printf("1\n");
  else
    printf("2\n");
}

void solve_2() {
  int pierz = 1;
  bool ok = 0;

  for (int j = 0; j <= 7; ++j)
    if (pierz + pref[j] <= n)
      pierz += pref[j];
    else {
      ok = 1;
      break;
    }
      
  if (ok) {
    if (pierz == n)
      printf("2\n");
    else
      printf("1\n");
    
    return;
  }

  pierz += (int)((n - pierz) / 34) * 34;

  for (int j = 0; j <= 4; ++j)
    if (pierz + per[j] <= n)
      pierz += per[j];
    else
      break;
    
  if (pierz == n)
    printf("2\n");
  else
    printf("1\n");
}

void solve_k_mic() {
  if (sg[n] == 0)
    printf("2\n");
  else
    printf("1\n");
}

void solve_k_mare() {
  if (n <= k - 1) {
    printf("2\n");
    return;
  }

  int pierz = k - 1;

  for (int i = 0; i <= 11; ++i)
    if (pierz + a[i] * k + b[i] <= n)
      pierz += a[i] * k + b[i];
    else
      break;

  if (pierz == n) 
    printf("2\n");
  else
    printf("1\n");
}

void solve() {
  for (int i = 1; i <= t; ++i) {
    assert(scanf("%d", &n));
    
    if (k == 1)
      solve_1();
    else if (k == 2)
      solve_2();
    else if (k > 2 && k <= 43)
      solve_k_mic();
    else
      solve_k_mare();
  }
}

int main() {
  assert(freopen("kboard.in", "r", stdin));
  assert(freopen("kboard.out", "w", stdout));

  assert(scanf("%d%d", &k, &t));

  init();
  
  solve();

  return 0;
}
