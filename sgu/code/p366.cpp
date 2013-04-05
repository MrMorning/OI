#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define pb(x) push_back(x)
#define mp(x, y) make_pair(x, y)
#define ALL(X) X.begin(),X.end()
using namespace std;

const int kInf = 0x3f3f3f3f;
const int DELTA1 = 50;
const int DELTA2 = 1000;

int n, m;
vector<pair<int, int> > group[101];
int f[102][21][2001], g[102][21][2001];
int preSum[102][21];
int ans[20], nAns;

bool cmp1(const pair<int, int> &p1, const pair<int, int> &p2) {
	return p1.second > p2.second;
}

void collect(int i, int k) {
	for ( int j = 0; j < k; j ++ )
		ans[nAns++] = group[i+DELTA1][j].first;
}

void output(int i, int j, int k) {
	int tmp = g[i+DELTA1][j][k+DELTA2];
	if ( tmp == -1 ) return;
	collect(i-1, tmp);
	output(i-1, j-tmp, k-tmp*(i-1));
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n ;i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		group[a-b+DELTA1].pb(mp(i, a+b));
	}
	for ( int i = -50; i <= 50; i ++ ) {
		sort(ALL(group[i+DELTA1]), cmp1);
		int sz = group[i+DELTA1].size();
		preSum[i+DELTA1][0] = 0;
		for ( int j = 0; j < min(sz, 20); j ++ ) 
			preSum[i+DELTA1][j+1] = preSum[i+DELTA1][j] + group[i+DELTA1][j].second;
	}
	memset(f, -1, sizeof(f));
	memset(g, -1, sizeof(g));
	f[-50+DELTA1][0][0+DELTA2] = 0;
	for ( int i = -50; i <= 50; i ++ )
		for ( int j = 0; j <= m; j ++ )
			for ( int k = -1000; k <= 1000; k ++ )
				if ( f[i+DELTA1][j][k+DELTA2] >= 0 ) {
					int val = f[i+DELTA1][j][k+DELTA2];
					int sz = group[i+DELTA1].size();
					for ( int t = 0; t <= sz; t ++ )
						if ( j+t <= m ) {
							int tmp = val+preSum[i+DELTA1][t];
							if ( tmp > f[i+1+DELTA1][j+t][k+t*i+DELTA2] ) {
								f[i+1+DELTA1][j+t][k+t*i+DELTA2] = tmp;
								g[i+1+DELTA1][j+t][k+t*i+DELTA2] = t;
							}
						}
				}
	int ans1 = kInf, ans2;
	for ( int k = -1000; k <= 1000; k ++ )
		if ( f[51+DELTA1][m][k+DELTA2] >= 0 ) {
			if ( abs(k) < abs(ans1) || 
					(abs(k) == abs(ans1) && ans2 < f[51+DELTA1][m][k+DELTA2]) ) {
				ans1 = k;
				ans2 = f[51+DELTA1][m][k+DELTA2];
			}
		}
	printf("%d %d\n", (ans1+ans2)/2, (ans2-ans1)/2);
	output(51, m, ans1);
	sort(ans, ans+nAns);
	for ( int i = 0; i < nAns; i ++ )
		printf("%d ", ans[i]);
}
