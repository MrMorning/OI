#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
using namespace std;
int n;
namespace calcAns {
	int log3[201];
	int noteF[201], noteG[201];

	int calcG(int n) {
		static bool dpDone[201];
		static int dpMemo[201];
		if ( n == 1 )
			return 0;
		if ( n == 2 )
			return 1;

		if ( dpDone[n] )
			return dpMemo[n];
		dpDone[n] = true;
		int &res = dpMemo[n] = 0x3f3f3f3f;
		for ( int p = 2; p <= n; p ++ ) {
			int tmp = 1 + max(log3[p], calcG(n - p));
			if ( tmp < res ) {
				res = tmp;
				noteG[n] = p;
			}
		}
		return res;
	}

	int calcF(int n) {
		static bool dpDone[201];
		static int dpMemo[201];
		if ( dpDone[n] )
			return dpMemo[n];
		dpDone[n] = true;
		int &res = dpMemo[n] = 0x3f3f3f3f;
		for ( int k = 1; n - 2 * k > 0; k ++ ) {
			int tmp = 1 + max(log3[2 * k], calcG(n - 2 * k));
			if ( tmp < res ) {
				res = tmp;
				noteF[n] = k;
			}
		}
		return res;
	}

	void main() {
		log3[1] = 0;
		log3[3] = 1;
		log3[9] = 2;
		log3[27] = 3;
		log3[81] = 4;
		log3[243] = 5;
		for ( int i = 200, pre = 243; i >= 1; i -- )
			if ( log3[i] == 0 )
				log3[i] = log3[pre];
			else
				pre = i;
		printf("need %d weighings\n", calcF(n));
	}
}

string convert(int x) {
	string res;
	while ( x ) {
		res += (char)('0' + (x % 10));
		x /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}

string link(vector<int> S) {
	string res;
	int n = S.size();
	if ( n == 0 )
		return res;
	res = convert(S[0]);
	for ( int i = 1; i < n; i ++ ) {
		res += '+';
		res += convert(S[i]);
	}
	return res;
}

namespace printSol {
	int std;
	int maxDep = 0;

	void split(vector<int> S, vector<int> &A, vector<int> &B, vector<int> &C, int a, int b, int c) {
		assert((int)S.size() == a + b + c);
		A.clear();
		B.clear();
		C.clear();
		for ( int i = 0; i < a + b + c; i ++ ) {
			if ( i < a )
				A.push_back(S[i]);
			else if ( i < a + b )
				B.push_back(S[i]);	
			else
				C.push_back(S[i]);
		}

	}

	void printSpace(int n) {
		for ( int i = 0; i < n; i ++ )
			printf("  ");
	}

	void printP(vector<int> S1, vector<int> S2, int dep) {
		int n = S1.size(), m = S2.size();
		if ( n + m == 1 ) {
			printSpace(dep);
			printf("fake %d\n", n ? S1[0] : S2[0]);
			return;
		}
		if(dep >= 5)
			assert(0);
		maxDep = max(maxDep, dep);
		if ( n + m == 2 ) {
			if ( n == 0 ) {
				printSpace(dep);
				printf("weigh %d vs %d\n", S2[0], std);
				printSpace(dep);
				printf("case =:\n");
				printSpace(dep + 1);
				printf("fake %d\n", S2[1]);
				printSpace(dep);
				printf("case >:\n");
				printSpace(dep + 1);
				printf("fake %d\n", S2[0]);
				printSpace(dep);
				printf("end\n");
			}
			if ( n == 1 ) {
				printSpace(dep);
				printf("weigh %d vs %d\n", S1[0], std);
				printSpace(dep);
				printf("case =:\n");
				printSpace(dep + 1);
				printf("fake %d\n", S2[0]);
				printSpace(dep);
				printf("case <:\n");
				printSpace(dep + 1);
				printf("fake %d\n", S1[0]);
				printSpace(dep);
				printf("end\n");
			}
			if ( n == 2 ) {
				printSpace(dep);
				printf("weigh %d vs %d\n", S1[0], std);
				printSpace(dep);
				printf("case =:\n");
				printSpace(dep + 1);
				printf("fake %d\n", S1[1]);
				printSpace(dep);
				printf("case <:\n");
				printSpace(dep + 1);
				printf("fake %d\n", S1[0]);
				printSpace(dep);
				printf("end\n");
			}
			return;
		}
		vector<int> A1, B1, C1, A2, B2, C2;
		if ( n % 3 == 0 && m % 3 == 0 ) {
			split(S1, A1, B1, C1, n / 3, n / 3, n / 3);
			split(S2, A2, B2, C2, m / 3, m / 3, m / 3);
		} else if ( n % 3 == 0 && m % 3 == 1 ) {
			split(S1, A1, B1, C1, n / 3, n / 3, n / 3);
			split(S2, A2, B2, C2, m / 3, m / 3, m / 3 + 1);
		} else if ( n % 3 == 0 && m % 3 == 2 ) {
			split(S1, A1, B1, C1, n / 3, n / 3, n / 3);
			split(S2, A2, B2, C2, m / 3 + 1, m / 3 + 1, m / 3);
		} else if ( n % 3 == 1 && m % 3 == 0 ) {
			split(S1, A1, B1, C1, n / 3, n / 3, n / 3 + 1);
			split(S2, A2, B2, C2, m / 3, m / 3, m / 3);
		} else if ( n % 3 == 1 && m % 3 == 1 ) {
			split(S1, A1, B1, C1, n / 3, n / 3, n / 3 + 1);
			split(S2, A2, B2, C2, m / 3 + 1, m / 3, m / 3);
			//special processing
			
			printSpace(dep);
			string A1s, A2s, B1s, B2s;
			A1s = link(A1), A2s = link(A2);
			B1s = link(B1), B2s = link(B2);
			printf("weigh ");

			if ( A1s.size() ) 
				printf("%s+", A1s.c_str());
			printf("%d", std);
			if ( B2s.size() ) 
				printf("+%s", B2s.c_str());
			printf(" vs ");
			if ( !B1s.size() )
				printf("%s", A2s.c_str());
			else if ( !A2s.size() )
				printf("%s", B1s.c_str());
			else
				printf("%s+%s", B1s.c_str(), A2s.c_str());
			printf("\n");
			if ( A1.size() + A2.size() ) {
				printSpace(dep);
				printf("case <:\n");
				printP(A1, A2, dep + 1);
			}
			if ( B1.size() + B2.size() ) {
				printSpace(dep);
				printf("case >:\n");
				printP(B1, B2, dep + 1);
			}
			if ( C1.size() + C2.size() ) {
				printSpace(dep);
				printf("case =:\n");
				printP(C1, C2, dep + 1);
			}
			printSpace(dep);
			printf("end\n");

			return;
		} else if ( n % 3 == 1 && m % 3 == 2 ) {
			split(S1, A1, B1, C1, n / 3, n / 3, n / 3 + 1);
			split(S2, A2, B2, C2, m / 3 + 1, m / 3 + 1, m / 3);
		} else if ( n % 3 == 2 && m % 3 == 0 ) {
			split(S1, A1, B1, C1, n / 3 + 1, n / 3 + 1, n / 3);
			split(S2, A2, B2, C2, m / 3, m / 3, m / 3);
		} else if ( n % 3 == 2 && m % 3 == 1 ) {
			split(S1, A1, B1, C1, n / 3 + 1, n / 3 + 1, n / 3);
			split(S2, A2, B2, C2, m / 3, m / 3, m / 3 + 1);
		} else if ( n % 3 == 2 && m % 3 == 2 ) {
			split(S1, A1, B1, C1, n / 3 + 1, n / 3 + 1, n / 3);
			split(S2, A2, B2, C2, m / 3 + 1, m / 3 + 1, m / 3);
		} else {
			assert(0);
		}

		printSpace(dep);
		string A1s, A2s, B1s, B2s;
		A1s = link(A1), A2s = link(A2);
		B1s = link(B1), B2s = link(B2);
		printf("weigh ");
		if ( !A1s.size() )
			printf("%s", B2s.c_str());
		else if ( !B2s.size() )
			printf("%s", A1s.c_str());
		else
			printf("%s+%s", A1s.c_str(), B2s.c_str());
		printf(" vs ");
		if ( !B1s.size() )
			printf("%s", A2s.c_str());
		else if ( !A2s.size() )
			printf("%s", B1s.c_str());
		else
			printf("%s+%s", B1s.c_str(), A2s.c_str());
		printf("\n");

		if ( A1.size() + A2.size() ) {
			printSpace(dep);
			printf("case <:\n");
			printP(A1, A2, dep + 1);
		}
		if ( B1.size() + B2.size() ) {
			printSpace(dep);
			printf("case >:\n");
			printP(B1, B2, dep + 1);
		}
		if ( C1.size() + C2.size() ) {
			printSpace(dep);
			printf("case =:\n");
			printP(C1, C2, dep + 1);
		}
		printSpace(dep);
		printf("end\n");
	}

	void printG(vector<int> S, int dep) {
		maxDep = max(maxDep, dep);
		int n = S.size();
		assert(n > 0);
		if ( n == 1 ) {
			printSpace(dep);
			printf("fake %d\n", S[0]);
			return;
		} else if ( n == 2 ) {
			printSpace(dep);
			printf("weigh %d vs %d\n", S[0], std);
			printSpace(dep);
			printf("case <:\n");
			printSpace(dep + 1);
			printf("fake %d\n", S[0]);
			printSpace(dep);
			printf("case >:\n");
			printSpace(dep + 1);
			printf("fake %d\n", S[0]);
			printSpace(dep);
			printf("case =:\n");
			printSpace(dep + 1);
			printf("fake %d\n", S[1]);
			printSpace(dep);
			printf("end\n");
			return;
		}
		int p = calcAns::noteG[n];
		vector<int> A, B, C;
		int a = p / 2, b = p - a;
		split(S, A, B, C, a, b, n - p);
		printSpace(dep);
		if ( a < b ) {
			printf("weigh %s+%d vs %s\n", link(A).c_str(), std, link(B).c_str());
			assert(a + 1 == b);
		} else {
			assert(a == b);
			printf("weigh %s vs %s\n", link(A).c_str(), link(B).c_str());
		}

		printSpace(dep);
		printf("case <:\n");
		printP(A, B, dep + 1);
		printSpace(dep);
		printf("case >:\n");
		printP(B, A, dep + 1);
		printSpace(dep);
		if ( C.size() ) {
			printf("case =:\n");
			printG(C, dep + 1);
		}
		printSpace(dep);
		printf("end\n");
	}

	void printF(vector<int> S, int dep) {
		maxDep = max(maxDep, dep);
		int n = (int)S.size();
		int k = calcAns::noteF[n];
		assert(n - 2 * k > 0);
		vector<int> A, B, C;
		split(S, A, B, C, k, k, n - 2 * k);
		printSpace(dep);
		assert(A.size() == B.size());
		printf("weigh %s vs %s\n", link(A).c_str(), link(B).c_str());
		printSpace(dep);
		printf("case <:\n");
		std = C[0];
		printP(A, B, dep + 1);
		printSpace(dep);
		printf("case >:\n");
		std = C[0];
		printP(B, A, dep + 1);
		printSpace(dep);
		printf("case =:\n");
		std = A[0];
		printG(C, dep + 1);
		printSpace(dep);
		printf("end\n");
	}

	void main() {
		vector<int> vec(n);
		for ( int i = 1; i <= n; i ++ )
			vec[i - 1] = i;
		printF(vec, 0);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	calcAns::main();
	printSol::main();
}
