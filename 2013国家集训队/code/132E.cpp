#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#define LV(x) (x)
#define RV(x) ((x)+tot)
using namespace std;

const int kVtxMax = 2*300;
const int kEdgeMax = kVtxMax * kVtxMax;
const int kInf = 0x3f3f3f3f;

struct Edge {
	int to,cap,cost;
	Edge *next,*inv;
} edge[kEdgeMax], *begin[kVtxMax], *prev[kVtxMax];
int edgeCnt = 0;
int dist[kVtxMax], Q[kVtxMax];
bool inQ[kVtxMax];
int sVtx, tVtx;

Edge *makeEdge(int u, int v, int c, int w) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u], e->cap =c ,e->cost = w;
	begin[u] = e;
	return e;
}

void addEdge(int u, int v, int c, int w) {
//	fprintf(stderr, "%d->%d, c=%d, w=%d\n", u, v, c, w);
	Edge *e1 = makeEdge(u, v, c, w),
		 *e2 = makeEdge(v, u, 0, -w);
	e1->inv = e2, e2->inv = e1;
}

bool spfa() {
	memset(prev, 0, sizeof(prev));
	memset(dist, 0x3f, sizeof(dist));
	dist[sVtx] = 0;
	int qh = 0, qt = 0;
	Q[qt++] = sVtx;
	inQ[sVtx] = true;
	while ( qh != qt ) {
		int u = Q[qh];
		qh = (qh+1) % kVtxMax;
		inQ[u] = false;

		for ( Edge *e = begin[u]; e; e = e->next )
			if ( e->cap ) {
				int v = e->to;
				int tmp = dist[u] + e->cost;
				if ( tmp < dist[v] ) {
					dist[v] = tmp;
					prev[v] = e;
					if ( !inQ[v] ) {
						inQ[v] = true;
						Q[qt] = v;
						qt = (qt + 1) % kVtxMax;
					}	
				}
			}
	}
	return dist[tVtx] != kInf;
}

int mcmf() {
	int res = 0;
	while ( spfa() ) {
		int flow = kInf;
		for ( Edge *e = prev[tVtx]; e; e = prev[e->inv->to] )
			flow = min(flow, e->cap);
		for ( Edge *e = prev[tVtx]; e; e = prev[e->inv->to] ) {
			e->cap -= flow, e->inv->cap += flow;
			res += flow * e->cost;
		}
	}
	return res;
}

int n, m;
int num[300], arr[300], nArr;
char alp[300];
int nAss;
pair<char, int> ass[600];
int curVal[26];
int eval(int i) {
	int res = 0, tmp = num[i];
	while ( tmp ) {
		res += tmp & 1;
		tmp >>= 1;
	}
	return res;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d", &num[i]);
		arr[nArr++] = num[i];
	}
	sort(arr, arr+nArr);
	nArr = unique(arr, arr+nArr)-arr;
	int ext = min(nArr, m), tot = n + ext;

	int nVtx = 2*tot+2;
	sVtx = nVtx-1, tVtx = nVtx;
	for ( int i = 1; i <= n; i ++ )
		for ( int j = i + 1; j <= n; j ++ )
			addEdge(LV(i), RV(j), 1, num[i]==num[j]?0:eval(j));
	for ( int i = 1; i <= ext; i ++ )
		for ( int j = 1; j <= n; j ++ )
			addEdge(LV(n+i), RV(j), 1, eval(j));
	for ( int i = 1; i <= tot; i ++ ) {
		addEdge(sVtx, LV(i), 1, 0);
		addEdge(RV(i), tVtx, 1, 0);
	}
	int res = mcmf();
	for ( int i = 1; i <= ext; i ++ ) {
		int cur = i+n;
		while ( 1 ) {
			int nxt = 0;
			for ( Edge *e = begin[LV(cur)]; e; e = e->next ) 
				if ( e->to != sVtx && !e->cap ) {
					nxt = e->to;
					break;
				}
			if ( !nxt ) break;
			nxt -= tot;
			alp[nxt] = 'a'+i-1;
			cur = nxt;
		}
	}

	int testVal = 0;
	for ( int i = 1; i <= n; i ++ ) {
		bool found = false;
		for ( int j = i-1; j >= 1; j -- ) 
			if ( alp[j] == alp[i] ) {
				found = num[j] == num[i];
				break;
			}
		if ( !found ) {
			ass[nAss++] = make_pair(alp[i], num[i]);
			testVal += eval(i);
		}
		ass[nAss++] = make_pair(alp[i], -1);
	}
	assert(testVal == res);
	printf("%d %d\n", nAss, res);
	for ( int i = 0, ptr = 1; i < nAss; i ++ ) 
		if ( ass[i].second == -1 ) {
			if(num[ptr++] != curVal[ass[i].first-'a'])
				assert(0);
			printf("print(%c)\n", ass[i].first);
		} else {
			if(!('a' <= ass[i].first && ass[i].first <= 'z'))
				assert(0);
			printf("%c=%d\n", ass[i].first, ass[i].second);
			curVal[ass[i].first-'a'] = ass[i].second;
		}
}
