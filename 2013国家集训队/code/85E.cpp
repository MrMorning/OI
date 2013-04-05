#include <cstdio>
#include <vector>
#include <algorithm>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
typedef long long ll;
const int kMod = 1000000007;
int n, parent[5010];
int val[5010], x[5010], y[5010];
vector<pair<int, int> > vec[10010];
int ans1, ans2;

int powMod(int a, int n) {
	int res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = (ll)a * a % kMod;
		if ( n & 1 )
			res = (ll)res * a % kMod;
	}
	return res;
}

int find(int x) {
	return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void merge(int i, int j) {
	bool inv = val[i] == val[j];
	int p = find(i);
	for ( int k = 0; k < n; k ++ )
		if ( find(k) == p )
			val[k] ^= inv;
	parent[p] = find(j);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ )
		scanf("%d%d", &x[i], &y[i]);
	for ( int i = 0; i < n; i ++ )
		for ( int j = i; j < n; j ++ ) {
			int dist = abs(x[i]-x[j])+abs(y[i]-y[j]);
			vec[dist].push_back(make_pair(i, j));
		}
	bool fail = false;
	int nComp = n;
	for ( int i = 0; i < n; i ++ ) {
		parent[i] = i;
		val[i] = 0;
	}
	for ( int i = 10000; i >= 0; i -- ) {
		int compCp = nComp;
		foreach(it, vec[i]) 
			if ( find(it->first) == find(it->second) ) {
				if ( val[it->first] == val[it->second] ) {
					fail = true;
					break;
				}
			}  else {
				merge(it->first, it->second);
				nComp--;
			}
		if ( fail ) {
			ans1 = i;
			ans2 = powMod(2, compCp);
			break;
		}	
	}
	printf("%d\n%d\n", ans1, ans2);
}
