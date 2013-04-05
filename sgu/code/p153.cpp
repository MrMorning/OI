#include <cstdio>
#include <cstring>

bool f[9 * (1 << 9) + 1];
int n, m, p[9], hash[1 << 9];

bool solve()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i ++)
		scanf("%d", &p[i]);
	p[m ++] = 1;
	memset(f, 0, sizeof(f));
	memset(hash, -1, sizeof(hash));
	f[0] = 1;
	for(int i = 0; i < 9 * (1 << 9); i ++)
		for(int j = 0; j < m; j ++)
			if(i + p[j] <= 9 * (1 << 9))
				f[i + p[j]] |= !f[i];
	if(n <= 9 * (1 << 9))
		return f[n];
	else
	{
		int len, st;
		for(int i = 0; i < (1 << 9); i ++)
		{
			int tmp = 0;
			for(int j = 0; j < 9; j ++)
				tmp |= (1 << j) * f[i * 9 + j];
			if(hash[tmp] == -1)
				hash[tmp] = i;
			else
			{
				st = hash[tmp];
				len = i - st;
				break;
			}
		}
		n = (n - st * 9) % (len * 9) + (st * 9);
		return f[n];
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	int _;
	scanf("%d", &_);
	while(_ --)
	{
		if(solve())
			printf("FIRST PLAYER MUST WIN\n");
		else
			printf("SECOND PLAYER MUST WIN\n");
	}
}
