#include <cstdio>
#include <vector>
#include <cmath>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
const int kMatSz = 22*22+1;
const double kEps = 1e-12;
inline double sgn(double x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}
double mat[kMatSz][kMatSz*2];
vector<int> adj[23];
int n, m, xs, ys;
double p[23];
inline int r(int i, int j) {
	return (i-1)*n+j;
}
void elim(int n, int m) {
	for ( int j = 1, i = 1; i <= n; i ++ ) {
		//row j, col i
		int p;
		for ( p = j; p <= n; p ++ )
			if ( sgn(mat[p][i]) != 0 )
				break;
		if ( p == n+1 ) 
			continue;
		for ( int k = 1; k <= m; k ++ )
			swap(mat[j][k], mat[p][k]);
		double st = mat[j][i];
		for ( int k = 1; k <= m; k ++ )
			mat[j][k] /= st;
		for ( p = 1; p <= n; p ++ )
			if ( p != j && sgn(mat[p][i]) != 0 ) {
				double coef = mat[p][i];
				for ( int k = 1; k <= m; k ++ )
					mat[p][k] -= coef * mat[j][k];
			}
		j++;
	}
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	scanf("%d%d", &xs, &ys);
	while ( m -- ) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for ( int i = 1; i <= n; i ++ )
		scanf("%lf", &p[i]);
	int sz = n*n;
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ ) 
			if ( i != j ) {
				mat[r(i,j)][r(i,j)] = 1-p[i]*p[j];
				double c = p[i]*(1-p[j])/(double)adj[j].size();
				foreach(tj, adj[j])
					mat[r(i,j)][r(i,*tj)] = -c;
				c = (1-p[i])*p[j]/(double)adj[i].size();
				foreach(ti, adj[i])
					mat[r(i,j)][r(*ti,j)] = -c;
			   	c = (1-p[i])/(double)adj[i].size()*(1-p[j])/(double)adj[j].size();
				foreach(ti, adj[i])
					foreach(tj, adj[j])
						mat[r(i,j)][r(*ti,*tj)] = -c;

			} else 
				mat[r(i,j)][r(i,j)] = 1;
	for ( int i = 1; i <= n; i ++ )
		mat[r(i,i)][i+sz] = 1.0;
	elim(sz, sz+n);
	for ( int i = 1; i <= n; i ++ )
		printf("%.10lf ", mat[r(xs,ys)][i+sz]);
}
