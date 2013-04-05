#include <cstdio>
int k;
int countBits(int s) {
	int res = 0;
	while ( s ) {
		res += s & 1;
		s >>= 1;
	}
	return res;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &k);
	int ans = 0;
	if ( countBits(k) >= 3 ) {
		int p[4];
		int t = 3;
		for ( int d = 31; t >= 1 && d >= 0; d -- )
			if ( k & (1 << d) ) 
				p[t --] = d;
		ans = 1 + p[2] + (p[3] * p[3] - p[3]) / 2;
	} else if ( countBits(k) == 2 ) {
		int p[3];
		int t = 2;
		for ( int d = 31; t >= 1 && d >= 0; d -- )
			if ( k & (1 << d) ) 
				p[t --] = d;
		ans = p[1] + (p[2] * p[2] - p[2]) / 2;
	} else {
		int p[2];
		int t = 1;
		for ( int d = 31; t >= 1 && d >= 0; d -- )
			if ( k & (1 << d) ) 
				p[t --] = d;
		ans = (p[1] * p[1] - p[1]) / 2;
	}
	printf("%d\n", ans);
}
