#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;

struct Square {
  int x1, y1, x2, y2;

  Square(int _x1, int _y1, int _x2, int _y2) {
    x1 = _x1; y1 = _y1;
    x2 = _x2; y2 = _y2;
  }
};

struct Point {
  int x, y;

  Point(int _x, int _y) {
    x = _x; y = _y;
  }

  Point() {
    x = y = 0;
  }
};

const int kMaxn = 1005;

int n, k, d[kMaxn][kMaxn];

queue <Point> Q;

int dx[] = {  0, -1, +1,  0};
int dy[] = { -1,  0,  0, +1};

inline int min(int x, int y) {
  return x < y ? x : y;
}

inline int max(int x, int y) {
  return x > y ? x : y;
}

bool squareIntersection(vector <Square> v) {
  int x1 = -INF, y1 = -INF, x2 = INF, y2 = INF;

  for (int i = 0; i < (int)v.size(); ++i) {
    x1 = max(x1, v[i].x1); y1 = max(y1, v[i].y1);
    x2 = min(x2, v[i].x2); y2 = min(y2, v[i].y2);
  }

  if (x1 == x2 && y1 == y2 && (x1 & 1) == (y1 & 1))
    return 1;
  
  if (x1 == x2 && y1 == y2)
    return 0;
  
  if (x1 <= x2 && y1 <= y2)
    return 1;

  return 0;
}

bool inside(Point a) {
  return (1 <= a.x && a.x <= n && 1 <= a.x && a.x <= n);
}

void rotate45(Point &a) {
  a.x = a.x + a.y;
  a.y = a.x - 2 * a.y;
}

void init() {
  for (int i = 1; i < kMaxn; ++i)
    for (int j = 1; j < kMaxn; ++j)
      d[i][j] = INF;
}

int getNumber(char s[15], int &pos) {
  int x = 0;

  while (s[pos] >= '0' && s[pos] <= '9')
    x = x * 10 + s[pos++] - '0';

  return x;
}

void read() {
  char s[15];
  int x, y, pos;
  
  fgets(s, sizeof(s), stdin);
  pos = 0;
  n = getNumber(s, pos);
  ++pos;
  k = getNumber(s, pos);
  
  init();

  for (int i = 1; i <= k; ++i) {
    fgets(s, sizeof(s), stdin);
    pos = 0;
    x = getNumber(s, pos);
    ++pos;
    y = getNumber(s, pos);

    Q.push(Point(x + 1, y + 1));
    d[x + 1][y + 1] = 0;
  }
}

void _BFS() {
  while (!Q.empty()) {
    Point node = Q.front(), newnode; Q.pop();

    for (int i = 0; i < 4; ++i) {
      newnode.x = node.x + dx[i];
      newnode.y = node.y + dy[i];

      if (d[newnode.x][newnode.y] > d[node.x][node.y] + 1 && inside(newnode)) {
        d[newnode.x][newnode.y] = d[node.x][node.y] + 1;
        Q.push(newnode);
      }
    }
  }
}

bool ok(int dist) {
  vector <Square> v;

  Point p1, p2;

  for (int i = 1; i <= n; ++i) 
    for (int j = 1; j <= n; ++j)
      if (d[i][j] > dist) {
        p1.x = i - dist; p1.y = j;
        p2.x = i + dist; p2.y = j;
        rotate45(p1);
        rotate45(p2);
        v.push_back(Square(p1.x, p1.y, p2.x, p2.y));
      }
  
  return squareIntersection(v);
}

int binarySearch() {
  int step = 1 << 11, i = -1;

  for (i = -1; step; step >>= 1)
    if (!ok(i + step))
      i += step;

  return i + 1;
}

int main() {
  freopen("centru.in", "r", stdin);
  freopen("centru.out", "w", stdout);

  read();

  _BFS();

  printf("%d\n", binarySearch());

  return 0;
}
