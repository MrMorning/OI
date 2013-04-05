#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 1000;
char S[N_MAX], T[N_MAX];
int next[N_MAX], lcp[N_MAX];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%s%s", S, T);
	int n = strlen(S), m = strlen(T);
	next[1] = 0;
	while ( 1 + next[1] < m && T[1 + next[1]] == T[next[1]] )
		next[1] ++;
	int a = 1, p = 1 + next[1] - 1;
	for ( int i = 2; i < m; i ++ ) {
		int L = next[i - a];
		if ( i <= p && i + L - 1 <= p )
			next[i] = L;
		else {
			next[i] = max(0, p - i + 1);
			while ( i + next[i] < m && 
					T[i + next[i]] == T[next[i]] )
				next[i] ++;
			if ( i + next[i] - 1 > p )
				a = i, p = i + next[i] - 1;
		}
	}
//	for ( int i = 1; i < m; i ++ )
//		printf("%d\n", next[i]);
//	return 0;
	lcp[1] = 0;
	while ( 1 + lcp[1] < n && lcp[1] < m 
			&& S[1 + lcp[1]] == T[lcp[1]] )
		lcp[1] ++;
	a = 1, p = 1 + lcp[1] - 1;
	for ( int i = 2; i < n; i ++ ) {
		int L = next[i - a];
		if ( i <= p && i + L - 1 <= p )
			lcp[i] = L;
		else {
			lcp[i] = max(0, p - i + 1);
			while ( i + lcp[i] < n && 
					S[i + lcp[i]] == T[lcp[i]] )
				lcp[i] ++;
			if ( i + lcp[i] - 1 > p )
				a = i, p = i + lcp[i] - 1;
		}
	}
	for ( int i = 1; i < n; i ++ )
		printf("%d\n", lcp[i]);
}
