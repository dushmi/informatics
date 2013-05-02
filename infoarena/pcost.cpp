#include <cstdio>
#include <cassert>
#include <unordered_map>

using namespace std;

unordered_map <int, int> H;

void solve(int x) {
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0) {
            ++H[i];

            while (x % i == 0)
                x /= i;
        }
    
    if (x != 1)
        ++H[x];
}

int main() {
    assert(freopen("pcost.in", "r", stdin));
    assert(freopen("pcost.out", "w", stdout));
    
    int N;

    assert(scanf("%d", &N));

    for (int i = 1; i <= N; ++i) {
        int x;

        assert(scanf("%d", &x));

        solve(x);
    }

    long long ans = 0;

    for (auto it: H)
        ans += 1LL * it.second * (it.second - 1) / 2 * it.first * it.first;
    
    printf("%lld\n", ans);

    return 0;
}
