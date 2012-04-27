#include <cstdio>
#include <algorithm>
#include <deque>
#include <vector>
#include <cassert>

using namespace std;

const int INF = 0x3f3f3f3f, kMaxN = 15005, kMaxM = 200005;

struct Train {
  int A, B, C, T[2];
};

Train v[kMaxM];

vector <pair <int, int> > events;

int cc, N, M, money, din[kMaxM];

deque <pair <int ,int> > dq[kMaxN];

void read() {
  char s[70];

  assert(scanf("%d%d%d\n", &N, &M, &money));

  for (int i = 1; i <= M; ++i) {
    assert(fgets(s, sizeof(s), stdin));

    int pos = 0;
    for (;s[pos] >= '0' && s[pos] <= '9'; ++pos) v[i].A = v[i].A * 10 + s[pos] - '0'; ++pos;
    for (;s[pos] >= '0' && s[pos] <= '9'; ++pos) v[i].B = v[i].B * 10 + s[pos] - '0'; ++pos;
    for (;s[pos] >= '0' && s[pos] <= '9'; ++pos) v[i].C = v[i].C * 10 + s[pos] - '0'; ++pos;
    for (;s[pos] >= '0' && s[pos] <= '9'; ++pos) v[i].T[0] = v[i].T[0] * 10 + s[pos] - '0'; ++pos;
    for (;s[pos] >= '0' && s[pos] <= '9'; ++pos) v[i].T[1] = v[i].T[1] * 10 + s[pos] - '0'; ++pos;
  }
}

void train_departs(int ind, int delayc) {
  int city = v[ind].A;

  while (!dq[city].empty() && dq[city].front().first + delayc < v[ind].T[0])
    dq[city].pop_front();

  if (!dq[city].empty()) 
    din[ind] = min(din[ind], dq[city].front().second + v[ind].C);
  
  if (v[ind].B == N)
    cc = min(cc, din[ind]);
}

void train_arrives(int ind) {
  int city = v[ind].B;

  while (!dq[city].empty() && dq[city].back().second > din[ind])
    dq[city].pop_back();

  if (din[ind] != INF)
    dq[city].push_back(make_pair(v[ind].T[1], din[ind]));
}

bool solve(int delayc) {
  for (int i = 0; i < (int)events.size(); ++i) 
    if (events[i].second == 0)
      train_departs(events[i].first, delayc);
    else
      train_arrives(events[i].first);

  return (cc <= money);
}

bool comp(pair <int, int> a, pair <int, int> b) {
  if (v[a.first].T[a.second] == v[b.first].T[b.second])
    return (a.second > b.second);
  
  return (v[a.first].T[a.second] < v[b.first].T[b.second]);
}

void init() {
  for (int i = 1; i <= M; ++i) {
    events.push_back(make_pair(i, 0));
    events.push_back(make_pair(i, 1));
  }
  
  sort(events.begin(), events.end(), comp);
}

void reset() {
  cc = INF;
  
  for (int i = 1; i <= N; ++i)
    dq[i].clear();

  for (int i = 1; i <= M; ++i)
    if (v[i].A == 1 && v[i].C <= money)
      din[i] = v[i].C;
    else
      din[i] = INF;
}

void cautb() {
  int left = 0, right = 200000, mid = 0, t = 0, c = 0;

  while (left <= right) {
    mid = (left + right) / 2;

    reset();
    
    if (solve(mid)) {
      t = mid;
      c = cc;
      right = mid - 1;
    } else
      left = mid + 1;
  }

  printf("%d %d\n", t, c);
}

int main() {
  assert(freopen("trenuri.in", "r", stdin));
  assert(freopen("trenuri.out", "w", stdout));

  read();

  init();

  cautb();

  return 0;
}
