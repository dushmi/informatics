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

const int MOD = 1000000009;

long long fact[40005];

class FoxStones {
public:
    int modul(int x) {
      return x < 0 ? (-x) : x;
    }
    
    void pregen() {
      fact[0] = 1;

      for (int i = 1; i <= 40000; ++i)
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    
    int getCount(int N, int M, vector <int> sx, vector <int> sy)  {
      long long result = 1;

      map <vector <int>, int> V;
      
      pregen();

      for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j) {
          vector <int> pos;
        
          for (int k = 0; k < (int)sx.size(); ++k)
            pos.push_back(max(modul(i - sx[k]), modul(j - sy[k])));
        
          ++V[pos];
        }

      for (typeof(V.begin()) it = V.begin(); it != V.end(); ++it)
        result = (result * fact[it->second]) % MOD;

      return result;
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
	
	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) { 
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
			int N                     = 6;
			int M                     = 1;
			int sx[]                  = {3};
			int sy[]                  = {1};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = FoxStones().getCount(N, M, vector <int>(sx, sx + (sizeof sx / sizeof sx[0])), vector <int>(sy, sy + (sizeof sy / sizeof sy[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 2;
			int M                     = 2;
			int sx[]                  = {2};
			int sy[]                  = {1};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = FoxStones().getCount(N, M, vector <int>(sx, sx + (sizeof sx / sizeof sx[0])), vector <int>(sy, sy + (sizeof sy / sizeof sy[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 3;
			int M                     = 3;
			int sx[]                  = {1,2,3};
			int sy[]                  = {1,2,3};
			int expected__            = 8;

			clock_t start__           = clock();
			int received__            = FoxStones().getCount(N, M, vector <int>(sx, sx + (sizeof sx / sizeof sx[0])), vector <int>(sy, sy + (sizeof sy / sizeof sy[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 12;
			int M                     = 34;
			int sx[]                  = {5,6,7,8,9,10};
			int sy[]                  = {11,12,13,14,15,16};
			int expected__            = 410850247;

			clock_t start__           = clock();
			int received__            = FoxStones().getCount(N, M, vector <int>(sx, sx + (sizeof sx / sizeof sx[0])), vector <int>(sy, sy + (sizeof sy / sizeof sy[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int N                     = ;
			int M                     = ;
			int sx[]                  = ;
			int sy[]                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxStones().getCount(N, M, vector <int>(sx, sx + (sizeof sx / sizeof sx[0])), vector <int>(sy, sy + (sizeof sy / sizeof sy[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int N                     = ;
			int M                     = ;
			int sx[]                  = ;
			int sy[]                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxStones().getCount(N, M, vector <int>(sx, sx + (sizeof sx / sizeof sx[0])), vector <int>(sy, sy + (sizeof sy / sizeof sy[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int N                     = ;
			int M                     = ;
			int sx[]                  = ;
			int sy[]                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxStones().getCount(N, M, vector <int>(sx, sx + (sizeof sx / sizeof sx[0])), vector <int>(sy, sy + (sizeof sy / sizeof sy[0])));
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
