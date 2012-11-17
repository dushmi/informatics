#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

const int kMaxN = 1005;

vector <pair <int, int> > points;

vector <int> vx, norm;

void readPoints() {
    int N, x, y;
    
    assert(scanf("%d", &N));

    for (int i = 1; i <= N; ++i) {
        assert(scanf("%d%d", &x, &y) == 2);
        points.push_back(make_pair(x, y));
        vx.push_back(x);
    }
}

int x, y;

bool comp_left(const int &a, const int &b) {
    return 1LL * (y - points[a].second) * (x - points[b].first) < 1LL * (x - points[a].first) * (y - points[b].second);
}

bool comp_right(const int &a, const int &b) {
    return 1LL * (points[a].second - y) * (points[b].first - x) < 1LL * (points[a].first - x) * (points[b].second - y);
}

vector <int> left, right;

void split(size_t pos) {
    for (size_t i = 0; i < points.size(); ++i)
        if (i != pos) {
            if (points[i].first < points[pos].first)
                left.push_back(i);
            else
                right.push_back(i);
        }
}

int BIT[kMaxN], ans[kMaxN][kMaxN];

int change(int x) {
    return (x & (-x));
}

void insertBIT(int pos) {
    while (pos < kMaxN) {
        ++BIT[pos];
        pos += change(pos);
    }
}

int queryBIT(int pos) {
    int s = 0;

    while (pos > 0) {
        s += BIT[pos];
        pos -= change(pos);
    }

    return s;
}

void compute(size_t pos, vector <int> &v) {
    //clear BIT
    for (int i = 0; i < kMaxN; ++i)
        BIT[i] = 0;

    for (size_t i = 1; i < v.size(); ++i) {
        insertBIT(norm[v[i - 1]]);
        ans[pos][v[i]] = queryBIT(max(norm[pos], norm[v[i]])) - queryBIT(min(norm[pos], norm[v[i]]));
    }
}

void init() {
    //x coordinates normalisation
    sort(vx.begin(), vx.end());
    vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
    for (size_t i = 0; i < points.size(); ++i)
        norm.push_back(lower_bound(vx.begin(), vx.end(), points[i].first) - vx.begin() + 1);
    
    //ans[i][j] = number of points below the line i->j that have the x coordinate between i.x and j.x
    for (size_t i = 0; i < points.size(); ++i) {
        //reset vectors
        left.clear();
        right.clear();

        //split in left and right according to the position of i
        split(i);

        //sort
        x = points[i].first, y = points[i].second;
        sort(left.begin(), left.end(), comp_left);
        sort(right.begin(), right.end(), comp_right);
        
        //compute ans[i][j]
        compute(i, left);
        compute(i, right);
    }
}

int main() {
    assert(freopen("tri2.in", "r", stdin));
    assert(freopen("tri2.out", "w", stdout));

    readPoints();

    init();

    int Q, v[3];

    assert(scanf("%d", &Q));

    for (int i = 1; i <= Q; ++i) {
        assert(scanf("%d%d%d", &v[0], &v[1], &v[2]) == 3);
        
        for (int j = 0; j <= 2; ++j)
            --v[j];

        for (int j = 0; j <= 2; ++j)
            for (int k = j + 1; k <= 2; ++k)
                if (points[v[j]].first > points[v[k]].first)
                    swap(v[j], v[k]);

        x = points[v[0]].first, y = points[v[0]].second;
        if (comp_right(v[1], v[2]))
            printf("%d\n", ans[v[0]][v[2]] - ans[v[0]][v[1]] - ans[v[1]][v[2]] - 1);
        else
            printf("%d\n", ans[v[0]][v[1]] + ans[v[1]][v[2]] - ans[v[0]][v[2]]);
    }   

    return 0;
}
