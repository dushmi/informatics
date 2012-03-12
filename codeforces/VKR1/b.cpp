#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int K = 1005;

int n, k, c[K], t[K];

vector <pair <int, int> > v[2];

vector <int> sol[K];

void read() {
  scanf("%d%d", &n, &k);

  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &c[i], &t[i]);
    v[t[i] - 1].push_back(make_pair(c[i], i));
  }
}

void solve() {
  sort(v[0].begin(), v[0].end());
  sort(v[1].begin(), v[1].end());
  
  for (int i = 1; i <= k && !v[0].empty(); ++i) {
    sol[i].push_back(v[0][v[0].size() - 1].second);
    v[0].pop_back();
  }
  
  for (int i = k; i >= 1; --i)
    if (sol[i].empty()) {
      sol[i].push_back(v[1][v[1].size() - 1].second);
      v[1].pop_back();
    }

  while (!v[0].empty()) {
    sol[k].push_back(v[0][v[0].size() - 1].second);
    v[0].pop_back();
  }

  while (!v[1].empty()) {
    sol[k].push_back(v[1][v[1].size() - 1].second);
    v[1].pop_back();
  }
}

double calc(vector <int> a) {
  double rez = 0, min = 0;

  bool red = 0;

  for (int i = 0; i < (int)a.size(); ++i) {
    if (t[a[i]] == 1)
      red = 1;

    if (c[a[i]] < min || min == 0)
      min = c[a[i]];
    
    rez += c[a[i]];
  }

  if (red) {
    rez -= min;
    rez += 1.0 * min / 2.0;
  }

  return rez;
}

void compute() {
  double rez = 0;

  for (int i = 1; i <= k; ++i)
    rez += calc(sol[i]);

  printf("%.1lf\n", rez);

  for (int i = 1; i <= k; ++i) {
    printf("%d ", (int)sol[i].size());
    
    for (int j = 0; j < (int)sol[i].size(); ++j)
      printf("%d ", sol[i][j]);
    
    printf("\n");
  }
}

int main() {
  read();

  solve();

  compute();

  return 0;
}
