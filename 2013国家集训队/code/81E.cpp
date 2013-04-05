#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstring>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
const int kVMax = 100010;

struct Answer {
	int a, b;
	Answer(){}
	Answer(int aa, int bb):a(aa), b(bb){}
	bool operator< (const Answer &T) const {
		return a < T.a || (a==T.a&&b<T.b);
	}
	bool operator== (const Answer &T) const {
		return a == T.a && b == T.b;
	}
} f[kVMax][2], g[kVMax], val[kVMax];
vector<int> son[kVMax];
int nv, ptr[kVMax], sex[kVMax];
int inDgr[kVMax], stk[kVMax], top;
bool onCyc[kVMax], worked[kVMax];
int arr[kVMax];
int out[kVMax][2], nOut;
void addOut(int x) {
	out[nOut][0] = x, out[nOut][1] = ptr[x];
	nOut++;
}

Answer operator+ (const Answer &p, const Answer &q) {
	return Answer(p.a+q.a,p.b+q.b);
}
Answer operator- (const Answer &p, const Answer &q) {
	return Answer(p.a-q.a,p.b-q.b);
}

void workOnTree(int x) {
	foreach(it, son[x])
		workOnTree(*it);
	f[x][0] = Answer(0, 0);
	foreach(it, son[x])
		f[x][0] = f[x][0] + f[*it][1];
	f[x][1] = f[x][0];
	foreach(it, son[x])
		f[x][1] = max(f[x][1], f[x][0]-f[*it][1]+f[*it][0]+val[*it]);
}

void printOnTree(int x, int s) {
	if ( s == 0 || f[x][1] == f[x][0] )
		foreach(it, son[x])
			printOnTree(*it, 1);
	else
		foreach(it, son[x])
			if ( f[x][1] == f[x][0]-f[*it][1]+f[*it][0]+val[*it] ) {
				addOut(*it);
				printOnTree(*it, 0);
				foreach(it2, son[x])
					if ( *it2 != *it )
						printOnTree(*it2, 1);
				break;
			}
}

void rotate(int arr[], int n, int d) {
	static int arr2[kVMax];
	memcpy(arr2, arr, sizeof(int)*n);
	for ( int i = 0; i < n; i ++ )
		arr[i] = arr2[(i+d)%n];
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &nv);
	for ( int i = 1; i <= nv; i ++ ) {
		scanf("%d%d", &ptr[i], &sex[i]);
		inDgr[ptr[i]]++;
	}
	for ( int i = 1; i <= nv; i ++ ) {
		onCyc[i] = true;
		val[i] = Answer(1, sex[i]!=sex[ptr[i]]);
		if ( inDgr[i] == 0 )
			stk[top++] = i;
	}
	while ( top ) {
		int u = stk[--top];
		onCyc[u] = false;
		son[ptr[u]].push_back(u);
		inDgr[ptr[u]]--;
		if ( inDgr[ptr[u]]==0 )
			stk[top++] = ptr[u];
	}

	Answer totAns(0, 0);
	for ( int i = 1; i <= nv; i ++ )
		if ( onCyc[i] && !worked[i] ) {
			int nArr = 0, cur = i;
			do {
				arr[nArr++] = cur;
				worked[cur] = true;
				cur = ptr[cur];
			} while ( cur != i );
			reverse(arr, arr+nArr);
			//rotate(arr, nArr, 0);
			for ( int k = 0; k < nArr; k ++ )
				workOnTree(arr[k]);
			Answer curAns(0, 0);
			int connBest = 0;
			for ( int conn = 0; conn <= 1; conn ++ ) {
				if ( conn ) {
					g[0] = val[arr[0]]+f[arr[0]][0];
					g[1] = g[0]+f[arr[1]][1];
				} else {
					g[0] = f[arr[0]][1];
					g[1] = max(f[arr[0]][1]+f[arr[1]][1], f[arr[0]][0]+f[arr[1]][0]+val[arr[1]]);
				}
				if ( nArr >= 2 ) {
					for ( int k = 2; k < nArr-conn; k ++ )
						g[k] = max(g[k-1]+f[arr[k]][1], g[k-2]+val[arr[k]]+f[arr[k]][0]+f[arr[k-1]][0]);
					if ( conn )
						g[nArr-1] = g[nArr-2]+f[arr[nArr-1]][0];
				}
				if ( curAns < g[nArr-1] ) {
					curAns = g[nArr-1];
					connBest = conn;
				}
			}
			for ( int conn = connBest; conn <= connBest; conn ++ ) {
				if ( conn ) {
					g[0] = val[arr[0]]+f[arr[0]][0];
					g[1] = g[0]+f[arr[1]][1];
				} else {
					g[0] = f[arr[0]][1];
					g[1] = max(f[arr[0]][1]+f[arr[1]][1], f[arr[0]][0]+f[arr[1]][0]+val[arr[1]]);
				}
				if ( nArr >= 2 ) {
					for ( int k = 2; k < nArr-conn; k ++ )
						g[k] = max(g[k-1]+f[arr[k]][1], g[k-2]+val[arr[k]]+f[arr[k]][0]+f[arr[k-1]][0]);
					if ( conn )
						g[nArr-1] = g[nArr-2]+f[arr[nArr-1]][0];
				}
				if ( curAns < g[nArr-1] ) {
					curAns = g[nArr-1];
					connBest = conn;
				}
			}
			cur = nArr-1;
			while ( 1 ) {
				if ( nArr >= 2 && 2 <= cur && cur < nArr-connBest ) {
					if ( g[cur-1]+f[arr[cur]][1] < g[cur-2]+val[arr[cur]]+f[arr[cur]][0]+f[arr[cur-1]][0] ) {
						addOut(arr[cur]);
						printOnTree(arr[cur], 0);
						printOnTree(arr[cur-1], 0);
						cur = cur-2;
					} else {
						printOnTree(arr[cur], 1);
						cur = cur-1;
					}
				} else if ( cur == nArr-1 && connBest ) {
					printOnTree(arr[nArr-1], 0);
					cur = nArr-2;
				} else if ( cur == 1 ) {
					if ( connBest ) {
						printOnTree(arr[1], 1);
						cur = 0;
					} else {
						if ( f[arr[0]][1]+f[arr[1]][1]<f[arr[0]][0]+f[arr[1]][0]+val[arr[1]] ) {
							addOut(arr[1]);
							printOnTree(arr[0], 0);
							printOnTree(arr[1], 0);
						} else {
							printOnTree(arr[0], 1);
							printOnTree(arr[1], 1);
						}
						break;
					}
				} else {
					assert(cur == 0);
					if ( connBest ) {
						addOut(arr[0]);
						printOnTree(arr[0], 0);
					} else 
						printOnTree(arr[0], 1);
					break;
				}
			}

			totAns = totAns + curAns;
		}
	printf("%d %d\n", totAns.a, totAns.b);
	assert(totAns.a == nOut);
	for ( int i = 0; i < nOut; i ++ )
		printf("%d %d\n", out[i][0], out[i][1]);
}
