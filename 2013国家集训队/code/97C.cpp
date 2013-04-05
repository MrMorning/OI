#include <cstdio>
#include <cstring>

const int kNMax = 105;
const int kVtxMax = kNMax*2, kEdgeMax = kVtxMax*kVtxMax;

struct Edge {
	int to;
	double weight;
	Edge *next;
} edge[kEdgeMax], *begin[kVtxMax];
int Q[kVtxMax];
double dist[kVtxMax];
int cnt[kVtxMax];
bool inQ[kVtxMax];
int edgeCnt = 0;
double p[kNMax];
int n;

void addEdge(int u, int v, double w) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u], begin[u] = e;
	e->weight = w;
}

bool check(double ans) {
	edgeCnt = 0;
	memset(begin, 0, sizeof(begin));
	for ( int i = 0; i <= 2*n; i ++ )
		for ( int j = 0; j <= n; j ++ ) {
			int ni = i+n-2*j;
			if ( 0 <= ni && ni <= 2*n )
				addEdge(i, ni, 1-ans*p[j]);
		}
	int qh = 0, qt = 0;
	for ( int i = 0; i <= 2*n; i ++ ) {
		Q[qt++] = i;
		cnt[i] = 1;
		inQ[i] = true;
	}

	memset(dist, 0, sizeof(dist));

	while ( qh != qt ) {
		int u = Q[qh];
		qh = (qh + 1) % kVtxMax;
		inQ[u] = false;
		if ( cnt[u] > 2*n+5 ) return true;
		for ( Edge *e = begin[u]; e; e = e->next ) {
			int v = e->to;
			double tmp = dist[u] + e->weight;
			if ( tmp < dist[v] ) {
				dist[v] = tmp;
				if ( !inQ[v] ) {
					inQ[v] = true;
					cnt[v]++;
					Q[qt] = v;
					qt = (qt + 1) % kVtxMax;
				}
			}
		}
	}
	return false;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i <= n; i ++ )
		scanf("%lf", &p[i]);
	double lb = 0, rb = 1e7;
	for ( int cnt = 0; cnt < 100; cnt ++ ) {
		double mid = (lb + rb) / 2;
		if ( check(mid) )
			rb = mid;
		else
			lb = mid;
	}
	printf("%.10lf\n", 1.0/lb);
}
