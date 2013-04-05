#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const double kEps = 1e-8;
const double kInf = 1e100;

double sqr(double a) { return a * a; }

int nf, ne, ns, rf, re, rs, df, de;
double ans = 0;

int sgn(double x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

bool equal(double x, double y) {
	return sgn(x-y) == 0;
}

struct Segment {
	double l, r;
	Segment(double ll, double rr): l(ll), r(rr){}
};

double getCross(Segment A, Segment B) {
	if ( A.l > B.l ) swap(A, B);
	if ( A.r < B.l ) return 0;
	return min(A.r, B.r) - B.l;
}

double f[14][21][21];
double valf[14], vale[14];
int a[10];

void upd(double &a, double b) {
	a = max(a, b);
}

void work() {
	for ( int x = 0; x < 10; x ++ ) 
		if ( a[x] != 2 ) {
			double vf = 2*sqrt(sqr(rf)-1)*df, ve = 2*sqrt(sqr(re)-1)*de;
			for ( int y = 0; y < 10; y ++ ) {
				double ls = sqrt(sqr(rs)-1), lf = sqrt(sqr(rf)-1),
					   le = sqrt(sqr(re)-1);
				Segment ss = Segment(y-ls, y+ls),
						sf = Segment(x-lf, x+lf),
						se = Segment(x-le, x+le);
				vf += getCross(ss, sf) * df * a[y];
				ve += getCross(ss, se) * de * a[y];
			}
			valf[x] = vf, vale[x] = ve;
		}
	for ( int i = 0; i < 10; i ++ )
		for ( int j = 0; j <= nf; j ++ )
			for ( int k = 0; k <= ne; k ++ )
				f[i][j][k] = -kInf;
	f[0][nf][ne] = 0;
	for ( int i = 0; i < 10; i ++ )
		for ( int j = 0; j <= nf; j ++ )
			for ( int k = 0; k <= ne; k ++ )
				if ( sgn(f[i][j][k]) >= 0 ) {
					upd(f[i+1][j][k], f[i][j][k]); 
					if ( a[i] == 1 ) {
						if ( j > 0 ) upd(f[i+1][j-1][k], f[i][j][k] + valf[i]);
						if ( k > 0 ) upd(f[i+1][j][k-1], f[i][j][k] + vale[i]);
					} else if ( a[i] == 0 ) {
						if ( j > 0 ) upd(f[i+1][j-1][k], f[i][j][k] + valf[i]);
						if ( k > 0 ) upd(f[i+1][j][k-1], f[i][j][k] + vale[i]);
						if ( j >= 2 ) upd(f[i+1][j-2][k], f[i][j][k] + 2*valf[i]);
						if ( k >= 2 ) upd(f[i+1][j][k-2], f[i][j][k] + 2*vale[i]);
						if ( j >= 1 && k >= 1 ) upd(f[i+1][j-1][k-1], f[i][j][k] + valf[i] + vale[i]);
					}
				}
	ans = max(ans, f[10][0][0]);
}

void dfs(int i, int j) {
	//position i, j freeze towers left
	if ( i == 10 ) {
		if ( j == 0 )
			work();
		return;
	}

	dfs(i+1, j);
	if ( j >= 1 ) {
		a[i] = 1;
		dfs(i+1, j-1);
		a[i] = 0;
	}
	if ( j >= 2 ) { 
		a[i] = 2;
		dfs(i+1, j-2);
		a[i] = 0;
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &nf, &ne, &ns);
	scanf("%d%d%d", &rf, &re, &rs);
	scanf("%d%d", &df, &de);
	dfs(0, ns);
	printf("%.10lf\n", ans);
}
