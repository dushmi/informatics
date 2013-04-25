#include <cstdio>

int T;

int binarySearch(int MAXV) {
    int pas = (1 << 20), i = 0;

    for (i = 0; pas; pas >>= 1)
        if (i + pas <= MAXV) {
            printf("0 %d\n", i + pas);
            fflush(stdout);

            int ans;
            scanf("%d", &ans);

            if (ans == 0)
                return i + pas;

            if (ans == 1)
                i += pas;
        }

    return i + 1;
}

int main() {
    scanf("%d", &T);

    for (int i = 1; i <= T; ++i) {
        int N;
        scanf("%d", &N);

        printf("1 %d\n", binarySearch(N));
        fflush(stdout);
    }

    return 0;
}
