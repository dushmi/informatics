#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int N = 65, INF = 0x3f3f3f3f;

int n, S, D, rez, in[N], out[N], dist[N], dad[N], cap[N][N], flow[N][N], tax[N][N];

bool inq[N];

vector <int> L[N];

queue <int> Q;

inline int min(int x, int y) {
  return x < y ? x : y;
}

void read() {
  int m, x, y, d;

  scanf("%d%d", &n, &m);

  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &x, &y, &d);
    
    L[x].push_back(y);
    L[y].push_back(x);

    cap[x][y] = INF;

    ++out[x];
    ++in[y];

    tax[x][y] = d;
    tax[y][x] = -d;

    rez += d;
  }
}

void init_flow() {
  S = 0;
  D = n + 1;

  for (int i = 1; i <= n; ++i) 
    if (in[i] > out[i]) {
      L[S].push_back(i);
      cap[S][i] = in[i] - out[i];
    } else  if (out[i] > in[i]) {
      L[i].push_back(D);
      cap[i][D] = out[i] - in[i];
    }
}

bool BF() {
  int node;

  for (int i = S; i <= D; ++i)
    dist[i] = INF, dad[i] = -1;

  dist[S] = 0;
  dad[S] = 0;

  Q.push(S);
  inq[S] = 1;
  
  while (!Q.empty()) {
    node = Q.front();
    Q.pop();
    inq[node] = 0;

    for (int j = 0; j < (int)L[node].size(); ++j)
      if (flow[node][L[node][j]] < cap[node][L[node][j]] && dist[L[node][j]] > dist[node] + tax[node][L[node][j]]) {
        dist[L[node][j]] = dist[node] + tax[node][L[node][j]];
        dad[L[node][j]] = node;

        if (!inq[L[node][j]]) {
          Q.push(L[node][j]);
          inq[L[node][j]] = 1;
        }
      }
  }

  return (dist[D] != INF);
}

int compute_flow(int node) {
  int rez = INF;

  while (node) {
    rez = min(rez, cap[dad[node]][node] - flow[dad[node]][node]);
    node = dad[node];
  }

  return rez;
}

void send_flow(int node, int val) {
  while (node) {
    flow[dad[node]][node] += val;
    flow[node][dad[node]] -= val;
    node = dad[node];
  }
}

void mfmc() {
  int cflow = 0;

  while (BF()) {
    cflow = 0;
    
    cflow = compute_flow(D);
    
    send_flow(D, cflow);
    
    rez += cflow * dist[D];
  }
}

int main() {
  freopen("traseu.in", "r", stdin);
  freopen("traseu.out", "w", stdout);

  read();
  
  init_flow();
 
  mfmc();

  printf("%d\n", rez);

  return 0;
}
