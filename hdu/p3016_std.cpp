#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

using namespace std;

int n, in[100010][4];
int dp[100010];
int cmp(const void *a, const void *b) {
	return *((int *)b) - *((int *)a);
}
map<int, int> bb;

void solve(int x) {
	map<int, int>::iterator b, e;
	int t;
	b = bb.upper_bound(in[x][1] - 1);
	e = bb.lower_bound(in[x][2] + 1);
	while(b != e) {
		t = b->second;
		if(dp[t] <= 0) {
			++b;
			continue;
		}
		if(dp[t] + in[x][3] > dp[x]) dp[x] = dp[t] + in[x][3];
		++b;
	}
	b = bb.upper_bound(in[x][1]);
	bb.erase(b, e);
	bb[in[x][1]] = x;
	bb[in[x][2]] = x;
}

int main() {
	freopen("t.in", "r", stdin);
	int max;
	while(scanf("%d", &n) != EOF) {
		for(int i = 0; i < n; ++i) {
			scanf("%d %d %d %d", in[i], in[i] + 1, in[i] + 2, in[i] + 3);
		}
		memset(dp, 0, sizeof(dp));
		qsort(in, n, sizeof(in[0]), cmp);
		dp[0] = 100 + in[0][3];
		bb.clear();
		bb[in[0][1]] = 0;
		bb[in[0][2]] = 0;
		for(int i = 1; i < n; ++i) {
			solve(i);
		}
		max = 0;
		for(map<int, int>::iterator i = bb.begin(); i != bb.end(); ++i) {
			if(dp[i->second] > max) max = dp[i->second];
		}
		if(max == 0) puts("-1");
		else printf("%d\n", max);
	}
	return 0;
}
