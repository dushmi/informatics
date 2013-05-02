#include <cstdio>
#include <cassert>
#include <unordered_map>

using namespace std;

const int MOD = 9007, kMaxN = 100005;

unordered_map <int, bool> H;

int d[kMaxN];

inline int mod(int x) {
    if (x < MOD)
        return x;

    return x - MOD;
}

int main() {
    assert(freopen("ccount.in", "r", stdin));
    assert(freopen("ccount.out", "w", stdout));

    int N, K;

    assert(scanf("%d%d", &N, &K) == 2);

    for (int i = 1; i <= K; ++i) {
        int x;
        
        assert(scanf("%d", &x));

        H[x] = 1;
    }

    d[N] = 1;

    for (int i = N; i >= 3; --i)
        if (!H[i])
            d[i - 1] = mod(d[i - 1] + d[i]), d[i - 2] = mod(d[i - 2] + d[i]);

    int ans = 0;

    for (int i = 3; i <= N; ++i)
        if (!H[i])
            ans = mod(ans + d[i]);

    printf("%d\n", ans);

    return 0;
}
