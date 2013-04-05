#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
const double inf = 1e100;
int x[5555];
vector<pair<int, int> > horse[5555];
double f[5555];
int arr[5555];
int n, B;

bool cmpX(int i, int j) {
	return x[i] < x[j];
}

int main() {
	scanf("%d%d", &B, &n);
	for ( int i = 1; i <= n; i ++ ) {
		int m;
		scanf("%d%d", &x[i], &m);
		static vector<pair<int, int> > tv;
		tv.clear();
		while ( m -- ) {
			int v, d;
			scanf("%d%d", &v, &d);
			tv.push_back(make_pair(d, v));
		}
		sort(tv.begin(), tv.end());
		int sz = tv.size();
		static int tmp[100010];
		tmp[sz] = 0;
		for ( int k = sz - 1; k >= 0; k -- )
			tmp[k] = max(tmp[k + 1], tv[k].second);
		for ( int k = 0; k < sz; k ++ ) 
			if ( tv[k].second > tmp[k + 1] ) {
				horse[i].push_back(tv[k]);
			}
		arr[i] = i;
	}
	arr[n + 1] = n + 1; 
	x[n + 1] = B;
	n ++;
	sort(arr + 1, arr + 1 + n, cmpX);
	if ( x[arr[1]] != 0 ) {
		puts("-1");
		return 0;
	}
	for ( int i = 1; i <= n; i ++ )
		f[i] = inf;
	f[1] = 0.0;
	for ( int i = 1; i <= n; i ++ ) {
		int u = arr[i];
		if ( x[u] == B ) {
			if ( f[i] == inf ) 
				puts("-1");
			else
				printf("%.8lf\n", f[i]);
			return 0;
		}
		if ( f[i] == inf )
			continue;
		int ptr = 0, sz = horse[u].size();
		for ( int j = i + 1; j <= n; j ++ ) {
			int v = arr[j];
			while ( ptr + 1 < sz && (horse[u][ptr].first + x[u] < x[v]) )
				ptr ++;
			if ( ptr < sz && horse[u][ptr].first + x[u] >= x[v] )
				f[j] = min(f[j], f[i] + ((double)(x[v] - x[u]) / horse[u][ptr].second));
		}
	}
	assert(0);
}
