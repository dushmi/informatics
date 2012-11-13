#include <iostream>
#include <cstring>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

const int kMaxV = 10000005;

char s[30];

int n, fr[30];

long long val[30];

vector <int> primes;

bitset <kMaxV> t;

void sieve() {
    t[1] = 1;

    for (int i = 1; i < kMaxV; ++i)
        if (!t[i]) {
            primes.push_back(i);
            
            if (1LL * i * i < kMaxV)
                for (int j = i * i; j < kMaxV; j += i)
                    t[j] = 1;
        }
}

void gcd(bool ok, vector <pair <long long, int> > &v, long long x) {
    if (ok) {
        for (size_t i = 0; i < primes.size() && 1LL * primes[i] * primes[i] <= x; ++i)
            if (x % primes[i] == 0) {
                v.push_back(make_pair(primes[i], 0));
                while (x % primes[i] == 0) {
                    x /= primes[i];
                    ++v[v.size() - 1].second;
                }
            }
         
        if (x > 1)
             v.push_back(make_pair(x, 1));
        
        return;
    }

    for (size_t i = 0; i < v.size(); ++i) 
        if (x % v[i].first != 0) {
            swap(v[i], v[v.size() - 1]);
            v.pop_back();
            --i;
        } else {
            int newexp = 0;
            while (x % v[i].first == 0) {
                x /= v[i].first;
                ++newexp;
            }
            if (newexp < v[i].second)
                v[i].second = newexp;
        }
}

vector <long long> list;

long long ansc = 1;

void back(int pos, vector <pair <long long, int> > &v) {
    if (pos == (int)v.size()) {
        list.push_back(ansc);
        return;
    }

    back(pos + 1, v);

    for (int i = 1; i <= v[pos].second; ++i) {
        ansc *= v[pos].first;
        back(pos + 1, v);
    }

    for (int i = 1; i <= v[pos].second; ++i)
        ansc /= v[pos].first;
}

void solve() {
    n = strlen(s) - 1;
    
    int dist = 0;

    for (int i = 0; i < 26; ++i)
        val[i] = 0, fr[i] = 0;

    long long step = 1;

    for (int i = n; i >= 0; --i, step *= 10) {
        if (!fr[s[i] - 'a'])
            ++dist;

        ++fr[s[i] - 'a'];

        val[s[i] - 'a'] += step;
    }

    bool ok = 1;
    
    vector <pair <long long, int> > vans;
    
    if (dist < 10) {
        for (int i = 0; i < 26; ++i)
            if (val[i]) {
                gcd(ok, vans, val[i]);
                ok = 0;
            }
        
        list.clear();

        back(0, vans);
        
        sort(list.begin(), list.end());

        for (size_t i = 0; i < list.size(); ++i)
            cout << " " << list[i];

        cout << "\n";

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
    
    sieve();

    for (int i = 1; i <= T; ++i) {
        cin >> s;
        
        cout << "Case " << i << ":";

        solve();
    }

    return 0;
}

