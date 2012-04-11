#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 60005, L = 1000005;

int n, l, st, dr, dq[L], price[L], end[L], d[L];

vector <pair <int, int> > in, v;

void read() {
  char str[L * 6];
  int n, x, y;

  scanf("%d%d\n", &n, &l);
  
  fgets(str, sizeof(str), stdin);
  
  int poz = 0;

  for (int i = 1; i <= l; ++i) {
    while (str[poz] >= '0' && str[poz] <= '9')
      price[i] = price[i] * 10 + str[poz++] - '0';

    ++poz;
  }

  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &x, &y);
    in.push_back(make_pair(x, y));
  }
}

bool comp(const pair <int, int> &a, const pair <int, int> &b) {
  if (a.second == b.second)
    return a.first > b.first;

  return a.second < b.second;
}

void init() {
  sort(in.begin(), in.end(), comp);

  v.push_back(in[0]);

  for (int i = 1; i < (int)in.size(); ++i) {
    if (in[i].second == in[i - 1].second)
      continue;

    if (in[i].first <= v[(int)v.size() - 1].first)
      continue;

    v.push_back(in[i]);
  }

  for (int i = 1; i <= l; ++i)
    end[i] = -1;

  for (int i = 0; i < (int)v.size(); ++i)
    end[v[i].second] = i;
}

void erase(int poz) {
  while (st <= dr && dq[st] < poz)
    ++st;
}

void insert(int poz, int val) {
  while (dr >= st && d[dq[dr] - 1] + price[dq[dr]] > val)
    --dr;

  dq[++dr] = poz;
}

void solve() {
  d[0] = 0;
  st = 1; dr = 0;
  insert(1, d[0] + price[1]);

  for (int i = 1; i <= l; ++i) {
    if (end[i] == -1)
      d[i] = d[i - 1];
    else {
      erase(v[end[i]].first);
      d[i] = d[dq[st] - 1] + price[dq[st]];
    }

    insert(i + 1, d[i] + price[i + 1]);
  }

  printf("%d\n", d[l]);
}

int main() {
  freopen("cover.in", "r", stdin);
  freopen("cover.out", "w", stdout);

  read();

  init();

  solve();

  return 0;
}

