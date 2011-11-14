#include <cstdio>
#include <set>
#include <vector>
#include <cstdlib>

using namespace std;

const int N = 5005;

int moves, lvl, n, p, k, dad[N], niv[N];

bool red[N];

vector <int> L[N];

multiset <int> empty;

void read() {
  int nr, x;

  scanf("%d%d%d", &n, &p, &k);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &nr);
  
    for (int j = 1; j <= nr; ++j) {
      scanf("%d", &x);
      dad[x] = i;
      L[i].push_back(x);
    }
  }

  for (int i = 1; i <= k; ++i) {
    scanf("%d", &x);
    red[x] = 1;
  }
}

void init(int nod) {
  niv[nod] = lvl;

  ++lvl;

  for (int i = 0; i < (int)L[nod].size(); ++i)
    init(L[nod][i]);

  --lvl;
}

void add_set(int nod) {
  if (!red[nod])
    empty.insert(niv[nod]);

  for (int i = 0; i < (int)L[nod].size(); ++i)
    add_set(L[nod][i]);
}

void rewind(int nod, int next) {
  if (nod == 0)
    return;

  for (int i = 0; i < (int)L[nod].size(); ++i)
    if (L[nod][i] != next)
      add_set(L[nod][i]);

  if (red[nod]) {
    if (empty.empty()) {
      printf("-1\n");
      exit(0);
    }
    
    moves += *empty.begin() - niv[nod];
    empty.erase(empty.begin());
  }

  rewind(dad[nod], nod);
}

int main() {
  freopen("bile7.in", "r", stdin);
  freopen("bile7.out", "w", stdout);

  read();
  
  init(1);

  rewind(dad[p], p);

  printf("%d\n", moves);

  return 0;
}
