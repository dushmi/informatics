#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

const int kMaxN = 2 * 32005;

int z[kMaxN], zp[kMaxN], ans[kMaxN], s[2][kMaxN], n[2][kMaxN], d[2][kMaxN];

void df(int node, vector <int> v[kMaxN], int nb) {
  s[nb][++s[nb][0]] = 0; 
  n[nb][s[nb][0]] = node;
  
  for (size_t i = 0; i < v[node].size(); ++i)
    df(v[node][i], v, nb);

  s[nb][++s[nb][0]] = 1;
}

void readTree(int nb) {
  vector <int> v[kMaxN];
  int N;

  assert(scanf("%d", &N) == 1);

  for (int i = 1; i <= N; ++i) {
    int L, x;

    assert(scanf("%d", &L) == 1); 

    for (int j = 1; j <= L; ++j) {
      assert(scanf("%d", &x) == 1);
      v[i].push_back(x);
    }
  }

  df(1, v, nb);

  for (int i = 1; i <= s[nb][0]; ++i) {
    d[nb][i] = d[nb][i - 1];
    
    if (n[nb][i] != 0)
      ++d[nb][i];
  }
}

void _ZAlgorithmInit() {
  int j = 1;
  
  for (int i = 2; i <= s[0][0]; ++i) {
    if (j + z[j] <= i)
      z[i] = 0;
    else 
      z[i] = min(z[i - j + 1], j + z[j] - i);
    
    while (s[0][i + z[i]] == s[0][1 + z[i]] && i + z[i] <= s[0][0])
      ++z[i];  

    if (i + z[i] > j + z[j])
      j = i;
  }
}

void _ZAlgorithm() {
  int j = 0;
  
  for (int i = 1; i <= s[1][0]; ++i) {
    if (j + zp[j] <= i)
      zp[i] = 0;
    else
      zp[i] = min(z[i - j + 1], j + zp[j] - i);
    
    while (s[1][i + zp[i]] == s[0][1 + zp[i]] && i + zp[i] <= s[1][0] && 1 + zp[i] <= s[0][0])
      ++zp[i];
    
    if (i + zp[i] > j + zp[j])
      j = i;
  
    ans[n[1][i]] = d[0][zp[i]];
  }
}

void printAnswers() {
  for (int i = 1; i <= d[1][s[1][0]]; ++i)
    printf("%d\n", ans[i]);
}

int main() {
  assert(freopen("arbfind.in", "r", stdin));
  assert(freopen("arbfind.out", "w", stdout));

  readTree(0);
  readTree(1);

  _ZAlgorithmInit();
  _ZAlgorithm();

  printAnswers();

  return 0;
}
