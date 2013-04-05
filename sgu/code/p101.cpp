#include <cstdio>
#include <algorithm>
using namespace std;

const int N_MAX = 100;

typedef pair<int, int> info_t;
struct Edge
{
	Edge *next, *inv;
	int to;
	info_t info;
	bool marked;
} edge[2 * N_MAX], *begin[7];
int edgeCnt;
info_t stk[N_MAX];
int top;
int dgr[7];
bool vis[7];

Edge *makeEdge(int a, int b, info_t info)
{
	Edge *e = &edge[edgeCnt ++];
	e->to = b, e->next = begin[a], e->info = info;
	e->marked = false;
	return begin[a] = e;
}

void addEdge(int a, int b, int i)
{
	Edge *e1 = makeEdge(a, b, make_pair(i, 1)),
		 *e2 = makeEdge(b, a, make_pair(i, -1));
	e1->inv = e2, e2->inv = e1;
}

void dfs(int u)
{
	vis[u] = true;
	for(Edge *e = begin[u]; e; e = e->next)
		if(!e->marked)
		{
			e->marked = e->inv->marked = true;
			int v = e->to;
			dfs(v);
			stk[top ++] = e->info;
		}
}

int main()
{
	freopen("t.in", "r", stdin);
	int n, st;
	scanf("%d", &n);
	for(int i = 0, a, b; i < n; i ++)
	{
		scanf("%d%d", &a, &b);
		st = a;
		addEdge(a, b, i + 1);
		dgr[a] ++, dgr[b] ++;
	}
	int cnt = 0;
	for(int i = 0; i <= 6; i ++)
		if(dgr[i] & 1)
			st = i, cnt ++;
	if(cnt == 0 || cnt == 2)
	{
		dfs(st);
		for(int i = 0; i <= 6; i ++)
			if(dgr[i] != 0 && !vis[i])
			{
				printf("No solution\n");
				return 0;
			}
		while(top --)
			printf("%d %c\n", stk[top].first, (stk[top].second == 1 ? '+' : '-'));
	}
	else
		printf("No solution\n");
}
