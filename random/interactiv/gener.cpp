#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
    freopen("test.txt", "w", stdout);

    int T = rand() % 10 + 1;

    printf("%d\n", T);

    for (int i = 1; i <= T; ++i) {
        int lim = rand() % 1000000 + 1;
        int x = rand() % lim + 1;

        printf("%d %d\n", lim, x);
    }

    return 0;
}
