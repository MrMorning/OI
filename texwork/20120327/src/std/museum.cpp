#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#define foreach(I, C) for( __typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++ )
using namespace std;
const int REP_TIMES = 10;
const double EPS = 1e-5;

struct Matrix {
	double ele[666][666];
	int r, c;
};

Matrix mul(const Matrix &A, const Matrix &B) {
	static Matrix res;
	memset(res.ele, 0, sizeof(res.ele));
	res.r = A.r, res.c = B.c;
	for ( int i = 0; i < res.r; i ++ )
			for ( int k = 0; k < A.c; k ++ )
				if ( A.ele[i][k] > EPS )
					for ( int j = 0; j < res.c; j ++ )
						res.ele[i][j] += A.ele[i][k] * B.ele[k][j];
	return res;
}

Matrix T, A;
int dgr[30];
vector<int> adj[30];
int match[30][30];
int n, m, a, b;
double stay[30];

int main() {
	freopen("museum.in", "r", stdin);
	freopen("museum.out", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &a, &b);
	for ( int i = 0; i < m; i ++ ) {
		int u, v;
		scanf("%d%d", &u, &v);
		dgr[u] ++, dgr[v] ++;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for ( int i = 1; i <= n; i ++ )
		scanf("%lf", &stay[i]);
	for ( int i = 1; i <= n; i ++ )
		adj[i].push_back(i);
	int idx = 0;
	for ( int i = 1; i <= n + 1; i ++ )
		for ( int j = 1; j <= n; j ++ ) 
			match[i][j] = idx ++;
	A.r = idx, A.c = 1;
	A.ele[match[a][b]][0] = 1.0;
	if (a == b)
		A.ele[match[n + 1][a]][0] = 1.0;

	T.r = T.c = idx;
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= n; j ++ ) {
			foreach(it1, adj[i])
				foreach(it2, adj[j]) {
					int u = *it1, v = *it2;
					if ( u == v )
						continue;
					double k1, k2;
					if ( u == i )
						k1 = stay[i];
					else
						k1 = (1.0 - stay[u]) / dgr[u];
					if ( v == j )
						k2 = stay[j];
					else
						k2 = (1.0 - stay[v]) / dgr[v];
					T.ele[match[i][j]][match[u][v]] += k1 * k2;
				}
		}
	for ( int j = 1; j <= n; j ++ ) {
		T.ele[match[n + 1][j]][match[n + 1][j]] = 1.0;
		for ( int k = 0; k < idx; k ++ )
			T.ele[match[n + 1][j]][k] += T.ele[match[j][j]][k];
	}

	for ( int rep = 0; rep < REP_TIMES; rep ++ )
		T = mul(T, T);
	A = mul(T, A);
	for ( int j = 1; j <= n; j ++ )
		cout << fixed << setprecision(1) << A.ele[match[n + 1][j]][0] << ' ';
}

