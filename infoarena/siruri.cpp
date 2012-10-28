#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

const long long Base = 442501, Base2 = 666013, Mod = 2000007;

const int kMaxN = 100005;

int v[2][kMaxN];

void readVector(int A[kMaxN]) {
  assert(scanf("%d", &A[0]));
  for (int i = 1; i <= A[0]; ++i)
    assert(scanf("%d", &A[i]));
}

void changeVector(int A[kMaxN]) {
  for (int i = 1; i < A[0]; ++i)
    A[i] -= A[i + 1];
  --A[0];
}

void changeSign(int A[kMaxN]) {
  for (int i = 1; i <= A[0]; ++i)
    A[i] *= -1;
}

void add(int A[kMaxN]) {
  for (int i = 1; i <= A[0]; ++i)
    A[i] += 200000;
}

void insertHash(vector <pair <int, int> > hash[Mod], int key, int key2, int pos) {
  hash[key].push_back(make_pair(key2, pos));
}

int queryHash(vector <pair <int, int> > hash[Mod], int key, int key2) {
  for (size_t i = 0; i < hash[key].size(); ++i)
    if (hash[key][i].first == key2)
      return hash[key][i].second;

  return 0;
}

vector <pair <int, int> > hash[Mod];

bool possible(int length) {
  if (length > v[0][0] || length > v[1][0])
    return 0;

  long long currentHash = 0, currentHash2 = 0, power = 1, power2 = 1;

  for (int i = 1; i < length; ++i) {
    power = (power * Base) % Mod;
    power2 = (power2 * Base2) % Mod;
  }

  for (int i = 1; i <= length; ++i) {
    currentHash = ((currentHash * Base) % Mod + v[0][i]) % Mod;
    currentHash2 = ((currentHash2 * Base2) % Mod + v[0][i]) % Mod;
  }

  insertHash(hash, currentHash, currentHash2, 1);

  for (int i = length + 1; i <= v[0][0]; ++i) {
    currentHash = (currentHash - (power * v[0][i - length]) % Mod + Mod) % Mod;
    currentHash2 = (currentHash2 - (power2 * v[0][i - length]) % Mod + Mod) % Mod;
    currentHash = ((currentHash * Base) % Mod + v[0][i]) % Mod;
    currentHash2 = ((currentHash2 * Base2) % Mod + v[0][i]) % Mod;
    insertHash(hash, currentHash, currentHash2, i - length + 1);
  }

  currentHash = 0; currentHash2 = 0;

  for (int i = 1; i <= length; ++i) {
    currentHash = ((currentHash * Base) % Mod + v[1][i]) % Mod;
    currentHash2 = ((currentHash2 * Base2) % Mod + v[1][i]) % Mod;
  }

  if (queryHash(hash, currentHash, currentHash2))
    return 1;

  for (int i = length + 1; i <= v[1][0]; ++i) {
    currentHash = (currentHash - (power * v[1][i - length]) % Mod + Mod) % Mod;
    currentHash2 = (currentHash2 - (power2 * v[1][i - length]) % Mod + Mod) % Mod;
    currentHash = ((currentHash * Base) % Mod + v[1][i]) % Mod;
    currentHash2 = ((currentHash2 * Base2) % Mod + v[1][i]) % Mod;
    if (queryHash(hash, currentHash, currentHash2))
      return 1;
  }

  return 0;
}

void reset(int length) {
  long long currentHash = 0, power = 1;

  for (int i = 1; i < length; ++i)
    power = (power * Base) % Mod;

  for (int i = 1; i <= length; ++i)
    currentHash = ((currentHash * Base) % Mod + v[0][i]) % Mod;
  
  hash[currentHash].clear();

  for (int i = length + 1; i <= v[0][0]; ++i) {
    currentHash = (currentHash - (power * v[0][i - length]) % Mod + Mod) % Mod;
    currentHash = ((currentHash * Base) % Mod + v[0][i]) % Mod;
    hash[currentHash].clear();
  }
}

int binarySearch() {
  int i = 0, pas = 1 << 16;
  
  for (i = 0; pas; pas >>= 1)
    if (possible(i + pas)) {
      reset(i + pas);
      i += pas;
    }

  return i;
}

void solve(int length) {
  printf("%d ", length + 1);
  
  long long currentHash = 0, currentHash2 = 0, power = 1, power2 = 1;

  for (int i = 1; i < length; ++i) {
    power = (power * Base) % Mod;
    power2 = (power2 * Base2) % Mod;
  }

  for (int i = 1; i <= length; ++i) {
    currentHash = ((currentHash * Base) % Mod + v[0][i]) % Mod;
    currentHash2 = ((currentHash2 * Base2) % Mod + v[0][i]) % Mod;
  }

  insertHash(hash, currentHash, currentHash2, 1);
  
  for (int i = length + 1; i <= v[0][0]; ++i) {
    currentHash = (currentHash - (power * v[0][i - length]) % Mod + Mod) % Mod;
    currentHash2 = (currentHash2 - (power2 * v[0][i - length]) % Mod + Mod) % Mod;
    currentHash = ((currentHash * Base) % Mod + v[0][i]) % Mod;
    currentHash2 = ((currentHash2 * Base2) % Mod + v[0][i]) % Mod;
    insertHash(hash, currentHash, currentHash2, i - length + 1);
  }

  currentHash = 0; currentHash2 = 0;

  for (int i = 1; i <= length; ++i) {
    currentHash = ((currentHash * Base) % Mod + v[1][i]) % Mod;
    currentHash2 = ((currentHash2 * Base2) % Mod + v[1][i]) % Mod;
  }

  if (queryHash(hash, currentHash, currentHash2)) {
    printf("%d %d\n", queryHash(hash, currentHash, currentHash2), 1);
    return;
  }

  for (int i = length + 1; i <= v[1][0]; ++i) {
    currentHash = (currentHash - (power * v[1][i - length]) % Mod + Mod) % Mod;
    currentHash2 = (currentHash2 - (power2 * v[1][i - length]) % Mod + Mod) % Mod;
    currentHash = ((currentHash * Base) % Mod + v[1][i]) % Mod;
    currentHash2 = ((currentHash2 * Base2) % Mod + v[1][i]) % Mod;
    if (queryHash(hash, currentHash, currentHash2)) {
      printf("%d %d\n", queryHash(hash, currentHash, currentHash2), i - length + 1);
      return;
    }
  }
}

int main() {
  assert(freopen("siruri.in", "r", stdin));
  assert(freopen("siruri.out", "w", stdout));

  readVector(v[0]); readVector(v[1]);

  changeVector(v[0]); add(v[0]); changeVector(v[1]); changeSign(v[1]); add(v[1]);

  solve(binarySearch());

  return 0;
}
