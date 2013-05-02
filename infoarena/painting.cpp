#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

const int kMaxN = 100005;

int N, M, color[kMaxN], time[kMaxN], ans[kMaxN];

bool used[kMaxN];

vector <int> v[kMaxN];

void solve(int node, int lc, int lt) {
    used[node] = 1;

    if (time[node] > lt) {
        lc = color[node];
        lt = time[node];
    }

    ans[node] = lc;

    for (auto it: v[node])
        if (!used[it])
            solve(it, lc, lt);
}

int main() {
    assert(freopen("painting.in", "r", stdin));
    assert(freopen("painting.out", "w", stdout));

    assert(scanf("%d%d", &N, &M) == 2);

    color[1] = 1;
    time[1] = 0;

    for (int i = 1; i < N; ++i) {
        int x, y;

        assert(scanf("%d%d", &x, &y));

        v[x].push_back(y);
        v[y].push_back(x);
    }

    for (int i = 1; i <= M; ++i) {
        int x, y;
        
        assert(scanf("%d%d", &x, &y));

        color[x] = y;
        time[x] = i;
    }

    solve(1, 0, -1);

    for (int i = 1; i <= N; ++i)
        printf("%d ", ans[i]);

    return 0;
}
