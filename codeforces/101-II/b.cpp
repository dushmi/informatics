#include <cstdio>

int a, x, y;

void read() {
  scanf("%d%d%d", &a, &x, &y);
}

int solve() {
  int ry = y % a;

  if (ry == 0)
    return -1;

  int nry = y / a;
  
  if (nry == 0) {
    if (x > -(0.5 * a) && x < 0.5 * a)
      return 1;
    else return -1;
  }

  if (nry % 2 == 1) {
    if (x > -(0.5 * a) && x < 0.5 * a)
      return 1 + nry / 2 * 2 + nry / 2 + 1;
    else
      return -1;
  }

  if (x > -a && x < 0)
    return 1 + nry / 2 * 2 - 2 + nry / 2 + 1;
  else if (x > 0 && x < a)
    return 1 + nry / 2 * 2 - 2 + nry / 2 + 2;
  else 
    return -1;
}

int main() {
  read();

  printf("%d\n", solve()); 

  return 0;
}
