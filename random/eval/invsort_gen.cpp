#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

int N = 32000;

int main() {
  srand(time(0));

  assert(freopen("invsort.in", "w", stdout));

  printf("%d\n", N);

  for (int i = 1; i <= N; ++i)
    printf("%d\n", rand() % N);

  return 0;
}
