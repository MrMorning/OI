#include <cstdio>
#include <cstring>
#include <algorithm>
#define mp(a, b) make_pair(a,b)
using namespace std;
const int kMod = 99991, kBase = 100007;
pair<int, int> p[200010], ans[200010];
int n, m;
int nAns = 0;

struct HashMap {
	int begin[kMod], next[200010], size;
	pair<int, int> key[200010];
	void init() { 
		memset(begin, -1, sizeof(begin)); 
		size = 0;
	}
	void insert(pair<int, int> t) {
		int code = (t.first*kBase+t.second) % kMod;
		if ( code < 0 ) code += kMod;
		for ( int e = begin[code]; e != -1; e = next[e] ) 
			if ( key[e] == t ) return;
		key[size] = t;
		next[size] = begin[code];
		begin[code] = size;
		size++;
	}
	bool find(pair<int, int> t) {
		int code = (t.first*kBase+t.second) % kMod;
		if ( code < 0 ) code += kMod;
		for ( int e = begin[code]; e != -1; e = next[e] ) 
			if ( key[e] == t ) return true;
		return false;
	}
} HM;

bool check(int xo, int yo) {
	HM.init();
	int cnt = 0;
	for ( int i = 1; cnt <= m && i <= n; i ++ ) {
		int xt = xo-p[i].first, yt = yo-p[i].second;
		if ( !HM.find(mp(xt, yt)) ) {
			cnt++;
		}
	}
	return cnt <= m;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	if ( n <= m ) {
		printf("%d\n", -1);
		return 0;
	}
	for ( int i = 1; i <= n; i ++ )
		scanf("%d%d", &p[i].first, &p[i].second);
	for ( int i = 1; i <= n; i ++ ) 
		HM.insert(p[i]);
	sort(p+1,p+1+n);
	for ( int i = 1; i <= m+1; i ++ )
		for ( int j = n-m; j <= n; j ++ ) {
			if ( check(p[i].first+p[j].first, p[i].second+p[j].second) )
				ans[nAns++] = mp(p[i].first+p[j].first, p[i].second+p[j].second);
		}
	sort(ans, ans+nAns);
	nAns = unique(ans, ans+nAns)-ans;
	printf("%d\n", nAns);
	for ( int i = 0; i < nAns; i ++ )
		printf("%.10lf %.10lf\n", (double)ans[i].first/2, (double)ans[i].second/2);
}
