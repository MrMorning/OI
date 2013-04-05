#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 50000;
struct Stuff
{
	int key, fix, idx;
	bool operator< (const Stuff &t) const
	{
		return key < t.key;
	}
} a[N_MAX];

struct State
{
	int l, r;
	State(int _l = 0, int _r = 0):
		l(_l), r(_r){}
} queue[N_MAX];

int n;
int st[N_MAX][20], log2[N_MAX + 1];
int pre[N_MAX], lch[N_MAX], rch[N_MAX];
int ans[N_MAX][3];

void initST()
{
	for(int i = 0; (1 << i) <= n; i ++)
		log2[1 << i] = i;
	for(int i = 2; i <= n; i ++)
		if(log2[i] == 0)
			log2[i] = log2[i - 1];

	for(int i = 0; i < n; i ++)
		st[i][0] = i;
	for(int j = 1; (1 << j) <= n; j ++)
		for(int i = 0; i < n; i ++)
		{
			st[i][j] = st[i][j - 1];
			if(i + (1 << (j - 1)) >= n)
				continue;
			int tmp = st[i + (1 << (j - 1))][j - 1];
			if(a[tmp].fix < a[st[i][j]].fix)
				st[i][j] = tmp;
		} 
}

int getMin(int l, int r)
{
	if(l > r)
		return -1;
	int len = r - l + 1,
		k = log2[len];
	int res = st[l][k];
	int tmp = st[r - (1 << k) + 1][k];
	if(a[tmp].fix < a[res].fix)
		res = tmp;
	return res;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
	{
		scanf("%d%d", &a[i].key, &a[i].fix);
		a[i].idx = i;
	}
	sort(a, a + n);
	initST();

	int qh = 0, qt = 0;
	queue[qt ++] = State(0, n - 1);
	memset(pre, -1, sizeof(pre));
	memset(lch, -1, sizeof(lch));
	memset(rch, -1, sizeof(rch));
	while(qh < qt)
	{
		State u = queue[qh ++];
		if(u.l >= u.r)
			continue;
		int r = getMin(u.l, u.r),
			p = getMin(u.l, r - 1),
			q = getMin(r + 1, u.r);
		if(p != -1)
			pre[p] = r, lch[r] = p, queue[qt ++] = State(u.l, r - 1);
		if(q != -1)
			pre[q] = r, rch[r] = q, queue[qt ++] = State(r + 1, u.r);
	}
	for(int i = 0; i < n; i ++)
	{
		ans[a[i].idx][0] = pre[i] == -1 ? 0 : a[pre[i]].idx + 1;
		ans[a[i].idx][1] = lch[i] == -1 ? 0 : a[lch[i]].idx + 1;
		ans[a[i].idx][2] = rch[i] == -1 ? 0 : a[rch[i]].idx + 1;
	}
	printf("YES\n");
	for(int i = 0; i < n; i ++)
		printf("%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
}
