#include <cstdio>
#include <utility>

using namespace std;

const int N = 50005, INF = 0x3f3f3f3f;

int n, minx, miny, maxx, maxy;

pair <int, int> sq[5], a[N];

bool used[N];

void read() {
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i)
    scanf("%d%d", &a[i].first, &a[i].second);
}

void init(int lat) {
  minx = miny = INF;
  maxx = maxy = 0;

  for (int i = 1; i <= n; ++i)
    if (!used[i]) {
      if (a[i].first < minx)
        minx = a[i].first;

      if (a[i].first > maxx)
        maxx = a[i].first;

      if (a[i].second < miny)
        miny = a[i].second;

      if (a[i].second > maxy)
        maxy = a[i].second;
    }
 
  sq[1].first = minx; sq[1].second = maxy;
  sq[2].first = maxx - lat; sq[2].second = maxy;
  sq[3].first = maxx - lat; sq[3].second = miny + lat;
  sq[4].first = minx; sq[4].second = miny + lat;
}

void reset(bool a[N]) {
  for (int i = 1; i <= n; ++i)
    a[i] = 0;
}

void marcheaza(int ssx, int ssy, int lat) {
  for (int i = 1; i <= n; ++i)
    if (a[i].first >= ssx && a[i].first <= ssx + lat &&
        a[i].second <= ssy && a[i].second >= ssy - lat)
      used[i] = 1;
}

bool valid(int ssx1, int ssy1, int ssx2, int ssy2, int lat) {
  for (int i = 1; i <= n; ++i)
    if (!used[i] && !(a[i].first >= ssx1 && a[i].first <= ssx1 + lat &&
        a[i].second <= ssy1 && a[i].second >= ssy1 - lat) &&
        !(a[i].first >= ssx2 && a[i].first <= ssx2 + lat &&
        a[i].second <= ssy2 && a[i].second >= ssy2 - lat))
      return 0;

  return 1;
}

bool solve(int lat) {
  for (int c1 = 1; c1 <= 4; ++c1) {
    reset(used);

    init(lat);
  
    marcheaza(sq[c1].first, sq[c1].second, lat);
    
    init(lat);

    for (int c2 = 1; c2 <= 4; ++c2)
      for (int c3 = c2 + 1; c3 <= 4; ++c3)
        if (valid(sq[c2].first, sq[c2].second, sq[c3].first, sq[c3].second, lat))
          return 1;
  }

  return 0;
}

int cautb() {
  int pas = (1 << 16), i = 0;

  for (i = 0; pas; pas >>= 1)
    if (!solve(i + pas))
      i += pas;

  return i + 1;
}

int main() {
  freopen("patrate.in", "r", stdin);
  freopen("patrate.out", "w", stdout);

  read();

  if (n <= 3) {
    printf("0\n");
    return 0;
  }

  printf("%d\n", cautb());
  
  return 0;
}
