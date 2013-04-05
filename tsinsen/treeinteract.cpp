#define UDEB
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>
#define pb(x) push_back(x)
#define mp(x, y) make_pair(x, y)
using namespace std;

const int kNMax = 300010;

#ifndef UDEB
int tst;
int n, root, A[kNMax], pre[kNMax];
bool vis[kNMax];

int size() {
	return n;
}
int type() {
return 3;}
bool isAnc(int p, int q) {
	int cur = q;
	while ( 1 ) {
		if ( !pre[cur] ) return false;
		else if ( pre[cur] == p ) return true;
		cur = pre[cur];
	}
}
int question(int p, int q) {
	if ( isAnc(p, q) ) return 1;
	else if ( isAnc(q, p) ) return -1;
	return 0;
}
void submit(int x) {
	if ( x == root || vis[pre[x]] )
		vis[x] = true;
	else {
		printf("%d\n", n);
		for ( int i = 1; i <= n; i ++ )
			printf("%d->%d\n", i, pre[i]);
		assert(0);
	}
}
int makeTree(int l, int r) {
	int mid = rand()%(r-l+1)+l;
	if ( l != mid ) {
		int lch = makeTree(l, mid-1);
		pre[lch] = A[mid];
	}
	if ( r != mid ) {
		int rch = makeTree(mid+1, r);
		pre[rch] = A[mid];
	}
	return A[mid];
}

void buildTree() {
	n = rand() % 10 + 1;
	memset(vis, 0, sizeof(bool)*(n+1));
	memset(pre, 0, sizeof(int)*(n+1));
	for ( int i = 1; i <= n; i ++ )
		A[i] = i;
	random_shuffle(A+1, A+1+n);
	root = makeTree(1, n);
}
#endif

bool myCmp(int i, int j) {
	return question(i, j) == 1;
}

int T[kNMax], path[kNMax], belong[kNMax], res[kNMax];
bool onpath[kNMax];

bool cmpBelong(int i, int j) {
	return belong[i] < belong[j];
}

void solve(int l, int r) {
	int sz = r-l+1,
		p = T[rand() % sz+l];
	if ( sz == 1 ) {
		submit(p);
		return;
	}
	int pathL = 0;
	path[pathL++] = p;
	belong[p] = p;
	for ( int i = 0; i < sz; i ++ ) {
		int x = T[l+i];
		onpath[x] = false;
		if ( x == p ) continue;
		res[x] = question(x, p);
		if ( res[x] == 1 )
			path[pathL++] = x;
		else if ( res[x] == -1 )
			belong[x] = p;
	}
	stable_sort(path, path+pathL, myCmp);
	for ( int i = 0; i < pathL-1; i ++ ) {
		submit(path[i]);
		onpath[path[i]] = true;
	}

	for ( int i = 0; i < sz; i ++ ) {
		int x = T[l+i];
		if ( onpath[x] || x == p ) continue;
		if ( res[x] == 0 ) {
			int lb = 0, rb = pathL-1;
			while ( lb < rb - 1 ) {
				int mid = (lb + rb) / 2;
				if ( question(path[mid], x) == 1 )
					lb = mid;
				else
					rb = mid;
			}
			belong[x] = path[lb];
		}
	}
	for ( int i = 0; i < pathL-1; i ++ )
		belong[path[i]] = 0;
	sort(T+l, T+r+1, cmpBelong);
	for ( int i = l+pathL-1; i <= r; i ++ ) {
		int st = i;
		while ( i+1 <= r && belong[T[i+1]] == belong[T[i]] )
			i++;
		solve(st, i);
	}
}


int main() {
	//while ( 1 ) {
	//	buildTree();

		int n = size();
		for ( int i = 1; i <= n; i ++ )
			T[i] = i;
		if ( type() == 1 ) {
			stable_sort(T+1, T+1+n, myCmp);
			for ( int i = 1; i <= n; i ++ )
				submit(T[i]);
		} else 
			solve(1, n);
	//}
}
