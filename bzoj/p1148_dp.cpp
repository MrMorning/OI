#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3fLL;
int n;
struct Pen {
	int c, w;
} p[200010];

ll f[1000][1000];

bool cmp_cw(const Pen &p1, const Pen &p2) {
	return p1.c + p1.w < p2.c + p2.w;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ ) 
		scanf("%d%d", &p[i].c, &p[i].w);
	sort(p + 1, p + n + 1, cmp_cw);
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for ( int i = 1; i <= n; i ++ ) {
		f[i][0] = 0;
		for ( int j = 1; j <= n; j ++ ) {
			f[i][j] = f[i - 1][j];
			if ( p[i].c >= f[i - 1][j - 1] )
				f[i][j] = min(f[i][j], f[i - 1][j - 1] + p[i].w);
		}
	}

	ll sumW;
	int maxL;
	for ( int j = n; j >= 1; j -- )
		if ( f[n][j] != inf ) {
			sumW = f[n][j];
			maxL = j;
			break;
		}

	cout << maxL << '\n' << sumW << '\n';
}
