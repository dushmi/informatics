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

class DengklekTryingToSleep {
public:
    int minDucks(vector <int> ducks)  {
      int m = 100, M = 0, nrel = ducks.size();

      for (int i = 0; i < nrel; ++i) {
        if (ducks[i] < m)
          m = ducks[i];

        if (ducks[i] > M)
          M = ducks[i];
      }

      return M - m + 1 - nrel;
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
			int ducks[]               = {5, 3, 2};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = DengklekTryingToSleep().minDucks(vector <int>(ducks, ducks + (sizeof ducks / sizeof ducks[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int ducks[]               = {58};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = DengklekTryingToSleep().minDucks(vector <int>(ducks, ducks + (sizeof ducks / sizeof ducks[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int ducks[]               = {9, 3, 6, 4};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = DengklekTryingToSleep().minDucks(vector <int>(ducks, ducks + (sizeof ducks / sizeof ducks[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int ducks[]               = {7, 4, 77, 47, 74, 44};
			int expected__            = 68;

			clock_t start__           = clock();
			int received__            = DengklekTryingToSleep().minDucks(vector <int>(ducks, ducks + (sizeof ducks / sizeof ducks[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int ducks[]               = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = DengklekTryingToSleep().minDucks(vector <int>(ducks, ducks + (sizeof ducks / sizeof ducks[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int ducks[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DengklekTryingToSleep().minDucks(vector <int>(ducks, ducks + (sizeof ducks / sizeof ducks[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int ducks[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DengklekTryingToSleep().minDucks(vector <int>(ducks, ducks + (sizeof ducks / sizeof ducks[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int ducks[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DengklekTryingToSleep().minDucks(vector <int>(ducks, ducks + (sizeof ducks / sizeof ducks[0])));
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
