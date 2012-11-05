// Hamiltonian Cycle in Dense Graph
#include <cstdio>

const int N = 1005;

int n, cycle[N];

bool friends[N][N];

void read() {
  char s[N * N];
  int x;

  scanf("%d\n", &n);

  for (int i = 1; i <= n; ++i) {
    gets(s);

    x = 0;
    
    for (int j = 0; s[j]; ++ j)
      if (s[j] >= '0' && s[j] <= '9')
        x = x * 10 + s[j] - '0';
      else {
        friends[i][x] = friends[x][i] = 1;
        x = 0;
      }
    
    if (x)
      friends[i][x] = friends[x][i] = 1;
  }
}

// initial possible hamiltonian cycle
void init() {
  for (int i = 1; i <= n; ++i)
    cycle[i] = i;
}

// swap the vector
void swap_vec(int a[N]) {
  int aux = 0;

  for (int i = 1; i <= a[0] / 2; ++ i) {
    aux = a[i];
    a[i] = a[a[0] - i + 1];
    a[a[0] - i + 1] = aux;
  }
}

// swap the region between x and y in a circular vector
void swap_region(int x, int y) {
  int v[N];

  v[0] = 0;

  if (y > x) {
    for (int i = x; i <= y; ++i) 
      v[++v[0]] = cycle[i];
    
    swap_vec(v);
    
    v[0] = 0;

    for (int i = x; i <= y; ++i)
      cycle[i] = v[++v[0]];

    return;
  }

  for (int i = x; i <= n; ++i)
    v[++v[0]] = cycle[i];

  for (int i = 1; i <= y; ++i)
    v[++v[0]] = cycle[i];

  swap_vec(v);

  v[0] = 0;

  for (int i = x; i <= n; ++i)
    cycle[i] = v[++v[0]];

  for (int i = 1; i <= y; ++i)
    cycle[i] = v[++v[0]];
}

// edit the hamiltonian cycle
void solve() {
  bool ok = true;

  // remove the holes
  while (ok) {
    ok = false;

    for (int i = 1; i < n; ++i)
      if (!friends[cycle[i]][cycle[i + 1]]) {
        for (int j = i + 1; j < n; ++j)
          if (friends[cycle[i]][cycle[j]] && friends[cycle[i + 1]][cycle[j + 1]]) {
            swap_region(i + 1, j);
            ok = true;
            break;
          }

        if (ok)
          continue;

        if (friends[cycle[i]][cycle[n]] && friends[cycle[i + 1]][cycle[1]]) {
          swap_region(i + 1, n);
          ok = true;
          continue;
        }
        
        for (int j = 1; j < i - 1; ++j)
          if (friends[cycle[i]][cycle[j]] && friends[cycle[i + 1]][cycle[j + 1]]) {
            swap_region(i + 1, j);
            ok = true;
            break;
          }

        if (ok)
          continue;
      }

    if (!friends[cycle[n]][cycle[1]])
      for (int j = 2; j < n - 1; ++j)
        if (friends[cycle[n]][cycle[j]] && friends[cycle[1]][cycle[j + 1]]) {
          swap_region(1, j);
          ok = true;
          break;
        }
  }
}

// print the solution
void print() {
  cycle[n + 1] = cycle[1];

  // verify if the solution is good
  for (int i = 1; i <= n; ++i) 
    if (!friends[cycle[i]][cycle[i + 1]]) {
      printf("No solution");
      return;
    }

  int p1;
  
  for (int i = 1; i <= n; ++ i)
    if (cycle[i] == 1)
      p1 = i;

  for (int i = p1; i <= n; ++i)
    printf("%d ",cycle[i]);
  
  for (int i = 1; i <= p1; ++ i)
    printf("%d ",cycle[i]);
}

int main() {
  read();

  init();

  solve();

  print();
  
  return 0;
}
