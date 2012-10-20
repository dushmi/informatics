#include <cstdio>
#include <cassert>

typedef int Huge[100];

void reset(Huge A) {
  for (int i = 0; i < 100; ++i)
    A[i] = 0;
}

void add(Huge A, Huge B) {
  int i, T = 0;
  
  for (i = 1; i <= A[0] || i <= B[0] || T; ++i) {
    A[i] += B[i] + T;
    T = A[i] / 10;
    A[i] %= 10;
  }

  A[0] = i - 1;
}

void mult(Huge A, int x) {
  int i, T = 0;
  
  for (i = 1; i <= A[0] || T; ++i) {
    A[i] = A[i] * x + T;
    T = A[i] / 10;
    A[i] %= 10;
  }

  A[0] = i - 1;
}

int mod(Huge A, int x) {
  int R = 0;

  for (int i = A[0]; i >= 1; --i) {
    R = R * 10 + A[i];
    R %= x;
  }

  return R;
}

void print(Huge A) {
  if (A[0] == 0) {
    printf("0\n");
    return;
  }

  for (int i = A[0]; i >= 1; --i)
    printf("%d", A[i]);
  
  printf("\n");
}

int main() {
  assert(freopen("resturi.in", "r", stdin));
  assert(freopen("resturi.out", "w", stdout));

  int T;
  assert(scanf("%d", &T) == 1);

  for (int i = 1; i <= T; ++i) {
    int N;
    assert(scanf("%d", &N) == 1);
  
    Huge ANS, prod;
    reset(ANS);
    reset(prod); prod[++prod[0]] = 1;

    for (int j = 1; j <= N; ++j) {
      int p, r;
      assert(scanf("%d%d", &p, &r) == 2);
      
      for (;mod(ANS, p) != r;)
        add(ANS, prod);
        

      mult(prod, p);
    }

    print(ANS);
  }

  return 0;
}
