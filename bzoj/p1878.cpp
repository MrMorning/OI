#include <cstdio>

#define LOWBIT(x) ((x) & (- (x)))
const int N_MAX = 50010, M_MAX = 200010;
const int RANGE_MAX = 1000001;

int node[RANGE_MAX], next[M_MAX], begin[N_MAX], id[M_MAX], left[M_MAX], ans[M_MAX];
int pre[RANGE_MAX], a[N_MAX];
int n, m, count;

void add(int pos, int val)
{
	for(int i = pos; i < RANGE_MAX; i += LOWBIT(i))
		node[i] += val;
}

int sum(int pos)
{
	int ret = 0;
	for(int i = pos; i > 0; i -= LOWBIT(i))
		ret += node[i];
	return ret;
}

void add_query(int r, int _id, int l)
{
	count ++;
	next[count] = begin[r];
	begin[r] = count;
	id[count] = _id;
	left[count] = l;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int i = 1, l, r; i <= m; i ++)
	{
		scanf("%d%d", &l, &r);
		add_query(r, i, l);
	}
	for(int i = 1; i <= n; i ++)
	{
		add(pre[a[i]] + 1, 1);
		add(i + 1, -1);
		pre[a[i]] = i;
		for(int now = begin[i]; now; now = next[now])
			ans[id[now]] = sum(left[now]);
	}
	for(int i = 1; i <= m; i ++)
		printf("%d\n", ans[i]);
}
