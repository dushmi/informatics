#include <cstdio>

const int N = 1000005;

char s[N];

int n, pi[N];

void compute_pi() {
  for (n = 1; s[n]; ++n);
  --n;

  int q = 0;
  
  pi[1] = 0;
   
  for (int i = 2; i <= n; ++i) {
    while (q && s[i] != s[q + 1])
      q = pi[q];
    
    if (s[i] == s[q + 1])
      ++q;
    
    pi[i] = q;
  }
}

void solve() {
  int rez = 0, poz = 0;

  if (pi[n] == 0) {
    printf("Just a legend");
    return;
  }
  
  for (int i = pi[n]; i > 0 && (!rez); i = pi[i]) 
    for (int j = 2; j < n; ++j)
      if (pi[j] == i) {
        rez = i;
        poz = j;
        break;
      }
  
  if (!rez) {
    printf("Just a legend");
    return;
  }

  for (int i = poz - rez + 1; i <= poz; ++i)
    printf("%c", s[i]);
}

int main() {
  gets(s + 1);

  compute_pi();

  solve();

  return 0;
}
