#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 50005, M = 1005, MOD = 10007;
int a[N], n, m, s[N];
bool ok(int len)
{
	int register cnt = 0, t = 0;
	for (int register i = 1; i <= n; i ++)
	{
		t += a[i];
		if (t > len)
			cnt ++, t = a[i];
		if (t > len)
			return false;
		if (cnt == m + 1)
			return false;
	}
	return (++ cnt) <= m + 1;
}
int work(int min)
{
	int l = min, r = s[n];
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (ok(mid))
			r = mid;
		else l = mid + 1;
	}
	return l;
}
int arr[2][N];
int pos[N], q[N], qh, qt;
int sum[N];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	int mv = 1 << 30;
	for (int i = 1; i <= n; i ++)
		scanf("%d", a + i), s[i] = s[i - 1] + a[i], mv = min(mv, a[i]);
	int ans = work(mv);

	// calc position
	qh = 1, qt = 1;
	q[1] = 1;
	pos[1] = 1;
	for (int i = 2; i <= n; i ++)
	{
		while (qh <= qt && s[q[qh]] < s[i] - ans) qh ++;
		pos[i] = q[qh];
		q[++ qt] = i;
	}

	int *now = arr[0], *prev = arr[1];
	for (int i = 1, t = 0; (t += a[i]) <= ans && i <= n; i ++)
		prev[i] = 1;
	for (int i = 1; i <= n; i ++)
		sum[i] = (sum[i - 1] + prev[i]) % MOD;
	int register cnt = prev[n] % MOD;
	for (int j = 1; j <= m; swap(now, prev), j ++)
	{
		for (int register i = 1; i <= n; i ++)
			now[i] = (sum[i - 1] - sum[pos[i] - 1] + MOD) % MOD;
		for (int register i = 1; i <= n; i ++)
			sum[i] = (sum[i - 1] + now[i]) % MOD;
		cnt = (cnt + now[n]) % MOD;
	}
	printf("%d %d\n", ans, cnt);
	return 0;
}
