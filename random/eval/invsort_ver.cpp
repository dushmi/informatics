#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cstdlib>

using namespace std;

const int kMaxN = 32005;

int N, aux[kMaxN], vec[kMaxN];

int main() {
  assert(freopen("invsort.in", "r", stdin));

  assert(scanf("%d", &N) == 1); 

  for (int i = 1; i <= N; ++i)
    assert(scanf("%d", &vec[i]) == 1);
  
  fclose(stdin);

  copy(vec + 1, vec + N + 1, aux + 1);
  sort(aux + 1, aux + N + 1);

  assert(freopen("invsort.out", "r", stdin));

  int x, y;

  while (scanf("%d%d", &x, &y) != EOF)
    reverse(vec + x, vec + y + 1);

  for (int i = 1; i <= N; ++i)
    if (vec[i] != aux[i]) {
      printf("WA at position %d : %d != %d\n", i, vec[i], aux[i]);
      system("mv invsort.in invsort.wa");
      return 0;
    }

  printf("OK\n");
  return 0;
}
