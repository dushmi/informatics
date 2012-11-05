#include <cstdlib>
#include <cstdio>
#include <cassert>

int main() {
  for (int i = 1; i <= 100; ++i) {
    system("./invsort_gen");
    system("./invsort");
    system("./invsort_ver");
  }
  
  return 0;
}
