#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
using namespace std;
const int N_MAX = 310;
set<int> S;
bool vis[N_MAX * N_MAX];
int match[N_MAX * N_MAX];
int N, M;
int A[N_MAX], B[N_MAX];
int axis[N_MAX * N_MAX], axisCnt = 0;
int solCnt[N_MAX];
int ans[N_MAX];
int low[N_MAX], high[N_MAX];
struct Edge {
	int to;
	Edge *next;
} edge[N_MAX * N_MAX], *begin[N_MAX];
int edgeCnt = 0;
void addEdge(int u, int v) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u];
	begin[u] = e;
}

int ceilDiv(int a, int b) {
	if ( a % b == 0 )
		return a / b;
	return a / b + 1;
}

bool dfs(int x) {
	for ( Edge *e = begin[x]; e; e = e->next ) {
		int y = e->to;
		if ( vis[y] )
			continue;
		vis[y] = true;
		if ( match[y] == -1 || dfs(match[y]) ) {
			match[y] = x;
			return true;
		}
	}
	return false;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &M);
	for ( int i = 0; i < N; i ++ ) 
		scanf("%d%d", &A[i], &B[i]);
	for ( int i = 0; i < N; i ++ ) {
		if ( A[i] == 0 ) {
			if ( 1 <= B[i] && B[i] <= M )
				low[i] = high[i] = 0;
			else
				low[i] = 1, high[i] = 0;
		} else if ( A[i] > 0 ) {
			low[i] = max(0, ceilDiv(1 - B[i], A[i]));
			high[i] = (M - B[i]) / A[i];
		} else {
			high[i] = (1 - B[i]) / A[i];
			low[i] = max(0, ceilDiv((M - B[i]), A[i]));
		}

		solCnt[i] = max(0, high[i] - low[i] + 1);
		if ( solCnt[i] < N ) {
			for ( int k = low[i]; k <= high[i]; k ++ ) 
				axis[axisCnt++] = A[i] * k + B[i];
		}
	}
	sort(axis, axis + axisCnt);
	axisCnt = unique(axis, axis + axisCnt) - axis;

	for ( int i = 0; i < N; i ++ ) {
		if ( solCnt[i] < N ) {
			for ( int k = low[i]; k <= high[i]; k ++ ) {
				int x = A[i] * k + B[i];
				x = lower_bound(axis, axis + axisCnt, x) - axis;
				addEdge(i, x);
			}
		}
	}

	memset(match, -1, sizeof(match));
	memset(ans, -1, sizeof(ans));
	for ( int i = 0; i < N; i ++ ) {
		memset(vis, 0, sizeof(vis));
		dfs(i);
	}
	for ( int i = 0; i < axisCnt; i ++ )
		if ( match[i] != -1 ) {
			ans[match[i]] = axis[i];
			S.insert(axis[i]);
		}
	for ( int i = 0; i < N; i ++ )
		if ( solCnt[i] >= N ) {
			for ( int k = low[i]; k <= high[i]; k ++ ) {
				int x = A[i] * k + B[i];
				if ( S.find(x) == S.end() ) {
					ans[i] = x;
					S.insert(x);
					break;
				}
			}
		}

	for ( int i = 0; i < N; i ++ )
		if ( ans[i] == -1 ) {
			for ( int t = 1; t <= M; t ++ )
				if ( S.find(t) == S.end() ) {
					ans[i] = t;
					S.insert(t);
					break;
				}
		}

	for ( int i = 0; i < N; i ++ )
		printf("%d ", ans[i]);
}
