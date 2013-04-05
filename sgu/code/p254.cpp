#include <cstdio>

int a[2000001];
int n, q;

inline void adjust(int &p)
{
	if(p == 0)
		p = n;
	if(p == n + 1)
		p = 1;
}

inline int next(int p, int dir)
{
	p = p + dir;
	adjust(p);
	while(a[p] == 0)
		p = p + dir, adjust(p);
	return p;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i ++)
		a[i] = i;
	int p = 1, dir = 1;
	int tmp = n;
	for(int i = 0; i < tmp - 1; i ++)
	{
		for(int t = 0; t < q - 1; t ++)
			p = next(p, dir);
		a[p] = 0;
		p = next(p, 1);
		if(a[p] & 1)
			dir = 1;
		else
			dir = -1;
		if(i % 200000 == 0)
		{
			int m = 0;
			for(int k = 1; k <= n; k ++)
				if(a[k] != 0)
				{
					a[++ m] = a[k];
					if(k == p)
						p = m;
				}
			n = m;
		}
	}
	for(int i = 1; i <= n; i ++)
		if(a[i] != 0)
		{
			printf("%d\n", a[i]);
			break;
		}
}
