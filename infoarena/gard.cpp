#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

struct employee {
    int length, salary, position;
};

const int kMaxN = 16005, kMaxK = 105;

employee worker[kMaxK];

int N, K, left, right, deque[kMaxN], d[kMaxK][kMaxN];

bool comp(const employee &a, const employee &b) {
    return a.position < b.position;
}

void eraseLeft(int workerID, int position) {
    while (position - deque[left] >= worker[workerID].length)
        ++left;
}

void insert(int workerID, int position) {
    while (d[workerID - 1][deque[right] - 1] + worker[workerID].salary * (position - deque[right] + 1) 
          < d[workerID - 1][position - 1] + worker[workerID].salary && right >= left)
        --right;

    deque[++right] = position;
}

int main() {
    assert(freopen("gard.in", "r", stdin));
    assert(freopen("gard.out", "w", stdout));

    assert(scanf("%d%d", &N, &K) == 2);

    for (int i = 1; i <= K; ++i)
        assert(scanf("%d%d%d", &worker[i].length, &worker[i].salary, &worker[i].position) == 3);

    sort(worker + 1, worker + K + 1, comp);

    int ans = 0;

    for (int i = 1; i <= K; ++i) {
        left = 1; right = 0;
        
        for (int j = 1; j < worker[i].position; ++j) {
            d[i][j] = d[i - 1][j];
            eraseLeft(i, j);
            insert(i, j);
        }

        insert(i, worker[i].position);

        for (int j = worker[i].position; j < worker[i].position + worker[i].length && j <= N; ++j) {
            eraseLeft(i, j);
            d[i][j] = max(d[i - 1][j], d[i][deque[left] - 1] + worker[i].salary * (j - deque[left] + 1));
            ans = max(ans, d[i][j]);
        }

        for (int j = worker[i].position + worker[i].length; j <= N; ++j)
            d[i][j] = d[i - 1][j];
    }

    printf("%d\n", ans);

    return 0;
}
