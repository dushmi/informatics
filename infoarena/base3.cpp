#include <cstdio>
#include <cassert>
#include <queue>

using namespace std;

const int kMaxN = 16005, kMaxD = 2 * kMaxN, INF = 0x3f3f3f3f;

char A[kMaxN], B[kMaxN], C[kMaxN]; 

int LA, LB, LC, d[kMaxD];

priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > H;

void get_length(char X[kMaxN], int &LX) {
    for (LX = 0; '0' <= X[LX] && X[LX] <= '2'; ++LX);
}

inline int abs(int x) {
    return x > 0 ? x : (-x);
}

inline int min(int x, int y) {
    return x < y ? x : y;
}

void compute(char X[kMaxN], int LX) {
    for (int i = 0; i < LX; ++i)
        if (X[i] == '1')
            d[abs(i - (LX - i - 1))] = min(d[abs(i - (LX - i - 1))], LX);
}

void init() {
    for (int i = 0; i < kMaxD; ++i)
        d[i] = INF;

    compute(A, LA);
    compute(B, LB);
    compute(C, LC);
    
    for (int i = 0; i < kMaxD; ++i)
        if (d[i] != INF) 
            H.push(make_pair(d[i], i));
}

void send(int c, int n, int LX) {
    if (n + LX < kMaxD && d[n + LX] > c + LX) {
        H.push(make_pair(c + LX, n + LX));
        d[n + LX] = c + LX;
    }

    if (abs(n - LX) < kMaxD && d[abs(n - LX)] > c + LX) {
        H.push(make_pair(c + LX, abs(n - LX)));
        d[abs(n - LX)] = c + LX;
    }
}

void solve() {
    while (!H.empty()) {
        int c = H.top().first, n = H.top().second;
        H.pop();

        if (d[n] < c)
            continue;

        if (n == 0)
            break;

        send(c, n, LA);
        send(c, n, LB);
        send(c, n, LC);
    }
}

int main() {
    assert(freopen("base3.in", "r", stdin));
    assert(freopen("base3.out", "w", stdout));

    assert(fgets(A, sizeof(A), stdin));
    assert(fgets(B, sizeof(B), stdin));
    assert(fgets(C, sizeof(C), stdin));

    get_length(A, LA);
    get_length(B, LB);
    get_length(C, LC);
    
    init();

    solve();

    printf("%d\n", (d[0] == INF ? 0 : d[0]));

    return 0;
}
