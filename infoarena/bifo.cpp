#include <cstdio>
#include <cstring>

const int N = 505, C = 135;

typedef int Huge[C];

Huge length[N], sum[N], v[N];

char a[3][C];

int n;

void plusplus(Huge a) {
  if (!a[0])
    a[++a[0]] = 1;
  else {
    ++a[1];

    int poz = 1;

    while (a[poz] >= 10) {
      a[poz + 1] += a[poz] / 10;
      a[poz] %= 10;
      ++poz;
    }

    if (poz > a[0])
      a[0] = poz;
  }
}

void adun(Huge a, Huge b, Huge c) {
  int i = 0, T = 0;

  for (i = 1; i <= b[0] || i <= c[0] || T; ++i) {
    a[i] = b[i] + c[i] + T;
    T = a[i] / 10;
    a[i] %= 10;
  }

  a[0] = i - 1;
}

int comp(Huge a, Huge b) {
  if (a[0] < b[0])
    return -1;

  if (a[0] > b[0])
    return 1;

  for (int i = a[0]; i >= 1; --i) {
    if (a[i] < b[i])
      return -1;

    if (a[i] > b[i])
      return 1;
  }

  return 0;
}

void scad(Huge a, Huge b) {
  int T = 0;

  for (int i = 1; i <= a[0]; ++i) {
    a[i] -= (b[i] + T);
    if (a[i] < 0) {
      a[i] += 10;
      T = 1;
    } else
      T = 0;
  }

  while (!a[a[0]])
    --a[0];
}

int tonumber(Huge a) {
  int x = 0;

  for (int i = a[0]; i >= 1; --i)
    x = x * 10 + a[i];

  return x;
}

void read() {
  char s[C];

  gets(a[1] + 1);
  for (int i = 1; a[1][i]; ++i)
    plusplus(length[1]);

  gets(a[2] + 1);
  for (int i = 1; a[2][i]; ++i)
    plusplus(length[2]);

  scanf("%d\n", &n);

  for (int i = 1; i <= n; ++i) {
    gets(s);
    
    for (int j = strlen(s) - 1; j >= 0; --j)
      v[i][++v[i][0]] = s[j] - '0';
  }
}

void init() {
  for (int i = 3; i < N; ++i)
    adun(length[i], length[i - 1], length[i - 2]);

  for (int i = 1; i < N; ++i) 
    adun(sum[i], sum[i - 1], length[i]);
}

int cautb(Huge a) {
  int pas = (1 << 7), i = 0;

  for (i = 0; pas; pas >>= 1)
    if (i + pas < N && comp(sum[i + pas], a) == -1)
      i += pas;

  return i + 1;
}

void divide_et_impera(Huge pt, int poz) {
  if (poz <= 2) {
    int x = tonumber(pt);
    printf("%c", a[poz][x]);
    return;
  }

  if (comp(length[poz - 2], pt) == -1) {
    scad(pt, length[poz - 2]);
    divide_et_impera(pt, poz - 1);
  } else 
    divide_et_impera(pt, poz - 2);
}

void solve() {
  for (int i = 1; i <= n; ++i) {
    int nr = cautb(v[i]);
    
    scad(v[i], sum[nr - 1]);
    
    divide_et_impera(v[i], nr);
  }
}

int main() {
  freopen("bifo.in", "r", stdin);
  freopen("bifo.out", "w", stdout);

  read();

  init();

  solve();

  return 0;
}
