#include <cstdio>
#include <cassert>

const int kMaxN = 33;

long double x0[kMaxN], p[kMaxN], y[kMaxN], ans[kMaxN][kMaxN], aux[kMaxN][kMaxN];

int N, M;

void read() {
    assert(scanf("%d%d", &N, &M));
    
    for (int i = 1; i <= N; ++i)
        assert(scanf("%Lf", &x0[i]));

    for (int i = 1; i <= N; ++i)
        assert(scanf("%Lf", &p[i]));

    for (int i = 1; i <= N; ++i)
        assert(scanf("%Lf", &y[i]));
}

void multiply(long double r[kMaxN][kMaxN], long double a[kMaxN][kMaxN], long double b[kMaxN][kMaxN]) {
    long double c[kMaxN][kMaxN];

    for (int i = 1; i <= N + 1; ++i)
        for (int j = 1; j <= N + 1; ++j) {
            c[i][j] = 0;

            for (int k = 1; k <= N + 1; ++k)
                c[i][j] += a[i][k] * b[k][j];
        }
    
    for (int i = 1; i <= N + 1; ++i)
        for (int j = 1; j <= N + 1; ++j)
            r[i][j] = c[i][j];
}

int main() {
    assert(freopen("ecu.in", "r", stdin));
    assert(freopen("ecu.out", "w", stdout));

    read();

    //build initial ans
    for (int i = 1; i <= N + 1; ++i)
        ans[i][i] = 1;
    
    //build aux
    for (int i = 1; i <= N; ++i) {
        aux[i][i] = p[i];
        aux[i][i % N + 1] = 1.0 - p[i % N + 1];
        aux[i][N + 1] = y[i];
    }
    aux[N + 1][N + 1] = 1;
    
    while (M) {
        if (M & 1)
            multiply(ans, ans, aux);

        multiply(aux, aux, aux);
        M >>= 1;
    }

    for (int i = 1; i <= N; ++i) {
        long double x = 0;
        for (int j = 1; j <= N; ++j)
            x += ans[i][j] * x0[j];
        x += ans[i][N + 1];
        
        printf("%.3Lf ", x);
    }

    return 0;
}
