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

class DengklekMakingChains {
public:
    int maxBeauty(vector <string> chains)  {
      int st[51], dr[51];
      
      bool fine[51];
      
      int rez = 0;

      for (int i = 0; i < (int)chains.size(); ++i) {
        st[i] = dr[i] = 0;
        fine[i] = 0;

        if (chains[i][0] != '.') {
          st[i] += chains[i][0] - '0';
          
          if (chains[i][1] != '.') {
            st[i] += chains[i][1] - '0';
            
            if (chains[i][2] != '.') 
              st[i] += chains[i][2] - '0';
          }
        }

        if (chains[i][2] != '.') {
          dr[i] += chains[i][2] - '0';

          if (chains[i][1] != '.') {
            dr[i] += chains[i][1] - '0';

            if (chains[i][0] != '.')
              dr[i] += chains[i][0] - '0';
          }
        }

        if (chains[i][0] != '.' && chains[i][0] - '0' > rez)
          rez = chains[i][0] - '0';

        if (chains[i][1] != '.' && chains[i][1] - '0' > rez)
          rez = chains[i][1] - '0';

        if (chains[i][2] != '.' && chains[i][2] - '0' > rez)
          rez = chains[i][2] - '0';

        if (chains[i][0] != '.' && chains[i][1] != '.' && chains[i][2] != '.')
          fine[i] = 1;
      }

      int sum = 0;

      for (int i = 0; i < (int)chains.size(); ++i)
        if (fine[i]) {
          sum += dr[i];
          continue;
        }
      
      if (sum > rez)
        rez = sum;

      for (int s = 0; s < (int)chains.size(); ++s)
        for (int d = 0; d < (int)chains.size(); ++d)
          if (!fine[s] && !fine[d] && s != d && sum + st[s] + dr[d] > rez)
            rez = sum + st[s] + dr[d];
      
    for (int i = 0; i < (int)chains.size(); ++i)
      if (!fine[i]) {
        if (sum + st[i] > rez)
          rez = sum + st[i];

        if (sum + dr[i] > rez)
          rez = sum + dr[i];
      }

      return rez;
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
			string chains[]           = {".15", "7..", "402", "..3"};
			int expected__            = 19;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string chains[]           = {"..1", "7..", "567", "24.", "8..", "234"};
			int expected__            = 36;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string chains[]           = {"...", "..."};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string chains[]           = {"16.", "9.8", ".24", "52.", "3.1", "532", "4.4", "111"};
			int expected__            = 28;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			string chains[]           = {"..1", "3..", "2..", ".7."};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			string chains[]           = {"412", "..7", ".58", "7.8", "32.", "6..", "351", "3.9", "985", "...", ".46"};
			int expected__            = 58;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string chains[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string chains[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string chains[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DengklekMakingChains().maxBeauty(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])));
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
