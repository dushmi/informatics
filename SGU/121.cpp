#include <cstdio>
#include <list>
#include <cstdlib>

using namespace std;

const int N = 115;

int n;

bool used[N], col[N][N], d[N][2];

list <int> L[N], L1[N];

void read() {
  int x;

  scanf("%d", &n);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);

    while(x) {
      L[i].push_back(x);

      L1[i].push_back(x);

      scanf("%d", &x);
    }
  }
}

void init() {
  for (int i = 1; i <= n; ++i)
    if (L[i].size() & 1) {
      L[i].push_back(0);
      L[0].push_back(i);
    }
}

void del(int a, int b) {
  L[a].pop_front();
  
  for (list <int> :: iterator it = L[b].begin(); it != L[b].end(); ++it)
    if (*it == a) {
      L[b].erase(it);
      return;
    }
}

void solve(int nod, int c) {
  int next;
  
  used[nod] = 1;

  while (!L[nod].empty()) {
    next = *L[nod].begin();
    del(nod, next);
    if (nod == 0)
      solve(next, -1);
    else {
      if (c == -1) {
        if (!d[nod][0]) {
          d[nod][0] = 1;
          d[next][0] = 1;
          col[nod][next] = col[next][nod] = 0;
          solve(next, 0);
        } else {
          d[nod][1] = 1;
          d[next][1] = 1;
          col[nod][next] = col[next][nod] = 1;
          solve(next, 1);
        }
      } else {
        col[nod][next] = col[next][nod] = !c;
        solve(next, !c);
      }
    }
  }
}

void verif() {
  for (int i = 1; i <= n; ++i) {
    bool c[2];
    c[0] = c[1] = 0;
    
    for (list <int> :: iterator it = L1[i].begin(); it != L1[i].end(); ++it)
      c[col[i][*it]] = 1;

    if ((!c[0] || !c[1]) && L1[i].size() > 1){
      printf("No solution");
      exit(0);
    }
  }
}

void afis() {
  for (int i = 1; i <= n; ++i) {
    for (list <int> :: iterator it = L1[i].begin(); it != L1[i].end(); ++it)
      printf("%d ", col[i][*it] + 1);
  
    printf("0\n");
  }
}

int main() {
  read();

  init();

  for (int i = 0; i <= n; ++i)
    if (!used[i])
      solve(i, -1);

  verif();

  afis();

  return 0;
}
