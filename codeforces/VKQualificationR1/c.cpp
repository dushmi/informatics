#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

char s[250];

vector <string> v;

string str;

void afis() {
  for (int i = 0; i < (int)v.size(); ++i) {
    cout << "/";
    cout << v[i];;
  }
  cout << "/\n";
}

void reset(char s[250]) {
  for (int i = 0; i < 250; ++i)
    s[i] = '\x0';
}

void solve(int poz) {  
  if (s[poz] == '.') {
    v.pop_back();
    solve(poz + 3);
    return;
  }

  if (s[poz] >= 'a' && s[poz] <= 'z') {
    v.push_back(str);
    for (poz = poz; s[poz] >= 'a' && s[poz] <= 'z'; ++poz)
      v[v.size() - 1] += s[poz];
    solve(poz + 1);
  }
}

int main() {
  int n;

  scanf("%d\n", &n);
  
  for (int i = 1; i <= n; ++i) {
    reset(s);
    fgets(s, sizeof(s), stdin);
    
    if (s[0] == 'p') {
      afis();
      continue;
    }

    if (s[3] == '/') {
      v.clear();
      solve(4);
    } else
      solve(3);
  }
}
