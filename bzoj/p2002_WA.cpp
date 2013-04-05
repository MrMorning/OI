#include <cstdio>
#include <cstring>
const int BLOCK_SIZE = 500;
const int N_MAX = 200010;
int n, n_blk;
int jump[N_MAX], setting[N_MAX];
int belong[N_MAX], f[N_MAX];
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d", &n);
	memset(jump, -1, sizeof(jump));
	for(int i = 0; i < n; i ++)
	{
		scanf("%d", &setting[i]);
		jump[i] = setting[i] + i;
		f[i] = 1;
	}
	int n_blk = n / BLOCK_SIZE + 1;
	for(int i = 0; i < n_blk; i ++)
		for(int j = i * BLOCK_SIZE; j < i * (BLOCK_SIZE + 1); j ++)
			belong[j] = i;
	for(int i = n - 1; i >= 0; i --)
	{
		if(jump[i] < n && belong[i] == belong[jump[i]])
		{
			f[i] = f[jump[i]] + 1;
			jump[i] = jump[jump[i]];
		}
	}
	int m;
	scanf("%d", &m);
	while(m --)
	{
		int i, j;
		scanf("%d%d", &i, &j);
		if(i == 1)
		{
			int u = j;
			int cnt = 0;
			while(1)
			{
				cnt += f[u];
				u = jump[u];
				if(u >= n)
					break;
			}
			printf("%d\n", cnt);
		}
		else
		{
			int k;
			scanf("%d", &k);
			setting[j] = k;
			jump[j] = j + k;
			f[j] = 1;
			if(k < n && k < BLOCK_SIZE * (belong[j] + 1))
			{
				f[j] = f[jump[j]] + 1;
				jump[j] = jump[jump[j]];
			}
			for(int k = j - 1; k >= BLOCK_SIZE * belong[j]; k --)
				if(setting[k] == j)
				{
					f[k] = f[j] + 1;
					jump[k] = jump[j];
				}
		}
	}
}
