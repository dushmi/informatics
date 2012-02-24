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

const int N = (1 << 20);

bool d[N];

class EllysCheckers {
public:
    void init(int n) {
      d[0] = 0;
      d[1] = 0;
      for (int i = 2; i < (1 << n); ++i)
        if (i & 1)
          d[i] = d[i - 1];
        else {
          for (int j = 1; j < n; ++j)
            if (i & (1 << j)) {
              if (!(i & (1 << (j - 1))))
                d[i] |= (!d[i - (1 << j) + (1 << (j - 1))]);
              
              if (j >= 3 && !(i & (1 << (j - 3)))) 
                d[i] |= (!d[i - (1 << j) + (1 << (j - 3))]);
            }
       }
    }

    string getWinner(string board)  {
      init(board.size());
      
      int nrc = 0;

      for (int i = board.size() - 1; i >= 0; --i)
        if (board[i] == 'o')
          nrc = nrc + (1 << (board.size() - 1 - i));

      if (d[nrc])
        return "YES";

      return "NO";
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
	
	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
			cerr << "    Expected: \"" << expected << "\"" << endl; 
			cerr << "    Received: \"" << received << "\"" << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum) {
		switch (casenum) {
		case 0: {
			string board              = ".o...";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string board              = "..o..o";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string board              = ".o...ooo..oo..";
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string board              = "......o.ooo.o......";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			string board              = ".o..o...o....o.....o";
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string board              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string board              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string board              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = EllysCheckers().getWinner(board);
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
