#include <cstdio>
#include <cstring>
int p[9], f[1000000];
void solve()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i ++)
		scanf("%d", &p[i]);
	memset(f, 0, sizeof(f));
	f[0] = 1;
	for(int i = 0; i < n; i ++)
	{
		f[i + 1] |= !f[i];
		for(int j = 0; j < m; j ++)
			if(i + p[j] <= n)
				f[i + p[j]] |= !f[i];
	}
	if(f[n])
		printf("FIRST PLAYER MUST WIN\n");
	else
		printf("SECOND PLAYER MUST WIN\n");
}

int main()
{
	freopen("t.in", "r", stdin);
	int _;
	scanf("%d", &_);
	while(_ --)
		solve();
}
