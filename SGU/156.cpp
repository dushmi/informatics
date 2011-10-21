#include <cstdio>
#include <vector>

using namespace std;

const int N = 10015;

vector <int> E, C[N], L[N], G[N]; 
// E = eulerian cycle on the super graph
// C[i] = members of the ith clique
// L = initial graph
// G = super graph

int n, nb_cliques, dim[N], deg[N], clique[N];
// clique[i] = the clique of the ith node
// dim[i] = number of nodes in the ith clique

bool used[N];

void read() {
  int x, y, m;

  scanf("%d%d", &n, &m);

  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    
    L[x].push_back(y);
    L[y].push_back(x);
    
    ++deg[x];
    ++deg[y];
  }
}

// mark all the neigbors from node's clique  
void solve_clique(int node) {
  clique[node] = ++nb_cliques;
  
  for (int i = 0; i < (int)L[node].size(); ++i)
    if (deg[L[node][i]] > 2)
      clique[L[node][i]] = nb_cliques;
}

// determine cliques
void det_cliques() {
  for (int i = 1; i <= n; ++i) 
    if (deg[i] == 2) { // i is an intermediary node between 2 cliques
      if (!clique[L[i][0]] && deg[L[i][0]] > 2)
        solve_clique(L[i][0]);
      if (!clique[L[i][1]] && deg[L[i][1]] > 2)
        solve_clique(L[i][1]);
    }
}

void reset_vector(int v[N]) {
  for (int i = 1; i <= n; ++i)
    deg[i] = 0;
}

// build the super graph( each clique is a node)
void build_super_graph() {
  for (int i = 1; i <= n; ++i)
    if (!clique[i])
      clique[i] = ++nb_cliques;

  reset_vector(deg);

  for (int i = 1; i <= n; ++i) {
    ++dim[clique[i]];
    C[clique[i]].push_back(i);
  }

  for (int i = 1; i <= n; ++i)
      for (int j = 0; j < (int)L[i].size(); ++j)
        if (clique[L[i][j]] != clique[i]) {
          G[clique[i]].push_back(clique[L[i][j]]);
          ++deg[clique[i]];
        }
}

void df(int node) {
  used[node] = 1;

  for (int i = 0; i < (int)G[node].size(); ++i)
    if (!used[G[node][i]])
      df(G[node][i]);
}

// verify if each node in G has even degree and if G is conex
bool eulerian_graph_verification() {
  df(1);

  for (int i = 1; i <= nb_cliques; ++i)
    if (!used[i])
      return 0;

  for (int i = 1; i <= nb_cliques; ++i)
    if (deg[i] % 2 == 1)
      return 0;

  return 1;
}

void eulerian_cycle(int node) {
  int w;

  E.push_back(node);

  while (!G[node].empty()) {
    w = G[node][(int)G[node].size() - 1];
    
    G[node].pop_back();
    
    for (int i = 0; i < (int)G[w].size(); ++i)
      if (G[w][i] == node) {
        swap(G[w][i], G[w][G[w].size() - 1]);
        G[w].pop_back();
        break;
      }

    eulerian_cycle(w);
  }
}

// print the solution
void print() {
  int last_node = 0;
  
  for (int i = 0; i < (int)C[1].size(); ++i) {
    for (int j = 0; j < (int)L[C[1][i]].size(); ++j)
      if (clique[L[C[1][i]][j]] == E[1]) {
        last_node = C[1][i];
        break;
      }

    if (last_node)
      break;
  }

  --dim[1];
  printf("%d ", last_node);

  for (int i = 1; i < (int)E.size() - 1; ++ i) {
    for (int j = 0; j < (int)L[last_node].size(); ++j)
      if (clique[L[last_node][j]] == E[i]) {
        last_node = L[last_node][j];
        break;
      }
    
    --dim[E[i]];
    printf("%d ", last_node);
      
    int aux = last_node;

    for (int c = 0; c < (int)C[E[i]].size(); ++c) {
      for (int j = 0; j < (int)L[C[E[i]][c]].size(); ++j)
        if (clique[L[C[E[i]][c]][j]] == E[i + 1]) {
          last_node = C[E[i]][c];
          break;
        }
    
      if (last_node != aux)
        break;
    }
    
    if (last_node != aux) {
      --dim[E[i]];
      printf("%d ", last_node);
    }
  }

  if (dim[E[E.size() - 1]] > 0) {
    for (int j = 0; j < (int)L[last_node].size(); ++j)
      if (clique[L[last_node][j]] == E[E.size() - 1]) {
        last_node = L[last_node][j];
        break;
      }
    
    printf("%d ", last_node);
  }
}

int main() {
  read();

  det_cliques();

  build_super_graph();
  
  if (eulerian_graph_verification()) {
    eulerian_cycle(1);
    print();
  } else
    printf("-1");

  return 0;
}
