#include <cstdio>
#include <vector>

using namespace std;

const int kMaxN = 20, kMaxL = 105, kMaxD = 1005, MOD = 1000000007;

char start[kMaxL], s[kMaxN][kMaxL];

int N, L, NR, put[kMaxD][kMaxL];

vector <pair <int, int> > res;

void read() {
  scanf("%d%d%d\n", &N, &L, &NR);

  for (int i = 0; i < N; ++i)
    fgets(s[i], sizeof(s[i]), stdin);
}

void init() {
  for (int i = 0; i < L; ++i)
    start[i] = '?';

  for (int i = 0; i <= 1000; ++i) {
    put[i][0] = 1;

    for (int j = 1; j < kMaxL; ++j)
      put[i][j] = (1LL * put[i][j - 1] * (i + 26)) % MOD;
  }
}

int query(char str[kMaxL]) {
  int ans = 0;

  for (int i = 0; i < L; ++i)
    if (str[i] == '?')
      ++ans;
  
  return ans;
}

void back(int pos, int sgn, char str[kMaxL]) {
  if (pos >= N) {
    res.push_back(make_pair(sgn, query(str))); 
    return;
  }

  back(pos + 1, sgn, str);

  char newstr[kMaxL];

  for (int i = 0; i < L; ++i)
    if (str[i] != s[pos][i] && str[i] != '?' && s[pos][i] != '?')
      return;
    else 
      newstr[i] = (str[i] != '?' ? str[i] : s[pos][i]);
  
  back(pos + 1, -sgn, newstr);
}

int answer(int C) {
  int ans = 0;

  for (size_t i = 1; i < res.size(); ++i) {
    ans = ans + res[i].first * put[C][res[i].second];
    
    if (ans < 0)
      ans += MOD;
    
    if (ans >= MOD)
      ans -= MOD;
  }
  
  return ans;
}

void solve() {
  int C;
  
  for (int i = 0; i < NR; ++i) {
    scanf("%d", &C);

    printf("%d\n", answer(C));
  }
}

int main() {
  freopen("afacere.in", "r", stdin);
  freopen("afacere.out", "w", stdout);

  read();

  init();

  back(0, -1, start);

  solve();

  return 0;
}
