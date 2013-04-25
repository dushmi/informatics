#include <cstdio>

int T;

int main() {
    FILE *f = fopen("test.txt", "r");
    FILE *fs = fopen("ans.txt", "w");

    fscanf(f, "%d", &T);
    
    printf("%d\n", T);
    fflush(stdout);

    for (int i = 1; i <= T; ++i) {
        int N, x;
        fscanf(f, "%d%d", &N, &x);
        
        printf("%d\n", N);
        fflush(stdout);

        int type, xc;
        scanf("%d%d", &type, &xc);

        while (type == 0) {
            if (xc < x) {
                printf("1\n");
                fflush(stdout);
            } else if (xc == x) {
                printf("0\n");
                fflush(stdout);
            } else {
                printf("-1\n");
                fflush(stdout);
            }

            scanf("%d%d", &type, &xc);
        }

        if (xc == x)
            fprintf(fs, "OK\n");
        else
            fprintf(fs, "WRONG\n");
    }

    return 0;
}
