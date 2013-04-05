#include <cstdio>
#include <cmath>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
const int N_MAX = 100000;

int st[N_MAX][30];
int seq[N_MAX], left[N_MAX], right[N_MAX];

inline int extre_expand(int x, int l, int r)
{
	l = MAX(l, x - left[x] + 1);
	r = MIN(r, x + right[x] - 1);
	return r - l + 1;
}

void pre_work(int n_seq)
{
	for(int i = 0; i < n_seq; i ++)
		left[i] = (i != 0 && seq[i] == seq[i - 1]) ? left[i - 1] + 1 : 1;
	for(int i = n_seq - 1; i >= 0; i --)
		right[i] = (i != n_seq - 1 && seq[i] == seq[i + 1]) ? right[i + 1] + 1 : 1;
	for(int i = 0; i < n_seq; i ++)
		st[i][0] = 1;
	for(int j = 1; (1 << j) < n_seq; j ++)
		for(int i = 0; i < n_seq; i ++)
		{
			int tmp = i + (1 << (j - 1));
			if(tmp >= n_seq)
			{
				st[i][j] = st[i][j - 1];
				continue;
			}
			st[i][j] = MAX(st[i][j - 1], st[tmp][j - 1]);
			st[i][j] = MAX(st[i][j], extre_expand(tmp, i, i + (1 << j) - 1));
		}
}
void solve(int n_seq)
{
	int n_query;
	scanf("%d", &n_query);
	for(int i = 0; i < n_seq; i ++)
		scanf("%d", &seq[i]);
	pre_work(n_seq);
	while(n_query --)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		a --, b --;
		int len = (int)(log(b - a + 1) / log(2));
		int cnt = MAX(st[a][len], st[b - (1 << len) + 1][len]);
		int tmp = a + (1 << len) - 1;
		cnt = MAX(cnt, extre_expand(tmp, a, b));
		tmp = b - (1 << len) + 1;
		cnt = MAX(cnt, extre_expand(tmp, a, b));
		printf("%d\n", cnt);
	}
}
int main()
{
	freopen("t.in", "r", stdin);
	//freopen("t.out", "w", stdout);
	while(1)
	{
		int n;
		scanf("%d", &n);
		if(n == 0)
			break;
		solve(n);
	}
}
