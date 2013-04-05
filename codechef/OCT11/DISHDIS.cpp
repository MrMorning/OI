#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

ll f[101][101];
int n, m, l[101], r[101];

void solve()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++)
		scanf("%d%d", &l[i], &r[i]);
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	for(int i = 1; i <= m; i ++)
		for(int j = 0; j <= n; j ++)
		{
			for(int k = l[i]; k <= min(j, r[i]); k ++)
				f[i][j] += f[i - 1][j - k];
			f[i][j] %= 1000000007;
		}
	printf("%lld\n", f[m][n]);
}

int main()
{
	freopen("t.in", "r", stdin);
	int _;
	scanf("%d", &_);
	while(_ --)
		solve();
}
