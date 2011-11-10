#include <iostream>
#include <cstring>

using namespace std;

char s[30];

int n, fr[30];

long long f[30];

long long gcd(long long x, long long y) {
  long long r = x % y;

  while (r) {
    x = y;
    y = r;
    r = x % y;
  }

  return y;
}

void afis(long long x) {
  long long i;
  
  for (i = 1; i * i <= x; ++i)
    if (x % i == 0) 
      cout << " " << i;

  for (i = i - 1; i >= 1; --i)
    if (x % i == 0 && i != x / i)
      cout << " " << x / i;

  cout << "\n";
}

void solve() {
  n = strlen(s) - 1;

  int nrd = 0, i = 0;

  long long pas = 0, rez = 0;
  
  for (int i = 0; i < 26; ++i)
    f[i] = 0, fr[i] = 0;

  for (i = n, pas = 1; i >= 0; --i, pas *= 10) {
    if (!f[s[i] - 'a'])
      ++nrd;
  
    ++fr[s[i] - 'a'];

    f[s[i] - 'a'] += pas;
  }

  if (nrd < 10) {
    for (i = 0; i < 26; ++i)
      if (f[i]) {
        if (!rez)
          rez = f[i];
        else
          rez = gcd(rez, f[i]);
      }

    afis(rez);
    
    return;
  }

  if (n == 9) {
    cout << " 1 3 9\n";

    return;
  }

  if (n == 12) {
    for (int i = 0; i < 26; ++i)
      if (fr[i] == 4) {
        cout << " 1 3\n";
        
        return;
      }
  }

  cout << " 1\n";
}

int main() {
  int T;

  cin >> T;

  for (int i = 1; i <= T; ++i) {
    cin >> s;

    cout << "Case " << i << ":";

    solve();
  }

  return 0;
}
