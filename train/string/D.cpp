#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 100010;
void extended_KMP(int *res, char *S, char *T, int n, int m, int *next) {
	res[0] = 0;
	while ( res[0] < n && res[0] < m && S[res[0]] == T[res[0]] )
		res[0] ++;

	res[1] = 0;
	while ( res[1] + 1 < n && res[1] < m && S[1 + res[1]] == T[res[1]] )
		res[1] ++;

	int a = 1, p = 1 + res[1] - 1;
	for ( int i = 2; i < n; i ++ ) {
		int L = next[i - a];
		if ( i + L - 1 < p )
			res[i] = L;
		else {
			res[i] = max(0, p - i + 1);
			while ( i + res[i] < n && res[i] < m
					&& S[i + res[i]] == T[res[i]] )
				res[i] ++;
			if ( i + res[i] - 1 > p ) {
				a = i, p = i + res[i] - 1;
			}
		}
	}
}
char str1[N_MAX], str2[N_MAX];
int next[N_MAX], lcp[N_MAX];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%s%s", str1, str2);
	int n = strlen(str1),
		m = strlen(str2);
	extended_KMP(next, str2, str2, m, m, next);
	extended_KMP(lcp, str1, str2, n, m, next);
	int res = 0;
	for ( int i = 0; i < n; i ++ )
		res = max(res, lcp[i]);
	printf("%d\n", res);
}
