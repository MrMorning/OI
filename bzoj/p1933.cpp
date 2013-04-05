#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define INF 0x3f3f3f3f
#define MAXN 2101
struct book_t
{
	int h, w;
	bool operator< (const book_t &x) const
	{
		return h > x.h;
	}
} book[71];
struct State
{
	int j, k;
	State(){};
	State(int _j, int _k): j(_j), k(_k){};
} queue[2][MAXN * MAXN];
int tail[2];
bool marked[MAXN][MAXN];
int now = 0;

int f[2][MAXN][MAXN], sum[71];

void inline update(int i, int j, int k, int val)
{
	if(! marked[j][k])
	{
		marked[j][k] = true;
	   	queue[! now][tail[! now] ++] = State(j, k);
	}
	f[i][j][k] = MIN(f[i][j][k], val);
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
	queue[now][tail[now] ++] = State(0, 0);
	for(int i = 0; i < n; i ++)
	{
		memset(f[1], 0x3f, sizeof(f[1]));
		memset(marked, 0, sizeof(marked));
		tail[! now] = 0;
		for(int t = 0; t < tail[now]; t ++)
		{
			int j = queue[now][t].j, k = queue[now][t].k;
			if(f[0][j][k] == INF)
				continue;
			int l = sum[i] - j - k;
			if(l < 0)
				continue;
			int b = MAX(j, MAX(k, l));
			int a = b == 0 ? 0 : f[0][j][k] / b;
			if(j == 0)
				update(1, book[i + 1].w, k, (a + book[i + 1].h)* MAX(b, j + book[i + 1].w));
			else
				update(1, j + book[i + 1].w, k, a * MAX(b, j + book[i + 1].w));

			if(k == 0)
				update(1, j, book[i + 1].w, (a + book[i + 1].h)* MAX(b, k + book[i + 1].w));
			else
				update(1, j, k + book[i + 1].w, a * MAX(b, k + book[i + 1].w));

			if(l == 0)
				update(1, j, k, (a + book[i + 1].h)* MAX(b, l + book[i + 1].w));
			else
				update(1, j, k, a * MAX(b, l + book[i + 1].w));
		}
		memcpy(f[0], f[1], sizeof(f[1]));
		now = ! now;
	}
	int ans = INF;
	for(int j = 0; j <= sum[n]; j ++)
		for(int k = 0; k <= sum[n]; k ++)
			if(j != 0 && k != 0 && sum[n] - j - k != 0)
				ans = MIN(ans, f[1][j][k]);
	printf("%d\n", ans);
}
