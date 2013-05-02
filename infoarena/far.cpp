#include <cstdio>
#include <cassert>

long long count(int x, int p) {
    long long ans = 0, fc = p;

    while (fc <= x) {
        ans += x / fc;
        fc *= p;
    }

    return ans;
}

void solve() {
    int N, M, P;

    assert(scanf("%d%d%d", &N, &M, &P) == 3);

    for (int i = 2; i * i <= P; ++i)
        if (P % i == 0) {
            int nc = 0;

            while (P % i == 0) {
                P /= i;
                ++nc;
            }

            if (nc > count(N + M - 2, i) - count(N - 1, i) - count(M - 1, i)) {
                printf("0\n");
                return;
            }
        }
    
    if (P != 1 && 1 > count(N + M - 2, P) - count(N - 1, P) - count(M - 1, P)) {
        printf("0\n");
        return;
    }

    printf("1\n");
}

int main() {
    assert(freopen("far.in", "r", stdin));
    assert(freopen("far.out", "w", stdout));

    int T;

    assert(scanf("%d", &T));

    for (int i = 1; i <= T; ++i) 
        solve();

    return 0;
}
