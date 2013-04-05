#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int ds[5010];
struct Edge { 
	int u, v, id; double w;
	bool operator< (const Edge &E) const {
		return w < E.w || (w == E.w && id < E.id);
	}
} edge[100005];
bool chose[100005];
int n, m, k;
int find(int i) { return ds[i]==i?i:ds[i]=find(ds[i]); }
void merge(int i, int j) {
	i = find(i), j = find(j);
	ds[i] = j;
}

int check(double mid) {
	for ( int i = 1; i <= m; i ++ )
		if ( min(edge[i].u, edge[i].v) == 1 )
			edge[i].w += mid;
	sort(edge+1, edge+1+m);
	for ( int i = 1; i <= n; i ++ ) ds[i] = i;
	memset(chose, 0, sizeof(chose));
	int res = 0;
	for ( int i = 1; i <= m; i ++ ) {
		if ( find(edge[i].u) != find(edge[i].v) ) {
			merge(edge[i].u, edge[i].v);
			chose[i] = true;
			res += min(edge[i].u, edge[i].v) == 1;
		}
	}
	for ( int i = 1; i <= m; i ++ )
		if ( min(edge[i].u, edge[i].v) == 1 )
			edge[i].w -= mid;
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &k);
	for ( int i = 1; i <= m; i ++ ) {
		scanf("%d%d%lf", &edge[i].u, &edge[i].v, &edge[i].w);
		edge[i].id = i;
	}
	double lb = -1e6, rb = 1e6;
	if ( check(lb) < k || check(rb) > k ) {
		puts("-1");
		return 0;
	}
	for ( double mid = (lb + rb) / 2; ; mid = (lb + rb) / 2 ) {
//		fprintf(stderr, "%.3lf %.3lf\n", lb, rb);
		if ( check(mid) == k ) break;
		if ( check(mid) < k ) rb = mid;
		else lb = mid;
	}
	int cnt = 0;
	for ( int i = 1; i <= m; i ++ )
		cnt += chose[i];
	printf("%d\n", cnt);
	for ( int i = 1; i <= m; i ++ )
		if ( chose[i] )
			printf("%d ", edge[i].id);
}
