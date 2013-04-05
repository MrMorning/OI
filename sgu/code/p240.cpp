#include <cstdio>
#include <cstring>
const int V_MAX = 100;
const int E_MAX = V_MAX * V_MAX * 2;
const int oo = 0x3f3f3f3f;
struct Edge
{
	int to, time, speed, initTemp;
	Edge *next;
} edge[E_MAX], *begin[V_MAX];
int dist[V_MAX];
bool terminal[V_MAX];
int term, nv, sv, ne, tvNum, Hmax;
int prev[V_MAX];
int out[V_MAX + 1], top;

void addEdge(int a, int b, int t, int r, int p)
{
	static int tot = 0;
	Edge *e = edge + (tot ++);
	e->to = b, e->next = begin[a], e->time = t, e->speed = p, e->initTemp = r;
	begin[a] = e;
}

bool check(int H)
{
	static int Q[V_MAX];
	static bool inQ[V_MAX];
	memset(dist, 0x3f, sizeof(dist));
	dist[sv] = 0;
	int qh = 0, qt = 0;
	Q[qt ++] = sv;
	inQ[sv] = true;
	while(qh != qt)
	{
		int u = Q[qh];
		qh = (qh + 1) % nv;
		inQ[u] = false;
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->to;
			int curTemp = e->speed * (e->time + dist[u]) + e->initTemp;
			if(curTemp > H)
				continue;
			if(e->time + dist[u] < dist[v])
			{
				dist[v] = e->time + dist[u];
				prev[v] = u;
				if(!inQ[v])
				{
					inQ[v] = true;
					Q[qt] = v;
					qt = (qt + 1) % nv;
				}
			}
		}
	}
	for(int i = 0; i < nv; i ++)
		if(terminal[i] && dist[i] != oo)
		{
			term = i;
			return true;
		}
	return false;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d%d", &nv, &ne, &Hmax, &sv, &tvNum);
	sv --;
	while(ne --)
	{
		int a, b, c, d, e;
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
		a --, b --;
		addEdge(a, b, c, d, e);
		addEdge(b, a, c, d, e);
	}
	while(tvNum --)
	{
		int u;
		scanf("%d", &u);
		u --;
		terminal[u] = true;
	}
	int lb = -1, rb = Hmax;
	for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1)
		if(check(mid))
			rb = mid;
		else
			lb = mid;
	if(!check(rb))
	{
		printf("NO\n");
		return 0;
	}
	else
		printf("YES\n");
	int u = term;
	while(1)
	{
		out[top ++] = u;
		if(u == sv)
			break;
		u = prev[u];
	}
	printf("%d\n%d", rb, top);
	while(top)
		printf(" %d", out[--top] + 1);
}
