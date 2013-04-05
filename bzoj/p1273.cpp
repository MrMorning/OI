#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m, x[100000], cnt[17][65536], sum[17][65536];
inline int calc(int i, int lb, int rb)
{
	if(lb > rb)
		return 0;
	lb = max(0, lb), rb = min((1 << 16) - 1, rb);
	return sum[i][rb] - (lb == 0 ? 0 : sum[i][lb - 1]);
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i ++)
		scanf("%d", &x[i]);
	for(int i = 0; i < n; i ++)
		for(int j = 1; j <= 16; j ++)
			cnt[j][x[i] % (1 << j)] ++;
	for(int i = 1; i <= 16; i ++)
		for(int j = 0; j < (1 << 16); j ++)
			sum[i][j] = (j == 0 ? 0 : sum[i][j - 1]) + cnt[i][j];
	int delta = 0;
	ll ans = 0;
	while(m --)
	{
		char cmd[10];
		int t;
		scanf("%s %d\n", cmd, &t);
		if(cmd[0] == 'Q')
		{
			t ++;
			int tmp = delta % (1 << t);
			int res1 = calc(t, (1 << (t - 1)) - tmp, (1 << t) - tmp - 1);
			int res2 = calc(t, (1 << (t - 1)) + (1 << t) - tmp, (1 << 16) - 1);
			ans += res1 + res2;
		}
		else
			delta = (delta + t) % (1 << 16);
	}
	printf("%lld\n", ans);
}
