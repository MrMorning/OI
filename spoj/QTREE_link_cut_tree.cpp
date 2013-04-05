#include <cstdio>
#include <algorithm>
using namespace std;
const int V_MAX = 10010;
const int oo = 0x3f3f3f3f;
struct Edge
{
	int to, weight, down;
	Edge *next;
} edge[2 * V_MAX], *begin[V_MAX];
int edgeCnt;

struct Node
{
	Node *ch[2], *fa;
	int myVal, maxVal;
	void update()
	{
		maxVal = myVal;
		for(int t = 0; t < 2; t ++)
			if(ch[t])
				maxVal = max(maxVal, ch[t]->maxVal);
	}
} nodePool[V_MAX];

void addEdge(int u, int v, int w)
{
	Edge *e = edge + (edgeCnt ++);
	e->to = v, e->next = begin[u], e->weight = w;
	begin[u] = e;
}

void rotate(Node *x, int c)
{
	Node *y = x->fa;
	if((y->ch[!c] = x->ch[c]) != NULL)
		y->ch[!c]->fa = y;
	if((x->fa = y->fa) != NULL && (y == y->fa->ch[y == y->fa->ch[1]]))
		y->fa->ch[y == y->fa->ch[1]] = x;
	x->ch[c] = y, y->fa = x;
	y->update();
}

void splay(Node *x)
{
	while(x->fa && (x == x->fa->ch[0] || x == x->fa->ch[1]))
	{
		Node *y = x->fa, *z = y->fa;
		if(z == NULL || (y != z->ch[y == z->ch[1]]))
			rotate(x, x == y->ch[0]);
		else
		{
			if(y == z->ch[0])
			{
				if(x == y->ch[0])
					rotate(y, 1), rotate(x, 1);
				else
					rotate(x, 0), rotate(x, 1);
			}
			else
			{
				if(x == y->ch[1])
					rotate(y, 0), rotate(x, 0);
				else
					rotate(x, 1), rotate(x, 0);
			}
		}
	}
	x->update();
}

Node *expose(Node *x)
{
	Node *y = NULL;
	for(; x; x = x->fa)
	{
		splay(x);
		x->ch[1] = y;
		(y = x)->update();
	}
	return y;
}

int ask(int u, int v)
{
	Node *x = nodePool + u, *y = nodePool + v;
	expose(x);
	Node *p = expose(y);
	int res = -oo;
	if(p->ch[1])
		res = p->ch[1]->maxVal;
	if(x != p)
	{
		splay(x);
		res = max(res, x->maxVal);
	}
	return res;
}

void change(int u, int val)
{
	Node *x = nodePool + u;
	splay(x);
	x->myVal = val;
	x->update();
	//expose(x);
}

void bfs()
{
	static int Q[V_MAX];
	int qt = 0;
	Q[qt ++] = 0;
	for(int qh = 0; qh < qt; qh ++)
	{
		int u = Q[qh];
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->to;
			if(v == 0 || nodePool[v].fa)
				continue;
			nodePool[v].fa = nodePool + u;
			nodePool[v].myVal = e->weight;
			Q[qt ++] = v;
			e->down = (edge + ((e - edge) ^ 1))->down = v;
		}
	}
}

void solve()
{
	int nodeNum = 0;
	scanf("%d", &nodeNum);
	edgeCnt = 0;
	for(int i = 0; i < nodeNum; i ++)
	{
		begin[i] = NULL;
		Node *x = nodePool + i;
		x->ch[0] = x->ch[1] = x->fa = NULL;
		x->myVal = -oo;
	}
	for(int i = 0; i < nodeNum - 1; i ++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	bfs();
	for(int i = 0; i < nodeNum; i ++)
		(nodePool + i)->update();
	while(1)
	{
		static char input[10];
		scanf("%s", input);
		if(input[0] == 'D')
			break;
		if(input[0] == 'C')
		{
			int t, c;
			scanf("%d%d", &t, &c);
			t --;
			change((edge + t + t)->down, c);
		}
		else
		{
			int u, v;
			scanf("%d%d", &u, &v);
			u --, v --;
			printf("%d\n", ask(u, v));
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	int testNum;
	scanf("%d", &testNum);
	while(testNum --)
		solve();
}
