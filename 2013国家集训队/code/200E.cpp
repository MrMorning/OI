#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;
struct Solution {
	int x0, y0, a, b;
	bool hasSol;
	//x = x0+at, y = y0+bt
};

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

void exgcd(int a, int b, int &x, int &y) {
	if ( b == 0 ) {
		x = 1, y = 0;
		return;
	}
	int x0, y0;
	exgcd(b, a%b, x0, y0);
	x = y0, y = x0-a/b*y0;
}

Solution solveEq(int a, int b, int c) {
	Solution res;
	int g = gcd(a, b);
	if ( c % g != 0 ) {
		res.hasSol = false;
		return res;
	}
	res.hasSol = true;
	a /= g, b /= g, c /= g;
	exgcd(a, b, res.x0, res.y0);
	res.x0 *= c, res.y0 *= c;
	assert(res.x0*a+res.y0*b==c);
	res.a = b, res.b = -a;
	return res;
}

int n, s;
int c[7];
int ans = -1, ansK3, ansK4, ansK5;
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &s);
	for ( int i = 0; i < n; i ++ ) {
		int x;
		scanf("%d", &x);
		c[x]++;
	}
	for ( int k4 = 0; k4*c[4] <= s; k4 ++ ) {
		Solution sol = solveEq(c[3], c[5], s-k4*c[4]);
		if ( !sol.hasSol ) continue;
		int lb = -s, rb = s;
		if ( sol.b > 0 )
			lb = max(lb, (int)ceil((double)(k4-sol.y0) / sol.b));
		else 
			rb = min(rb, (int)floor((double)(k4-sol.y0) / sol.b));
		if ( sol.a > 0 ) {
			rb = min(rb, (int)floor((double)(k4-sol.x0) / sol.a));
			lb = max(lb, (int)ceil((double)-sol.x0 / sol.a));
		}
		else {
			lb = max(lb, (int)ceil((double)(k4-sol.x0) / sol.a));
			rb = min(rb, (int)floor((double)-sol.x0 / sol.a));
		}
#define EVAL(t) (abs(c[3]*(sol.x0+sol.a*(t))-c[4]*k4)+abs(c[4]*k4-c[5]*(sol.y0+sol.b*(t))))
		if ( lb <= rb ) {
			/*if ( k4 == 1000 ) {
				FILE *ftest = fopen("t.log", "w");
				for ( int t = lb; t <= rb ;t ++ )
					fprintf(ftest, "%d\n", EVAL(t));
			}*/
			for ( int cnt = 0; cnt < 100; cnt ++ ) {
				int midl = lb+(rb-lb)/3,
					midr = rb-(rb-lb)/3;
				if ( EVAL(midl) < EVAL(midr) )
					rb = midr;
				else
					lb = midl;
			}
			int best = lb;
			for ( int t = lb+1; t <= rb; t ++ )
				if ( EVAL(t) < EVAL(best) )
					best = t;
			if ( ans==-1 || EVAL(best) < ans ) {
				ans = EVAL(best);
				ansK4 = k4, ansK3 = sol.x0+sol.a*best, ansK5 = sol.y0+sol.b*best;
			}
		}
	}
	if ( ans == -1 ) puts("-1");
	else
	//	printf("%d\n", ans);
		printf("%d %d %d\n", ansK3, ansK4, ansK5);
}
