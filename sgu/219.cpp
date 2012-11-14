#include <cstdio>
#include <cassert>
#include <queue>

using namespace std;

const int kMaxN = 1005;

int number, N, v[kMaxN], comp[kMaxN], input[kMaxN], zero[kMaxN]; 

vector <pair <int, int> > graph[kMaxN], graphT[kMaxN];

bool state[kMaxN], used[kMaxN], super[kMaxN][kMaxN];

void makeVector(int n) {
    used[n] = 1;
    for (size_t i = 0; i < graph[n].size(); ++i)
        if (!used[graph[n][i].first])
            makeVector(graph[n][i].first);
    v[++v[0]] = n;
}

void markComponent(int n) {
    used[n] = 1;
    for (size_t i = 0; i < graphT[n].size(); ++i)
        if (!used[graphT[n][i].first]) {
            comp[graphT[n][i].first] = comp[n];
            markComponent(graphT[n][i].first);
        }
}

void stronglyConnectedComponents() {
    for (int i = 1; i <= N; ++i)
        if (!used[i])
            makeVector(i);

    for (int i = 1; i <= N; ++i)
        used[i] = 0;

    for (int i = N; i >= 1; --i) 
        if (!used[v[i]]) {
            ++number;
            comp[v[i]] = number;
            markComponent(v[i]);
        }
}

void createSuperGraph() {
    for (int i = 1; i <= N; ++i)
        for (size_t j = 0; j < graph[i].size(); ++j)
            if (comp[i] != comp[graph[i][j].first] && !super[comp[i]][comp[graph[i][j].first]])
                super[comp[i]][comp[graph[i][j].first]] = 1, ++input[comp[graph[i][j].first]];
}

bool testComponent(int nc) {
    queue <int> Q;

    for (int i = 1; i <= N; ++i)
        if (comp[i] == nc)
            for (size_t j = 0; j < graph[i].size(); ++j)
                if (comp[graph[i][j].first] == nc && graph[i][j].second == 0) 
                    ++zero[graph[i][j].first];

    for (int i = 1; i <= N; ++i)
        if (comp[i] == nc && zero[i] == 0) {
            used[i] = 1;
            Q.push(i);
        }
    
    while (!Q.empty()) {
        int n = Q.front();
        Q.pop();

        for (size_t i = 0; i < graph[n].size(); ++i)
            if (comp[graph[n][i].first] == nc) {
                if (graph[n][i].second == 0) {
                    graph[n][i].second = 1;
                    --zero[graph[n][i].first];
                }
                
                if (zero[graph[n][i].first] == 0 && !used[graph[n][i].first]) {
                    used[graph[n][i].first] = 1;
                    Q.push(graph[n][i].first);
                }
            }
    }

    for (int i = 1; i <= N; ++i)
        if (comp[i] == nc && !used[i])
            return 0;
    
    return 1;
}

void solve() {
    queue <int> Q;

    for (int i = 1; i <= number; ++i)
        state[i] = 1;

    for (int i = 1; i <= number; ++i)
        if (input[i] == 0)
            Q.push(i);

    for (int i = 1; i <= N; ++i)
        used[i] = 0;

    while (!Q.empty()) {
        int n = Q.front(); 
        Q.pop();
    
        if (state[n])
            state[n] = (state[n] & testComponent(n));

        for (int i = 1; i <= number; ++i)
            if (super[n][i]) {
                state[i] = (state[i] & state[n]);
                --input[i];
                if (input[i] == 0)
                    Q.push(i);
            }
    }
}

void print() {
    for (int i = 1; i <= N; ++i)
        printf("%d\n", state[comp[i]]);
}

int main() {
    int M, x, y, v;
    
    assert(scanf("%d%d", &N, &M) == 2);

    for (int i = 1; i <= M; ++i) {
        assert(scanf("%d%d%d", &x, &y, &v) == 3);
        graph[x].push_back(make_pair(y, v));
        graphT[y].push_back(make_pair(x, v));
    }

    stronglyConnectedComponents();
    
    createSuperGraph();

    solve();

    print();

    return 0;
}
