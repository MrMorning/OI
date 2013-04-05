#include <cstdio>
#include <cstring>
#define MAXN 21000

int testNum, n, a[MAXN], w[MAXN], f[MAXN * 6];

int main()
{
	freopen("t.in", "r", stdin);
	freopen("test2", "w", stdout);
	while(1)
	{
		int sum = 0;
		for(int i = 1; i <= 6; i ++)
			scanf("%d", &a[i]), sum += a[i] * i;
		if(sum == 0)
			break;
		printf("Collection #%d:\n", ++ testNum);
		if((sum & 1) == 1)
			printf("Can't be divided.\n\n");
		else
		{
			n = 0;
			for(int i = 1; i <= 6; i ++)
			{
				int j = 1;
				while(a[i] - j > 0)
					w[++ n] = i * j, a[i] -= j, j <<= 1; 
				w[++ n] = a[i] * i;
			}
			int half = sum >> 1;
			memset(f, 0, sizeof(f));
			f[0] = 1;
			for(int i = 1; i <= n; i ++)
				for(int j = half; j >= w[i]; j --)
					f[j] |= f[j - w[i]];
			if(f[half])
				printf("Can be divided.\n");
			else
				printf("Can't be divided.\n");
			printf("\n");
		}
	}
}
