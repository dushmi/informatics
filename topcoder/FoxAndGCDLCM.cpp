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

class FoxAndGCDLCM {
public:
    long long get(long long G, long long L)  {
      if (L % G != 0)
        return -1;

      L /= G;
       
      vector <long long> v;

      for (long long i = 2; i * i <= L; ++i) 
        if (L % i == 0) {
          long long put = 1;

          while (L % i == 0) {
            put *= i;
            L /= i;
          }

          v.push_back(put);
        }

      if (L > 1)
        v.push_back(L);
      
      long long sol = -1;

      for (int i = 0; i < (1 << v.size()); ++i) {
        long long LA = 1, LB = 1;

        for (int j = 0; j < v.size(); ++j)
          if (i & (1 << j))
            LA *= v[j];
          else
            LB *= v[j];

        if (G * LA + G * LB < sol || sol == -1)
          sol = G * LA + G * LB;
      }

      return sol;
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
			long long G               = 2;
			long long L               = 20;
			long long expected__      = 14;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			long long G               = 5;
			long long L               = 8;
			long long expected__      = -1;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			long long G               = 1000;
			long long L               = 100;
			long long expected__      = -1;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			long long G               = 100;
			long long L               = 1000;
			long long expected__      = 700;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			long long G               = 10;
			long long L               = 950863963000LL;
			long long expected__      = 6298430;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			long long G               = ;
			long long L               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			long long G               = ;
			long long L               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long G               = ;
			long long L               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FoxAndGCDLCM().get(G, L);
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
