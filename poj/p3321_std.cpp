#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN = 100005;

struct Edge{
	int v, next;
};
Edge edge[MAXN * 2];
int mset, cnt;
int n, m;
int bg[MAXN];
int time[MAXN][2];
int in[2*MAXN];
int flag[MAXN];

void addEdge (int u, int v)
{
	edge[mset].v = v;
	edge[mset].next = bg[u];
	bg[u] = mset++;
}
void dfs (int u, int pre)
{
	int now, v;

	now = bg[u];
	time[u][0] = cnt++;
	while (now != -1)
	{
		v = edge[now].v;
		if (v != pre)
			dfs (v, u);
		now = edge[now].next;
	}
	time[u][1] = cnt++;
}
int Lowbit (int t)
{
	return t & (t ^ (t - 1));
}
int Sum (int end)
{
	int sum = 0;

	while (end > 0)
	{
		sum += in[end];
		end -= Lowbit (end);
	}
	return sum;
}
void Plus (int pos, int num)
{
	while (pos < cnt)
	{
		in[pos] += num;
		pos += Lowbit (pos);
	}
}
int main ()
{
	freopen("t.in", "r", stdin);
	int i, u, v, k;
	char str[4];

	scanf ("%d", &n);
	for (i = 1; i <= n; i++)
	{
		flag[i] = -1;
		bg[i] = -1;
	}
	mset = 0;
	for (i = 1; i < n; i++)
	{
		scanf ("%d%d", &u, &v);
		addEdge (u, v);
		addEdge (v, u);
	}
	cnt = 1;
	dfs (1, -1);
	for (i = 1; i < cnt; i++)
		in[i] = 0;
	for (i = 1; i <= n; i++)
		Plus (time[i][0], 1);
	scanf ("%d", &m);
	while (m--)
	{
		scanf ("%s%d", str, &k);
		if (strcmp (str, "Q") == 0)
			printf ("%d\n", Sum (time[k][1]) - Sum (time[k][0]-1));
		else
		{
			Plus (time[k][0], flag[k]);
			flag[k] = -flag[k];
		}
	}
	return 0;
}
