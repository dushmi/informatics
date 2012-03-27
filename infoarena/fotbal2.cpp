#include <cstdio>
#include <vector>

using namespace std;

const int N = 50005, INF = 0x3f3f3f3f;

int n, m, points[N], winner[N];

bool used[N];

vector <pair <int, int> > L[N];

void read() {
  int x, y;

  scanf("%d%d", &n, &m);

  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &x, &y);

    L[x].push_back(make_pair(y, i));
    L[y].push_back(make_pair(x, i));
  }
}

bool verif() {
  for (int i = 1; i <= n; ++i)
    if (L[i].size() & 1)
      return 0;

  return 1;
}

void delete_edge(int a, int b) {
  int nro = L[a][L[a].size() - 1].second;

  L[a].pop_back();

  for (int i = 0; i < L[b].size(); ++i)
    if (L[b][i].first == a && L[b][i].second == nro) {
      swap(L[b][i], L[b][L[b].size() - 1]);
      L[b].pop_back();
      return;
    }
}

void euler(int node) {
  int newnode;

  used[node] = 1;

  while (!L[node].empty()) {
    newnode = L[node][L[node].size() - 1].first;
    winner[L[node][L[node].size() - 1].second] = node;
    
    if (node && newnode) {
      ++points[node];
      --points[newnode];
    }
    
    delete_edge(node, newnode);
    euler(newnode);
  }
}

void edit() {
  for (int i = 1; i <= n; ++i)
    if (L[i].size() & 1) {
      L[0].push_back(make_pair(i, 0));
      L[i].push_back(make_pair(0, 0));
    }
}

void print() {
  int min = INF, max = -INF;

  for (int i = 1; i <= n; ++i) {
    if (points[i] > max)
      max = points[i];

    if (points[i] < min)
      min = points[i];
  }

  printf("%d\n", max - min);

  for (int i = 1; i <= m; ++i)
    printf("%d\n", winner[i]);
}

int main() {
  freopen("fotbal2.in", "r", stdin);
  freopen("fotbal2.out", "w", stdout);

  read();

  if (verif()) {
    for (int i = 1; i <= n; ++i)
      if (!used[i])
        euler(i);
  } else {
    edit();

    for (int i = 0; i <= n; ++i)
      if (!used[i])
        euler(i);
  }
  
  print();

  return 0;
}
