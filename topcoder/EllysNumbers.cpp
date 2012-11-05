#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long int64;

long long ng, SOL;

vector <long long> v;
vector <int> in;
bool mat[505][505];

class EllysNumbers {
public:
    long long gcd(long long a, long long b) {
      long long r = a % b;
      
      while (r) {
        a = b;
        b = r;
        r = a % b;
      }

      return b;
    }

    void DF(int nod, long long val) {
      if (val > ng || val < 0)
        return;
      
      if (val == ng) {
        ++SOL;
        return;
      }
    
      in.push_back(nod);

      for (int i = 0; i < (int)v.size(); ++i) 
        if (mat[nod][i]) {
          bool ok = 1;

          for (int j = 0; j < (int)in.size() - 1; ++j)
            if (!mat[in[j]][i]) {
              ok = 0;
              break;
            }
        
          if (ok)
            DF(i, val * v[i]);
        }
      
      in.pop_back();
    }

    long long getSubsets(long long n, vector <string> special)  {
      long long cnb = 0;

      for (int i = 0; i < (int)special.size(); ++i)
        for (int j = 0; j < (int)special[i].size(); ++j) {
          if (special[i][j] == ' ') {
            v.push_back(cnb);
            cnb = 0;
            continue;
          }

          cnb = cnb * 10 + special[i][j] - '0';
        }
      
      v.push_back(cnb);

      sort(v.begin(), v.end());

      for (int i = 0; i < (int)v.size(); ++i)
        for (int j = i + 1; j < (int)v.size(); ++j)
          if (gcd(v[i], v[j]) == 1)
            mat[i][j] = 1;
          else
            mat[i][j] = 0;
        
      ng = n;
      
      SOL = 0;

      for (int i = 0; i < (int)v.size(); ++i)
        DF(i, v[i]);

      return SOL;
    }
};

// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			cerr << "No test cases run." << endl;
		} else if (correct < total) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}
	
	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;
		
		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl; 
			cerr << "    Received: " << received << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum) {
		switch (casenum) {
		case 0: {
			long long n               = 12;
			string special[]          = {"4 2 5 6 3"};
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			long long n               = 42;
			string special[]          = {"1 2 3 4 5 6 7 13 14 21 42"};
			long long expected__      = 10;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
	  case 2: {
			long long n               = 1337;
			string special[]          = {"1 13 42 666 2674"};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			long long n               = 1073741824;
			string special[]          = {"1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 1",
 "6384 32768 65536 131072 262144 524288 1048576 2097",
 "152 4194304 8388608 16777216 33554432 67108864 134",
 "217728 268435456 536870912"};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			long long n               = 7420738134810LL;
			string special[]          = {"435 625199055 4199 33263 17 222870 284870433 72093",
 "2379 7 11 31 247110827 23 1771 81809 851968487 13 ", 
 "476379795 1001 5 435274114 38264554 7429 239906525",
 " 3 227183706 887045414 606786670 3795 797605175 29",
 " 30 747186719 19 2 562347843 74 2294 588002688 743",
 "6429 703 591740547 36657492 37 444178205 1002001 2",
 "17626404"};
			long long expected__      = 110;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			long long n               = ;
			string special[]          = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			long long n               = ;
			string special[]          = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long n               = ;
			string special[]          = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
  if (argc == 1) {
    for (int test = 0; test < 10; ++test) {
      string command = string(argv[0]) + " ";
      command.push_back('0' + test);
      if (system(command.c_str()))
        cerr << "TEST FAILED!" << endl;
    }
  } else {
    moj_harness::run_test(atoi(argv[1]));
  }
  return 0;
}
// END CUT HERE 
