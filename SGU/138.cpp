#include <cstdio>
#include <algorithm>

using namespace std;

// v = number of games, p = position
struct elem {
  int v, p;
};

const int N = 105, M = 10005;

int n, sum, m, r[M][2];

elem a[N];

// in ascending order by the number of games
bool comp(const elem &A, const elem &B) {
  return (A.v < B.v);
}

void read() {
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i].v);
    a[i].p = i;
  }
}

// find the player with nb of games > val, except the pos_th player 
int find_next(int val, int pos) {
  for (int i = 1; i < n; ++i)
    if (a[i].v > val && i != pos)
      return i;
  return 0;
}

// sort the numbers and compute the sum of the smallest n - 1 numbers
void init() {
  sort(a + 1, a + n + 1, comp);
  
  sum = 0;

  for (int i = 1; i < n; ++i)
    sum += a[i].v;

  printf("%d\n", (sum + a[n].v) / 2);
}

// greedy
void solve() {
  int f = 1, s = 0;

  // make the sum of the smallest n - 1 number equal to the largest one 
  while (sum > a[n].v) {
    if (a[f].v == 1) {
      if (a[s].v <= 1)
        s = find_next(1, f);
    } else if (a[s].v == 1) {
      if (a[f].v <= 1)
        f = find_next(1, s);
    } else if (a[f].v == 0) {
      if (a[s].v == 1)
        f = find_next(1, s);
      else 
        f = find_next(0, s);
    } else if (a[s].v == 0) {
      if (a[f].v == 1)
        s = find_next(1, f);
      else
        s = find_next(0, f);
    }

    --a[f].v, --a[s].v;
    sum -= 2;
    r[++m][0] = a[f].p, r[m][1] = a[s].p;
  }
  
  // everyone plays with the player who has been ignored until now
  if (a[f].v) {
    r[++m][0] = a[f].p, r[m][1] = a[n].p;

    --a[f].v;
  } else if (a[s].v) {
    r[++m][0] = a[s].p, r[m][1] = a[n].p;
    
    --a[s].v;
  }
  
  for (int i = 1; i < n; ++i)
    while (a[i].v--) 
      r[++m][0] = a[i].p, r[m][1] = a[n].p;
}

// print the matches
void print() {
  for (int i = 1; i < m; ++i)
    if (r[i][0] == r[i + 1][0] || r[i][0] == r[i + 1][1]) 
      printf("%d %d\n", r[i][0], r[i][1]);
    else 
      printf("%d %d\n", r[i][1], r[i][0]);

  printf("%d %d\n", r[m][0], r[m][1]);
}

int main() {
  read();

  init();
  
  solve();
  
  print();

  return 0;
}
