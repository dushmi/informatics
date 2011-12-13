#include <cassert>
#include <cstdio>

const int N = 1000005;

char s[N], a[N << 1];

int n, c, mdr, d[N << 1];

void edit() {
    for (int i = 1; s[i]; ++i) {
        n = 2 * i;
        a[2 * i - 1] = s[i];
        a[2 * i] = '?';
    }
    --n;
}

void extinde(int poz, int dr, int st) {
    c = poz;
    mdr = dr - 1;

    while (st > 0 && dr <= n && a[dr] == a[st]) {
        ++d[poz];
        mdr = dr;
        ++dr;
        --st;
    }
}

void solve() {
    for (int i = 1; i <= n; ++i)
        if (mdr > i) {   
            if (c - (i - c) - d[c - (i - c)] > c - d[c])
                d[i] = d[c - (i - c)];
            else {
                d[i] = mdr - i;
                extinde(i, i + d[i] + 1, i - d[i] - 1);
            }
        } else
            extinde (i, i + 1, i - 1);
}

void afis() {
    long long rez = 0;

    for (int i = 1; i <= n; ++i)
        rez += (d[i] + 1 - i % 2)/ 2 + i % 2;

    printf("%lld", rez);
}

int main() {
    assert(freopen("pscpld.in", "r", stdin));
    assert(freopen("pscpld.out", "w", stdout));

    assert(scanf("%s", s + 1) == 1);
    
    edit();

    solve();

    afis();

    return 0;
}

