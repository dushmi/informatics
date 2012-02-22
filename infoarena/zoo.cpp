#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 16500, M = 100500, INF = 2000000500;

struct point {
  int x, y, poz, sgn;
};

struct rectangle {
  int x1, y1, x2, y2;
};

rectangle q[M];

point v[N], t[4 * M];

int n, m, newm, ans[M], vy[N], cory[N], aib[N];

void read() {
  char s[100];

  int poz = 0, sgn = 1;

  assert(fgets(s, sizeof(s), stdin));

  while (s[poz] >= '0' && s[poz] <= '9')
    n = n * 10 + s[poz++] - '0';

  for (int i = 1; i <= n; ++i) {
    assert(fgets(s, sizeof(s), stdin));
    
    poz = 0;
    sgn = 1;

    if (s[poz] == '-') {
      sgn = -1;
      ++poz;
    }

    while (s[poz] >= '0' && s[poz] <= '9')
      v[i].x = v[i].x * 10 + s[poz++] - '0';

    v[i].x *= sgn;

    ++poz;
    sgn = 1;

    if (s[poz] == '-') {
      sgn = -1;
      ++poz;
    }

    while (s[poz] >= '0' && s[poz] <= '9')
      v[i].y = v[i].y * 10 + s[poz++] - '0';

    v[i].y *= sgn;
  }

  assert(fgets(s, sizeof(s), stdin));
  
  poz = 0;

  while (s[poz] >= '0' && s[poz] <= '9')
    m = m * 10 + s[poz++] - '0';
  
  for (int i = 1; i <= m; ++i) {
    assert(fgets(s, sizeof(s), stdin));
    
    poz = 0;
    sgn = 1;

    if (s[poz] == '-') {
      sgn = -1;
      ++poz;
    }

    while (s[poz] >= '0' && s[poz] <= '9')
      q[i].x1 = q[i].x1 * 10 + s[poz++] - '0';

    q[i].x1 *= sgn;

    ++poz;
    sgn = 1;

    if (s[poz] == '-') {
      sgn = -1;
      ++poz;
    }

    while (s[poz] >= '0' && s[poz] <= '9')
      q[i].y1 = q[i].y1 * 10 + s[poz++] - '0';

    q[i].y1 *= sgn;

    ++poz;
    sgn = 1;

    if (s[poz] == '-') {
      sgn = -1;
      ++poz;
    }

    while (s[poz] >= '0' && s[poz] <= '9')
      q[i].x2 = q[i].x2 * 10 + s[poz++] - '0';

    q[i].x2 *= sgn;
  
    ++poz;
    sgn = 1;

    if (s[poz] == '-') {
      sgn = -1;
      ++poz;
    }

    while (s[poz] >= '0' && s[poz] <= '9')
      q[i].y2 = q[i].y2 * 10 + s[poz++] - '0';

    q[i].y2 *= sgn;
  }
}

int cautb(int x, int *v, bool type) {
  int i = 0, pas = 1 << 18;

  for (i = 0; pas; pas >>= 1)
    if (i + pas <= v[0] && v[i + pas] < x)
      i += pas;

  if (type == 0)
    return i;
  
  if (type == 1) {
    if (v[i + 1] == x)
      return i + 1;

    return i;
  }

  return 0;  
}

void normalization() {
  vy[++vy[0]] = -INF;

  for (int i = 1; i <= n; ++i)
    vy[++vy[0]] = v[i].y;

  vy[++vy[0]] = INF;

  sort(vy + 1, vy + vy[0] + 1);

  for (int i = 1; i <= vy[0]; ++i) {
    cory[i] = cory[i - 1];

    if (vy[i] != vy[i - 1])
      ++cory[i];
  }

  for (int i = 1; i <= n; ++i)
    v[i].y = cory[cautb(v[i].y, vy, 1)];

  for (int i = 1; i <= m; ++i) {
    q[i].y1 = cory[cautb(q[i].y1, vy, 0)];
    q[i].y2 = cory[cautb(q[i].y2, vy, 1)];
  }
}

bool comp(point A, point B) {
  if (A.x < B.x)
    return 1;

  if (A.x > B.x)
    return 0;

  return A.y < B.y;
}

void init() {
  sort(v + 1, v + n + 1, comp);

  newm = 0;

  for (int i = 1; i <= m; ++i) {
    ++newm;
    t[newm].x = q[i].x2;
    t[newm].y = q[i].y2;
    t[newm].poz = i;
    t[newm].sgn = 1;

    ++newm;
    t[newm].x = q[i].x2;
    t[newm].y = q[i].y1;
    t[newm].poz = i;
    t[newm].sgn = -1;

    ++newm;
    t[newm].x = q[i].x1 - 1;
    t[newm].y = q[i].y2;
    t[newm].poz = i;
    t[newm].sgn = -1;

    ++newm;
    t[newm].x = q[i].x1 - 1;
    t[newm].y = q[i].y1;
    t[newm].poz = i;
    t[newm].sgn = 1;    
  }

  sort(t + 1, t + newm + 1, comp);
}

inline int bit(int x) {
  return x & (-x);
}

inline int query(int poz) {
  int rez = 0;

  while (poz) {
    rez += aib[poz];
    poz -= bit(poz);
  }

  return rez;
}

inline void insert(int poz) {
  while (poz < N) {
    ++aib[poz];
    poz += bit(poz);
  }
}

void solve() {
  for (int i = 1, j = 1; i <= n || j <= newm;)
    if (i > n) {
      ans[t[j].poz] += t[j].sgn * query(t[j].y);
      ++j;
    } else if (j > newm) {
      insert(v[i].y);
      ++i;
    } else if (v[i].x <= t[j].x) {
      insert(v[i].y);
      ++i;
    } else {
      ans[t[j].poz] += t[j].sgn * query(t[j].y);
      ++j;
    }

  for (int i = 1; i <= m; ++i)
      printf("%d\n", ans[i]);
}

int main() {
  assert(freopen("zoo.in", "r", stdin));
  assert(freopen("zoo.out", "w", stdout));

  read();

  normalization();

  init();

  solve();

  return 0;
}

