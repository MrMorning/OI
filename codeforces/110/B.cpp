#include <cstdio>
#include <algorithm>
using namespace std;

#define LIE 0
#define TRUTH 1
#define TIE 2

const int N_MAX = 100010;

int n, m;
pair<int, int> reply[N_MAX];
bool pos[N_MAX];
int posCnt, sumN, N[N_MAX], Y[N_MAX];

int solve(int i) {
	if ( reply[i].first == 0 ) {
		if ( posCnt == 1 )
			return pos[reply[i].second] ? LIE : TRUTH;
		else {
			if ( pos[reply[i].second] )
				return TIE;
			else
				return TRUTH;
		}
	} else {
		if ( posCnt == 1 )
			return pos[reply[i].second] ? TRUTH : LIE;
		else {
			if ( pos[reply[i].second] )
				return TIE;
			else
				return LIE;
		}
	}
}
int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d%d\n", &n, &m);
	for ( int i = 1; i <= n; i ++ ) {
		char ch;
		int x;
		scanf("%c%d\n", &ch, &x);
		if ( ch == '-' ) {
			reply[i] = make_pair(0, x);	
			N[x] ++;
		}
		else {
			reply[i] = make_pair(1, x);
			Y[x] ++;
		}
	}
	sumN = 0;
	for ( int i = 1; i <= n; i ++ )
		sumN += N[i];
	posCnt = 0;
	for ( int i = 1; i <= n; i ++ ) {
		if ( Y[i] + sumN - N[i] == m ) {
			pos[i] = true;
			posCnt ++;
		}
	}
	for ( int i = 1; i <= n; i ++ ) {
		int res = solve(i);
		if ( res == LIE ) 
			printf("Lie\n");
		else if ( res == TIE )
			printf("Not defined\n");
		else
			printf("Truth\n");
	}
}
