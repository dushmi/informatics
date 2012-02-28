#include <cstdio>
#include <fstream>

using namespace std;

ifstream in("bursa.in");
ofstream out("bursa.out");

const int N = 100005;

int n;

long long s, p[N];

void read() {
  in >> n >> s;

  for (int i = 1; i <= n; ++i)
    in >> p[i];
}

void solve() {
  long long sinit = s, nra = 0;

  if (p[1] <= p[2]) {
    nra = s / p[1];
    s = s -  nra * p[1];
  }
  
  for (int i = 2; i < n; ++i) {
    if ((p[i] > p[i - 1] && p[i] > p[i + 1]) || (p[i] == p[i - 1] && p[i] > p[i + 1])) {
      s += nra * p[i];
      nra = 0;
    } else if ((p[i] < p[i - 1] && p[i] < p[i + 1]) || (p[i] == p[i - 1] && p[i] < p[i + 1])) {
      nra += s / p[i];
      s = s - (long long)(s / p[i]) * p[i];
    }
 }

  s += nra * p[n];
  
  out << s - sinit;
}

int main() {
  read();

  solve();

  return 0;
}
