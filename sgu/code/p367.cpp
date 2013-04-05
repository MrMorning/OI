#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int kNMax = 1010;
const int kMMax = 10010;

struct Edge {
	Edge *next;
	int to;
} edge[kMMax], *begin[kNMax];
int edgeCnt = 0;
int dfn[kNMax], low[kNMax];
int stk[kNMax], top;
int belong[kNMax], size[kNMax], sccCnt;
bool inStk[kNMax], del[kNMax];
int n, T, len[kNMax], m;
int inDgr[kNMax];
int arr[kNMax], nArr;
int ans[kNMax], nAns;

void addEdge(int u, int v) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u];
	begin[u] = e;
}

void tarjan(int x) {
	static int stamp = 0;
	dfn[x] = low[x] = ++stamp;
	stk[top++] = x;
	inStk[x] = true;

	for ( Edge *e = begin[x]; e; e = e->next ) {
		int y = e->to;
		if ( !dfn[y] ) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if ( inStk[y] )
			low[x] = min(low[x], dfn[y]);
	}

	if ( low[x] == dfn[x] ) {
		sccCnt++;
		while ( 1 ) {
			int t = stk[--top];
			belong[t] = sccCnt;
			inStk[t] = false;
			size[sccCnt]++;
			if ( t == x ) break;
		}
	}
}

void expand(int x) {
	del[x] = true;
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( !del[e->to] )
			expand(e->to);
}

bool cmpLen(int i, int j) {
	return len[i] < len[j];
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &T);
	for ( int i = 1; i <= n; i ++ )
		scanf("%d", &len[i]);
	scanf("%d", &m);
	while ( m -- ) {
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b);
	}
	for ( int i = 1; i <= n; i ++ )
		if ( !dfn[i] ) 
			tarjan(i);
	for ( int i = 1; i <= n; i ++ )
		if ( size[belong[i]] > 1 && !del[i] ) {
			expand(i);
		}
	for ( int i = 1; i <= n; i ++ )
		if ( !del[i] )
			arr[nArr++] = i;
	sort(arr, arr+nArr, cmpLen);

	for ( int i = 0; i < nArr; i ++ ) {
		int st = i;
		static int tmp[kNMax];
		int nTmp = 0;
		tmp[nTmp++] = arr[i];
		while ( i+1 < nArr && len[arr[i+1]] == len[arr[i]] ) 
			tmp[nTmp++] = arr[++i];

		for ( int k = 0; k < nTmp; k ++ ) inDgr[tmp[k]] = 0;
		for ( int k = 0; k < nTmp; k ++ )
			for ( Edge *e = begin[tmp[k]]; e; e = e->next )
				if ( !del[e->to] && len[e->to] == len[tmp[k]] )
					inDgr[e->to]++;
		for ( int k = 0; k < nTmp; k ++ )
			if ( inDgr[tmp[k]] == 0 ) 
				stk[top++] = tmp[k];
		while ( top ) {
			int u = stk[--top];
			arr[st++] = u;
			for ( Edge *e = begin[u]; e; e = e->next )
				if ( !del[e->to] && len[e->to] == len[u] ) {
					inDgr[e->to]--;
					if ( inDgr[e->to] == 0 )
						stk[top++] = e->to;
				}
		}
	}

	int acc = 0, penalty = 0;
	for ( int i = 0; i < nArr; i ++ ) {
		int x = arr[i];
		if ( len[x] + acc > T ) break;
		penalty += len[x] + acc;
		acc += len[x];
		ans[nAns++] = x;
	}
	printf("%d %d\n", nAns, penalty);
	for ( int i = 0; i < nAns; i ++ )
		printf("%d ", ans[i]);
}
