#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;
const int kEdgeMax = 22000;
const int kVtxMax = 10010;
vector<int> ans, ans1, ans2;

struct Edge {
	int to, id;
	Edge *next, *inv;
	bool mark;
} edge[kEdgeMax], *begin[kVtxMax];
int edgeCnt = 0;
int stk[kEdgeMax], top;
int dgr[kVtxMax];
bool exist[kVtxMax];
bool colored[kVtxMax];

Edge *makeEdge(int u, int v, int id) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u];
	e->id = id;
	begin[u] = e;
	return e;
}

void addEdge(int u, int v, int id) {
	Edge *e1 = makeEdge(u, v, id),
		 *e2 = makeEdge(v, u, id);
	e1->inv = e2, e2->inv = e1;
}

void dfs(int x) {
	for ( Edge *e = begin[x]; e; e = e->next )
		if ( !e->mark ) {
			e->mark = e->inv->mark = true;
			dfs(e->to);
			stk[top++] = e->id;
		}
}

void solve(int r) {
	static bool gotit[kVtxMax];
	static int Q[kVtxMax];
	ans.clear();
	memset(gotit, 0, sizeof(gotit));
	int qh = 0, qt = 0;
	Q[qt++] = r;
	gotit[r] = true;
	while ( qh != qt ) {
		int u = Q[qh++];
		for ( Edge *e = begin[u]; e; e = e->next ) {
			int v = e->to;
			if ( gotit[v] ) continue;
			gotit[v] = true;
			Q[qt++] = v;
		}
	}
	int odd = r;
	int oddCnt = 0;
	for ( int i = 0; i < qt; i ++ )
		if ( dgr[Q[i]] % 2 == 1 ) {
			odd = Q[i];
			oddCnt ++;
		}
	if ( oddCnt != 0 && oddCnt != 2 ) return;
	top = 0;
	dfs(odd);
	while ( top ) 
		ans.push_back(stk[--top]);
}

void color(int x) {
	colored[x] = true;
	for ( Edge *e = begin[x]; e; e = e->next ) {
		if ( !colored[e->to] )
			color(e->to);
	}
}

int main() {
	//freopen("t.in", "r", stdin);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int m;
	scanf("%d", &m);
	for ( int i = 0; i < m; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		exist[a] = exist[b] = true;
		addEdge(a, b, i+1);
		dgr[a]++, dgr[b]++;
	}

	static int comp[kVtxMax];
	int compCnt = 0;
	for ( int i = 1; i <= 10000; i ++ )
		if ( exist[i] && !colored[i] ) {
			color(i); comp[compCnt++] = i;
		}
	if ( compCnt >= 3 ) puts("-1");
	else if ( compCnt == 2 ) {
		solve(comp[0]);
		ans1 = ans;
		solve(comp[1]);
		ans2 = ans;
		if ( ans1.size() == 0 || ans2.size() == 0 ) puts("-1");
		else {
			printf("%d\n", ans1.size());
			for ( int i = 0; i < ans1.size(); i ++ )
				printf("%d ", ans1[i]);
			puts("");
			printf("%d\n", ans2.size());
			for ( int i = 0; i < ans2.size(); i ++ )
				printf("%d ", ans2[i]);
		}
	} else {
		static int odd[kVtxMax];
		int oddCnt = 0;
		for ( int i = 1; i <= 10000; i ++ )
			if ( exist[i] && dgr[i] % 2 == 1 )
				odd[oddCnt++] = i;
		if ( oddCnt == 0 || oddCnt == 2 ) {
			solve(comp[0]);
			if ( ans.size() <= 1 ) puts("-1");
			else {
				printf("1\n%d\n", ans[0]);
				printf("%d\n", ans.size()-1);
				for ( int i = 1; i < ans.size(); i ++ )
					printf("%d ", ans[i]);
			}
		} else if ( oddCnt > 4 ) puts("-1");
		else {
			assert(oddCnt == 4);

			addEdge(odd[0], odd[1], -1);
			dgr[odd[0]]++; dgr[odd[1]]++;
			solve(comp[0]);
			int L1;
			for ( int i = 0; i < ans.size(); i ++ )
				if ( ans[i] == -1 ) L1 = i;
			printf("%d\n", L1);
			for ( int i = 0; ans[i] != -1; i ++ )
				printf("%d ", ans[i]);
			puts("");
			printf("%d\n", ans.size() - L1 - 1);
			for ( int i = L1+1; i < ans.size(); i ++ )
				printf("%d ", ans[i]);
		}
	}
}
