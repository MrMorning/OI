#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N_MAX = 100010;
int val[N_MAX], tmp[N_MAX];
int n, m;
int main()
{
	freopen("t.in", "r", stdin);
//	freopen("t.out", "w", stdout);
	scanf("%d%d", &n, &m);
	static char str[N_MAX];
	scanf("%s", str);
	for(int i = 0; i < n; i ++)
		val[i] = str[i] == '(' ? 1 : -1;
	for(int i = 0; i < m; i ++)
	{
		int cmd, a, b;
		scanf("%d%d%d", &cmd, &a, &b);
		a --, b --;
		if(cmd == 0)
		{
			int lmin = 0;
			int cnt = 0;
			for(int j = a; j <= b; j ++)
			{
				cnt = cnt + val[j];
				lmin = min(lmin, cnt);
			}
			cnt = 0;
			int rmax = 0;
			for(int j = b; j >= a; j --)
			{
				cnt = cnt + val[j];
				rmax = max(rmax, cnt);
			}
			lmin *= -1;
			lmin = lmin == 0 ? 0 : (lmin - 1) / 2 + 1;
			rmax = rmax == 0 ? 0 : (rmax - 1) / 2 + 1;
			printf("%d\n", lmin + rmax);
		}
		else if(cmd == 1)
			for(int j = a; j <= b; j ++)
				val[j] *= -1;
		else
		{
			int len = b - a + 1;
			memcpy(tmp, val + a, sizeof(int) * len);
			for(int j = 0; j < len; j ++)
				val[a + j] = tmp[len - j - 1];
		}
	}
}
