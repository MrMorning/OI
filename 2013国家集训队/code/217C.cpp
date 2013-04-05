#include <cstdio>
#include <cassert>
#include <cstring>

char s[1000005];
int match[1000005];
int stk[1000005], top;

inline int calc(int a, int b, char op) {
	if ( op == '^' ) return a ^ b;
	if ( op == '|' ) return a | b;
	if ( op == '&' ) return a & b;
	assert(0);
}

int merge(int sl, int sr, char op) {
	static int al[3][2], ar[3][2];
	assert(sl && sr);
	int nl = 0, nr = 0;
	if ( sl & 1 ) {
		al[nl][0] = 0;
		al[nl][1] = 0;
		nl++;
	}
	if ( sl & 2 ) {
		al[nl][0] = 1;
		al[nl][1] = 1;
		nl++;
	}
	if ( sl & 4 ) {
		al[nl][0] = 0;
		al[nl][1] = 1;
		nl++;
	}
	if ( sr & 1 ) {
		ar[nr][0] = 0;
		ar[nr][1] = 0;
		nr++;
	}
	if ( sr & 2 ) {
		ar[nr][0] = 1;
		ar[nr][1] = 1;
		nr++;
	}
	if ( sr & 4 ) {
		ar[nr][0] = 0;
		ar[nr][1] = 1;
		nr++;
	}
	int msk = 0;
	for ( int i = 0; i < nl; i ++ )
		for ( int j = 0; j < nr; j ++ ) 
			for ( int t = 0; t < 2; t ++ ) {
				int vl = calc(al[i][0], ar[j][0^t], op),
					vr = calc(al[i][1], ar[j][1^t], op);
				if ( vl == vr ) msk |= 1<<vl;
				else msk |= 1<<2;
			}
	return msk;
}

int solve(int l, int r) {
	assert(l <= r);
	if ( l == r ) {
		if ( s[l] == '0' ) return 1<<0;
		else if ( s[l] == '1' ) return 1<<1;
		assert(s[l] == '?');
		return 1<<2;	
	}
	if ( s[l] == '(' && match[l] == r ) 
		return solve(l+1, r-1);
	int p;
	if ( s[l] == '(' ) 
		p = match[l]+1;
	else p = l+1;
	return merge(solve(l, p-1), solve(p+1, r), s[p]);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%*d%s", s);
	int n = strlen(s);
	for ( int i = 0; i < n; i ++ )
		if ( s[i] == '(' )
			stk[top++] = i;
		else if ( s[i] == ')' )
			match[stk[--top]] = i;
	int res = solve(0, n-1);
	printf("%s\n", res&(1<<2)?"YES":"NO");
}
