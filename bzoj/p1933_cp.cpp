#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define INF 0x3f3f3f3f
struct book_t
{
	int h, w;
	bool operator< (const book_t &x) const
	{
		return h > x.h;
	}
} book[71];

int f[2][2101][2101], sum[71];

void inline update(int &a, int b)
{
	a = MIN(a,b);
}

int main()
{
	int n;
	freopen("t.in", "r", stdin);
	scanf("%d\n", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d%d", &book[i].h, &book[i].w);
	std::sort(book + 1, book + n + 1);
	for(int i = 1; i <= n; i ++)
		sum[i] = sum[i - 1] + book[i].w;
	memset(f, 0x3f, sizeof(f));
	f[0][0][0] = 0;
	for(int i = 0; i < n; i ++)
	{
		memset(f[1], 0x3f, sizeof(f[1]));
		for(int j = 0; j <= sum[n]; j ++)
			for(int k = 0; k <= sum[n]; k ++)
			{
				if(f[0][j][k] == INF)
					continue;
				int l = sum[i] - j - k;
				if(l < 0)
					continue;
				int b = MAX(j, MAX(k, l));
				int a = b == 0 ? 0 : f[0][j][k] / b;
				if(j == 0)
					update(f[1][book[i + 1].w][k], (a + book[i + 1].h)* MAX(b, j + book[i + 1].w));
				else
					update(f[1][j + book[i + 1].w][k], a * MAX(b, j + book[i + 1].w));

				if(k == 0)
					update(f[1][j][book[i + 1].w], (a + book[i + 1].h)* MAX(b, k + book[i + 1].w));
				else
					update(f[1][j][k + book[i + 1].w], a * MAX(b, k + book[i + 1].w));

				if(l == 0)
					update(f[1][j][k], (a + book[i + 1].h)* MAX(b, l + book[i + 1].w));
				else
					update(f[1][j][k], a * MAX(b, l + book[i + 1].w));
			}
		memcpy(f[0], f[1], sizeof(f[1]));
	}
	int ans = INF;
	for(int j = 0; j <= sum[n]; j ++)
		for(int k = 0; k <= sum[n]; k ++)
			if(j != 0 && k != 0 && sum[n] - j - k != 0)
				ans = MIN(ans, f[1][j][k]);
	printf("%d\n", ans);
}
