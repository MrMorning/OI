#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;
const int N_MAX = 10100;
const double EPS = 1e-9;

double A[N_MAX], B[N_MAX], C[N_MAX];
double K[N_MAX], E[N_MAX];
vector<int> adj[N_MAX];

void dfs(int x, int fa) {
	int sz = adj[x].size();
	for ( int i = 0; i < sz; i ++ ) 
		if ( adj[x][i] != fa )
			dfs(adj[x][i], x);
	A[x] = K[x];
	B[x] = (1 - E[x] - K[x]) / sz;
	C[x] = 1 - E[x] - K[x];
	double tmp = 0;
	for ( int i = 0; i < sz; i ++ ) 
		if ( adj[x][i] != fa ) {
			int y = adj[x][i];
			A[x] += (1 - E[x] - K[x]) / sz * A[y];
			tmp += (1 - E[x] - K[x]) / sz * B[y];
			C[x] += (1 - E[x] - K[x]) / sz * C[y];
		}
	A[x] /= 1 - tmp;
	B[x] /= 1 - tmp;
	C[x] /= 1 - tmp;
}

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	for ( int i = 1; i <= TST; i ++ ) {
		printf("Case %d: ", i);
		memset(adj, 0, sizeof(adj));
		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));
		memset(C, 0, sizeof(C));
		int n;
		scanf("%d", &n);
		for ( int k = 1; k < n; k ++ ) {
			int u, v;
			scanf("%d%d", &u, &v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		for ( int k = 1; k <= n; k ++ ) {
			int a, b;
			scanf("%d%d", &a, &b);
			K[k] = (double)a / 100;
			E[k] = (double)b / 100;
		}
		dfs(1, 0);
		if ( fabs(1 - A[1]) < EPS ) 
			printf("impossible\n");
		else
			printf("%.6lf\n", C[1] / (1 - A[1]));
	}
}
