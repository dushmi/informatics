#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 3005;

struct people {
  int val;
  char name[11];
};

people v[N];

int n, who[N];

void read() {
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i)
    scanf("%s %d", v[i].name, &v[i].val);
}

bool comp(people a, people b) {
  return a.val < b.val;
}

void solve() {
  sort(v + 1, v + n + 1, comp);

  int q = 0, i;

  for (i = 1; i <= n; ++i)
    if (v[i].val == 0)
      who[++q] = i;
    else
      break;

  for (i = i; i <= n; ++i) {
    if (q - v[i].val + 1 <= 0) {
      printf("-1");
      return;
    }

    for (int j = q + 1; j > q - v[i].val + 1; --j)
      who[j] = who[j - 1];
    who[q - v[i].val + 1] = i;
    ++q;
  }

  for (i = 1; i <= n; ++i)
    v[who[i]].val = i;

  for (int i = 1; i <= n; ++i)
    printf("%s %d\n", v[i].name, v[i].val);
}

int main() {
  read();

  solve();

  return 0;
}

