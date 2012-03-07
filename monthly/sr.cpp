#include <cstdio>
#include <cassert>

const int N = 100005;

char A[N], B[N];

int main() {
  assert(freopen("sr.in", "r", stdin));
  assert(freopen("sr.out", "w", stdout));

  assert(fgets(A, sizeof(A), stdin));
  assert(fgets(B, sizeof(B), stdin));

  int pA = -1;

  for (int i = 0; B[i] >= 'a' && B[i] <= 'z'; ++i) {
    while (A[++pA] != B[i]);
    
    printf("%d ", pA + 1);
  }
  
  return 0;
}
