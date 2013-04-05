#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

const int WIDTH = 305;
const int EDGE_MAX = 2 * WIDTH * WIDTH;
const int VTX_MAX = 4 * WIDTH;

inline int sgn(int n) {
	return n & 1 ? -1 : 1;
}
struct Edge {
	int to;
	Edge *next;
} edge[EDGE_MAX], *begin[VTX_MAX], *_begin_[VTX_MAX];
int edgeCnt = 0;

void addEdge(int u, int v) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u], begin[u] = e;
//	fprintf(stderr, "%d->%d\n", u, v);
}
void setCertain(int x) {
	addEdge(x^1,x);
}

void save() {
	memcpy(_begin_, begin, sizeof(begin));
}
void load() {
	memcpy(begin, _begin_, sizeof(_begin_));
	edgeCnt--;
}

int N, M;
int nVtx;
int sum[2][WIDTH][WIDTH], A[WIDTH][WIDTH], B[WIDTH][WIDTH];
int rowId[WIDTH][2], colId[WIDTH][2];
int low[VTX_MAX], dfn[VTX_MAX], stk[VTX_MAX], stop, belong[VTX_MAX];
bool inStk[VTX_MAX];
int nScc = 0;
bool fail = false;
void tarjan(int x) {
	if ( fail )
		return;
	static int timeStamp = 0;
	dfn[x] = low[x] = timeStamp++;
	inStk[x] = true;
	stk[stop++] = x;
	for ( Edge *e = begin[x]; !fail && e; e = e->next ) {
		int y = e->to;
		if ( dfn[y] == -1 ) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if ( inStk[y] )
			low[x] = min(low[x], dfn[y]);
	}
	if ( low[x] == dfn[x] ) {
		nScc++;
		while ( 1 ) {
			int u = stk[--stop];
			inStk[u] = false;
			belong[u] = nScc;
			if ( belong[u] == belong[u^1] ) {
				fail = true;
				return;
			}
			if ( u == x )
				break;
		}
	}
}

bool check() {
	memset(dfn, -1, sizeof(dfn));
	memset(inStk, 0, sizeof(inStk));
	memset(belong, -1, sizeof(belong));
	stop = 0;
	nScc = 0;
	fail = false;

	for ( int i = 0; !fail && i < nVtx; i ++ )
		if ( dfn[i] == -1 )
			tarjan(i);
	if ( fail )
		return false;
	for ( int i = 0; i < nVtx; i += 2 )
		if ( belong[i] == belong[i + 1] )
			return false;
	return true;
}

int main() {
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d%d", &N, &M);
	for ( int i = 2; i <= N; i ++ ) {
		static char ts[WIDTH];
		scanf("%s", ts);
		for ( int j = 2; j <= M; j ++ )
			B[i][j] = ts[j - 2] - '0';
	}
	for ( int i = 2; i <= N; i ++ )
		for ( int j = 2; j <= M; j ++ ) {
			sum[0][i][j] = sum[0][i][j - 1] + sum[0][i - 1][j] - sum[0][i - 1][j - 1];
			sum[1][i][j] = sum[1][i][j - 1] + sum[1][i - 1][j] - sum[1][i - 1][j - 1];
			if ( (i + j) & 1 ) {
				sum[1][i][j] += B[i][j];
				sum[0][i][j] -= B[i][j];
			} else {
				sum[0][i][j] += B[i][j];
				sum[1][i][j] -= B[i][j];
			}
		}
	for ( int i = 2; i <= N; i ++ )
		rowId[i][0] = nVtx++, rowId[i][1] = nVtx++;
	for ( int j = 2; j <= M; j ++ )
		colId[j][0] = nVtx++, colId[j][1] = nVtx++;
	for ( int val0 = 0; val0 <= 1; val0 ++ ) {
		memset(begin, 0, sizeof(begin));
		edgeCnt = 0;
		bool noSol = false;
		for ( int i = 2; !noSol && i <= N; i ++ )
			for ( int j = 2; !noSol && j <= M; j ++ ) {
				int k = sgn(i + j + 1) * val0 + sum[(i + j) & 1][i][j];
				int rowCoef = sgn(j + 1), colCoef = sgn(i + 1);
				//fprintf(stderr, "(%d,%d):K = %d, rowC = %d, colC = %d\n", i, j, k, rowCoef, colCoef);
				if ( rowCoef == -1 && colCoef == 1 ) {
					if ( k == 0 ) {
						addEdge(rowId[i][1], colId[j][1]);
						addEdge(colId[j][0], rowId[i][0]);
					} else if ( k == 1 ) {
						addEdge(rowId[i][0], colId[j][0]);
						addEdge(colId[j][1], rowId[i][1]);
					} else if ( k == 2 ) {
						setCertain(rowId[i][1]);
						setCertain(colId[j][0]);
					} else if ( k == -1 ) {
						setCertain(rowId[i][0]);
						setCertain(colId[j][1]);
					} else 
						noSol = true;
				} else if ( rowCoef == -1 && colCoef == -1 ) {
					if ( k == 0 ) {
						setCertain(rowId[i][0]);
						setCertain(colId[j][0]);
					} else if ( k == 1 ) {
						addEdge(rowId[i][1], colId[j][0]);
						addEdge(colId[j][1], rowId[i][0]);
					} else if ( k == 2 ) {
						addEdge(rowId[i][0], colId[j][1]);
						addEdge(colId[j][0], rowId[i][1]);
					} else if ( k == 3 ) {
						setCertain(rowId[i][1]);
						setCertain(colId[j][1]);
					} else
						noSol = true;
				} else if ( rowCoef == 1 && colCoef == -1 ) {
					if ( k == 0 ) {
						addEdge(colId[j][1], rowId[i][1]);
						addEdge(rowId[i][0], colId[j][0]);
					} else if ( k == 1 ) {
						addEdge(colId[j][0], rowId[i][0]);
						addEdge(rowId[i][1], colId[j][1]);
					} else if ( k == 2 ) {
						setCertain(colId[j][1]);
						setCertain(rowId[i][0]);
					} else if ( k == -1 ) {
						setCertain(colId[j][0]);
						setCertain(rowId[i][1]);
					} else 
						noSol = true;
				} else {
					if ( k == 0 ) {
						addEdge(rowId[i][1], colId[j][0]);
						addEdge(colId[j][1], rowId[i][0]);
					} else if ( k == 1 ) {
						setCertain(rowId[i][0]);
						setCertain(colId[j][0]);
					} else if ( k == -1 ) {
						addEdge(rowId[i][0], colId[j][1]);
						addEdge(colId[j][0], rowId[i][1]);
					} else if ( k == -2 ) {
						setCertain(rowId[i][1]);
						setCertain(colId[j][1]);
					} else
						noSol = true;
				}
			}
		if ( !check() ) 
			noSol = true;
		if ( noSol )
			continue;

		A[1][1] = val0;

		for ( int i = 0; i < nVtx; i += 2 ) {
			save();
			addEdge(i, i + 1);
			if ( check() ) {
				if ( i < (N - 1) * 2 )
					A[i/2+2][1] = 1;
				else
					A[1][(i-(N-1)*2)/2+2] = 1;
			} else {
				load();
				addEdge(i + 1, i);
				if ( i < (N - 1) * 2 )
					A[i/2+2][1] = 0;
				else
					A[1][(i-(N-1)*2)/2+2] = 0;
			}
		}

		for ( int i = 2; i <= N; i ++ )
			for ( int j = 2; j <= M; j ++ ) {
				int k = sgn(i + j + 1) * val0 + sum[(i + j) & 1][i][j];
				int rowCoef = sgn(j + 1), colCoef = sgn(i + 1);
				A[i][j] = k + rowCoef * A[i][1] + colCoef * A[1][j];
				assert(0 <= A[i][j] && A[i][j] <= 1);
			}

		for ( int i = 1; i <= N; i ++, puts("") )
			for ( int j = 1; j <= M; j ++ )
				printf("%d", A[i][j]);

		return 0;
	}
	printf("CORRUPT\n");
}
