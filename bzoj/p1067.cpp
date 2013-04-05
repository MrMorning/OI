#include <cstdio>
#include <cstring>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

const int N_MAX = 50010;
const int INFINITY = 0x3f3f3f3f;

struct Node
{
	int l, r, val;
} node[N_MAX * 4];

int data[N_MAX][2];
int n;

bool bin_search(const Interval &itv)
{
	int l = 1, r = n_interv + 1, mid = (l + r) / 2;
	while(l < r - 1)
	{
		if(itv.r < interv[mid].l)
			r = mid;
		else if(itv.l > interv[mid].r)
			l = mid + 1;
		else
			break;
		mid = (l + r) / 2;
	}
	if(interv[mid].contain(itv))
		return true;
	else
		return false;
}

void build(int i, int l, int r)
{
	node[i].l = l, node[i].r = r;
	if(l == r)
	{
		node[i].val = data[l][1];
		return;
	}
	build(i * 2, l, (l + r) / 2);
	build(i * 2 + 1, (l + r) / 2 + 1, r);
	node[i].val = MAX(node[i * 2].val, node[i * 2 + 1].val);
}
int ask(int i, int l, int r)
{
	if(node[i].l > r || node[i].r < l)
		return - INFINITY;
	if(l <= node[i].l && node[i].r <= r)
		return node[i].val;
	int ret1 = ask(i * 2, l, r),
		ret2 = ask(i * 2 + 1, l, r);
	return MAX(ret1, ret2);
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d%d", &data[i][0], &data[i][1]);
	build(1, 1, n);
	scanf("%d", &m);
	while(m --)
	{
		int st, en;
		scanf("%d%d", &st, &en);
		int L = bin_search(st),
			R = bin_search(en);
		bool flag1 = st == data[L][0],
			 flag2 = en == data[R][0];
	}
}
