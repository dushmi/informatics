#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>

using namespace std;

const int S = 0, D = 1, kMaxN = 55, INF = 0x3f3f3f3f;

struct edge {
    int x, y, c, f;

    edge() {
        x = y = c = f = 0;
    }

    edge(int _x, int _y, int _c) {
        x = _x; y = _y; c = _c; f = 0;
    }
};

int N, M, current, target, used[kMaxN * kMaxN * 2], pred[kMaxN * kMaxN * 2];

vector <edge> temp, list;

vector <int> graph[kMaxN * kMaxN * 2];

int change(int n, int t) {
    return (1 + n + N * t);  
}

void update_graph(int t) {
    for (size_t i = 0; i < temp.size(); ++i) {
        int n1 = change(temp[i].x, t - 1), n2 = change(temp[i].y, t);
        list.push_back(edge(n1, n2, temp[i].c));
        graph[n1].push_back(list.size() - 1);
        graph[n2].push_back(list.size() - 1);
    }

    for (int i = 1; i <= N; ++i) {
        int n1 = change(i, t - 1), n2 = change(i, t);
        list.push_back(edge(n1, n2, INF));
        graph[n1].push_back(list.size() - 1);
        graph[n2].push_back(list.size() - 1);
    }

    list.push_back(edge(change(1, t), D, target));
    graph[change(1, t)].push_back(list.size() - 1);
    graph[D].push_back(list.size() - 1);
}

queue <int> Q;

void move(int n, int i) {
    if (list[i].x == n && list[i].f < list[i].c && !used[list[i].y]) {
        used[list[i].y] = 1;
        pred[list[i].y] = i;
        Q.push(list[i].y);
        return;
    } 

    if (list[i].y == n && list[i].f > 0 && !used[list[i].x]) {
        used[list[i].x] = 1;
        pred[list[i].x] = i;
        Q.push(list[i].x);
        return;
    }
}

bool BFS() {
    for (int i = 1; i < kMaxN * kMaxN * 2; ++i)
        used[i] = 0, pred[i] = 0;

    used[S] = 1;
    Q.push(S);

    while (!Q.empty()) {
        int n = Q.front(); Q.pop();

        for (size_t i = 0; i < graph[n].size(); ++i)
            move(n, graph[n][i]);
    }

    return used[D];
}

void compute(int n, int i, int &val) {
    if (list[i].y == n)
        val = min(val, list[i].c - list[i].f);
    else
        val = min(val, list[i].f);
}

void update(int n, int i, int val) {
    if (list[i].y == n) 
        list[i].f += val;
    else
        list[i].f -= val;
}

int other(int n, int i) {
    if (list[i].x == n)
        return list[i].y;
    return list[i].x;
}

void solve() {
    while (BFS()) {
        int val = INF;
        for (int n = D; pred[n]; n = other(n, pred[n]))
            compute(n, pred[n], val);
        for (int n = D; pred[n]; n = other(n, pred[n]))
            update(n, pred[n], val);
        current += val;
    }
}

int main() {
    assert(freopen("algola.in", "r", stdin));
    assert(freopen("algola.out", "w", stdout));

    assert(scanf("%d%d", &N, &M) == 2);

    int x, y, c;

    for (int i = 1; i <= N; ++i) {
        assert(scanf("%d", &x));
        
        target += x;
        
        list.push_back(edge(S, i + 1, x));
        graph[S].push_back(list.size() - 1);
        graph[i + 1].push_back(list.size() - 1);
    }

    list.push_back(edge(2, D, target));
    graph[2].push_back(list.size() - 1);
    graph[D].push_back(list.size() - 1);

    for (int i = 1; i <= M; ++i) {
        assert(scanf("%d%d%d", &x, &y, &c) == 3);
    
        temp.push_back(edge(x, y, c)); 
        temp.push_back(edge(y, x, c));
    }

    int time;
    
    for (time = 1; current != target; ++time) {
        update_graph(time);
        solve();
    }

    printf("%d", time - 1);

    return 0;
}
