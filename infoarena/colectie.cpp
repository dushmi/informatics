#include <cstdio>
#include <cassert>
#include <map>
#include <vector>

using namespace std;

typedef int vec[12];

const int kMaxN = 35;

int ans, N, d[12][2];

vec A, P, NB, options[kMaxN];

vector <int> v, st, aux, sol;

map <vector <int>, vector <int> > h;

void compute(int pos) {
  if (pos == 0)
    return;
 
  if (A[pos] > 0) {
    //this digit is 0
    if (pos == A[0])
      v[0] += d[pos - 1][0];
    else
      v[0] += d[pos - 1][1] + P[pos];
    for (int i = 1; i <= 9; ++i)
      v[i] += d[pos - 1][1];
  
    //this digit is any other digit < A[pos]
    for (int dig = 1; dig < A[pos]; ++dig) {
      v[dig] += P[pos];
      for (int i = 0; i <= 9; ++i)
        v[i] += d[pos - 1][1];
    }
  }

  //this digit is A[pos]
  v[A[pos]] += NB[pos] - A[pos] * P[pos] + 1;

  compute(pos - 1);
}

void init() {
  int K;

  assert(scanf("%d", &K) == 1);
  
  //d[i][0/1] = number of each zero/nonzero digit necessary in
  //            order to build all numbers lower than 10^i
  for (int i = 1, p = 1; i <= 9; ++i, p *= 10) {
    d[i][1] = d[i - 1][1] * 10 + p;
    d[i][0] = 9 * d[i - 1][1] + d[i - 1][0];
  }
  
  while (K) {
    A[++A[0]] = K % 10;
    P[A[0]] = (A[0] == 1) ? 1 : P[A[0] - 1] * 10;
    NB[A[0]] = A[A[0]] * P[A[0]] + NB[A[0] - 1];
    K /= 10;
  }

  for (int i = 0; i <= 9; ++i)
    v.push_back(0);

  compute(A[0]);
}

void insert_map() {
  if (h[aux].empty() || h[aux].size() < st.size())
    h[aux] = st;
}

void check_map() {
  for (int j = 0; j <= 9; ++j)
    v[j] -= aux[j];
  
  if (h[v].size() != 0 && (int)h[v].size() + (int)st.size() <= ans) {
    ans = h[v].size() + st.size();
    
    sol.clear();
    for (size_t i = 0; i < h[v].size(); ++i)
      sol.push_back(h[v][i]);
    for (size_t i = 0; i < st.size(); ++i)
      sol.push_back(st[i]);
  }
  
  for (int j = 0; j <= 9; ++j)
    v[j] += aux[j];
}

//type = 0 => insert in map
//       1 => check in map
void back(int pos, int end, bool type) {
  if (pos == end + 1) {
    if (type == 0)
      insert_map();
    else
      check_map();

    return;
  }
  
  //we don't take this one
  back(pos + 1, end, type);
  
  //we take this one
  for (int j = 0; j <= 9; ++j)
    if (aux[j] + options[pos][j] > v[j])
      return;

  st.push_back(pos);
  for (int j = 0; j <= 9; ++j)
    aux[j] += options[pos][j];
  
  back(pos + 1, end, type);
  
  for (int j = 0; j <= 9; ++j)
    aux[j] -= options[pos][j];
  st.pop_back();
}

void print() {
  if (ans == kMaxN) {
    printf("0\n");
    return;
  }

  printf("1\n");
  printf("%d\n", ans);
  for (size_t i = 0; i < sol.size(); ++i)
    printf("%d ", sol[i]);
}

int main() {
  assert(freopen("colectie.in", "r", stdin));
  assert(freopen("colectie.out", "w", stdout));

  assert(scanf("%d", &N) == 1);

  init();

  for (int i = 1; i <= N; ++i)
    for (int j = 0; j <= 9; ++j)
      assert(scanf("%d", &options[i][j]) == 1);

  for (int i = 0; i <= 9; ++i)
    aux.push_back(0);
  st.clear();
  back(1, N / 2, 0);
  
  ans = kMaxN;
  sol.clear();
  back(N / 2 + 1, N, 1);

  print();

  return 0;
}
