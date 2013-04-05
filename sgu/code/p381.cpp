#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int kEdgeMax = 500010;
const int kVMax = 100010;

struct Edge { 
	int to, w;
	Edge *next, *inv;
} edge[kEdgeMax*2], *begin[kVMax];
int edgeCnt = 0;
int color[kVMax];
int mem[kVMax], nMem;
bool fail;
int n, m;

Edge *makeEdge(int u, int v, int c) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->w = c, e->next = begin[u];
	begin[u] = e;
	return e;
}

void addEdge(int u, int v, int c1, int c2) {
	Edge *e1 = makeEdge(u, v, c2),
		 *e2 = makeEdge(v, u, c1);
	e1->inv = e2, e2->inv = e1;
}

void dfs(int x, int c) {
	if ( fail ) return;
	color[x] = c;
	mem[nMem++] = x;
	for ( Edge *e = begin[x]; e; e = e->next ) {
		int y = e->to;
		if ( color[y] == -1 ) {
			if ( (e->inv->w)*(c==1?-1:1)*e->w == -1 )
				dfs(y, 0);
			else
				dfs(y, 1);
		} else {
			if ( (e->inv->w)*(c==1?-1:1)*e->w*(color[y]==1?-1:1) != -1 ) {
				fail = true;
				return;
			}
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= m; i ++ ) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		addEdge(a, b, c, d);
	}
	memset(color, -1, sizeof(color));
	for ( int i = 1; i <= n; i ++ )
		if ( color[i] == -1 ) {
			nMem = 0;
			fail = false;
			dfs(i, 0);
			int cnt1 = 0, cnt2 = 0;

			if ( !fail ) {
				for ( int j = 0; j < nMem; j ++ ) {
					cnt1 += color[mem[j]] == 1;
					color[mem[j]] = -1;
				}
			} else cnt1 = 0x3f3f3f3f;

			fail = false;
			nMem = 0;
			dfs(i, 1);
			if ( !fail ) {
				for ( int j = 0; j < nMem; j ++ ) {
					cnt2 += color[mem[j]] == 1;
					color[mem[j]] = -1;
				}
			} else cnt2 = 0x3f3f3f3f;
			if ( cnt1 == cnt2 && cnt1 == 0x3f3f3f3f ) {
				puts("NO");
				return 0;
			}
			fail = false;
			nMem = 0;
			dfs(i, cnt1 > cnt2);
		}
	int tot = 0;
	for ( int i = 1; i <= n; i ++ )
		if ( color[i] == 1 ) tot ++;
	printf("YES\n%d\n", tot);
	//return 0;
	for ( int i = 1; i <= n; i ++ )
		if ( color[i] == 1 ) 
			printf("%d ", i);
}
