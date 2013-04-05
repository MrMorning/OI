#include <cstdio>
#include <cstring>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
namespace Solve
{
	const int MAXN = 50000,
		  INFINITY = 2147483647;
	struct Stuff
	{
		int a, b;
	};
	struct State
	{
		int key;
		int val;
		State(){};
		State(int _key, int _val): key(_key), val(_val){};
	};
	void init();
	void calcBound(int limit);
	void dp();
	void solve();

	int n, limit;
	int b[MAXN], f[MAXN];
	State queue[MAXN];
	Stuff stuff[MAXN];
	bool linked[MAXN];
	int maxSa[MAXN];
}


void Solve::init()
{
	memset(linked, 0, sizeof(bool) * (n + 1));
	memset(maxSa, 0, sizeof(int) * (n + 1));
	scanf("%d%d", &n, &limit);
	for(int i = 1; i <= n; i ++)
		scanf("%d%d", &stuff[i].a, &stuff[i].b);
	maxSa[n] = stuff[n].a;
	for(int i = n - 1; i >= 1; i --)
		maxSa[i] = MAX(stuff[i].a, maxSa[i + 1]);
	int minSb = INFINITY;
	for(int i = 1; i < n; i ++)
	{
		minSb = MIN(minSb, stuff[i].b);
		if(minSb <= maxSa[i + 1])
			linked[i] = true;
	}
	int newN = 0;
	for(int i = 1; i <= n; i ++)
	{
		newN ++;
		stuff[newN].a = stuff[i].a, stuff[newN].b = stuff[i].b;
		while(i < n && linked[i])
		{
			i ++;
			stuff[newN].a = MAX(stuff[newN].a, stuff[i].a);
			stuff[newN].b +=  stuff[i].b;
		}
	}
	n = newN;
}

void Solve::calcBound(int maxSb)
{
	int cnt = 0, i = 0;
	for(int j = 1; j <= n; j ++)
	{
		cnt += stuff[j].b;
		while(cnt > maxSb && i < j)
			cnt -= stuff[++ i].b;
		b[j] = i;
	}
}

void Solve::dp()
{
	int qh = 0, qt = 0;
	memset(f, 0x3f, sizeof(int) * (n + 1));
	f[0] = 0;
	for(int i = 1; i <= n; i ++)
	{
		while(qh < qt && queue[qh].key <= b[i])
			qh ++;
		while(qh < qt && queue[qt - 1].val <= stuff[i].a)
			qt --;
		queue[qt ++] = State(i, stuff[i].a);
		f[i] = MIN(f[i], f[b[i]] + queue[qh].val);
		for(int k = qh; k < qt - 1; k ++)
				f[i] = MIN(f[i], f[queue[k].key] + queue[k + 1].val);
	}
}

void Solve::solve()
{
	init();
	int l = 0, r = INFINITY, mid = (l + r) / 2;
	while(l < r)
	{
		calcBound(mid);
		dp();
		if(f[n] <= limit)
			r = mid;
		else
			l = mid + 1;
		mid = (l + r) / 2;
	}
	printf("%d\n", mid);
}

int main()
{
#ifndef STDIO
	freopen("t.in", "r", stdin);
#endif
	Solve::solve();
}
