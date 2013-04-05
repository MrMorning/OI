#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

const int SPOT_NUM_MAX = 100000;
const int ROAD_NUM_MAX = 300000;
const int INF = 0x3f3f3f3f;

int pre[SPOT_NUM_MAX];
int weight[SPOT_NUM_MAX];
int hvst[SPOT_NUM_MAX];
int depth[SPOT_NUM_MAX];
int jump[SPOT_NUM_MAX];
int size[SPOT_NUM_MAX];

int roadNum, spotNum;

struct DisjointSet
{
	int parent[SPOT_NUM_MAX], rank[SPOT_NUM_MAX];
	void init(int n)
	{
		for(int i = 0; i < n; i ++)
			parent[i] = i;
	}
	int find(int x)
	{
		return x == parent[x] ? x : parent[x] = find(parent[x]);
	}
	void merge(int x, int y)
	{
		int p = find(x), q = find(y);
		assert(p != q);
		if(rank[p] < rank[q])
			swap(p, q);
		parent[q] = p;
		rank[p] ++;
	}
};

struct Edge
{
	int to, weight;
	Edge *next;
} *begin[SPOT_NUM_MAX];


struct Road
{
	int u, v, weight;
	bool operator< (const Road &r) const
	{
		return weight < r.weight;
	}
} road[ROAD_NUM_MAX];

namespace sgt
{
	struct Node
	{
		int l, r, val;
		Node *ch[2];
	} node_pool[SPOT_NUM_MAX * 4];

	Node *build(int l, int r, int buf[], int offset)
	{
		static int freePos = 0;
		Node *x = &node_pool[freePos ++];
		x->l = l, x->r = r;
		if(l == r)
		{
			x->val = weight[buf[l - offset]];
			x->ch[0] = x->ch[1] = NULL;
		}
		else
		{
			int mid = (l + r) / 2;
			x->ch[0] = build(l, mid, buf, offset);
			x->ch[1] = build(mid + 1, r, buf, offset);
			assert(x->ch[0] != NULL && x->ch[1] != NULL);
			x->val = max(x->ch[0]->val, x->ch[1]->val);
		}
		return x;
	}

	int ask(Node *x, int l, int r)
	{
		//assert(x != NULL);
		if(x == NULL)
			assert(0);
		if(l > x->r || r < x->l)
			return -INF;
		if(l <= x->l && x->r <= r)
			return x->val;
		return max(ask(x->ch[0], l, r), ask(x->ch[1], l, r));
	}
}

sgt::Node *root[SPOT_NUM_MAX];

void addEdge(int u, int v, int w)
{
	static Edge edge[2 * SPOT_NUM_MAX];
	static int freePos = 0;
	Edge *e = &edge[freePos ++];
	e->to = v, e->next = begin[u], e->weight = w;
	begin[u] = e;
}

int seq[SPOT_NUM_MAX];
int seqCnt;

void bfs()
{
	static int queue[SPOT_NUM_MAX];
	int qh = 0, qt = 0;
	queue[qt ++] = 0;
	pre[0] = -1;
	depth[0] = 0;
	weight[0] = -INF;
	while(qh < qt)
	{
		int u = queue[qh ++];
		seq[seqCnt ++] = u;
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->to;
			if(v == pre[u])
				continue;
			pre[v] = u;
			depth[v] = depth[u] + 1;
			weight[v] = e->weight;
			queue[qt ++] = v;
		}
	}
}

void initReversely()
{
	assert(seqCnt == spotNum);
	memset(hvst, -1, sizeof(int) * spotNum);
	for(int i = seqCnt - 1; i >= 0; i --)
	{
		int u = seq[i];
		size[u] ++;
		if(pre[u] != -1)
		{
			size[pre[u]] += size[u];
			if(hvst[pre[u]] == -1 || size[hvst[pre[u]]] < size[u])
				hvst[pre[u]] = u;
		}
	}
}

void chainSplit()
{
	static int buf[SPOT_NUM_MAX];
	memset(jump, -1, sizeof(int) * spotNum);
	for(int i = seqCnt - 1; i >= 0; i --)
	{
		int u = seq[i];
		if(root[u] != NULL)
			continue;
		int p = pre[u];
		int bufCnt = 0;
		buf[bufCnt ++] = u;
		while(p != -1 && hvst[p] == u)
			u = p, p = pre[p], buf[bufCnt ++] = u;
		sgt::Node *x = sgt::build(depth[buf[bufCnt - 1]], depth[buf[0]], buf, depth[buf[bufCnt - 1]]);
		for(int i = 0; i < bufCnt; i ++)
			root[buf[i]] = x, jump[buf[i]] = pre[u];
	}
}

int lca(int u, int v)
{
	while(u != v)
	{
		if(depth[u] < depth[v])
			v = pre[v];
		else
			u = pre[u];
	}
	assert(u != -1);
	return u;
}

int letItJump(int u, int p)
{
	int result = -INF;
	while(u != p)
		result = max(result, weight[u]), u = pre[u];
	return result;
}

int ask(int u, int v)
{
	int p = lca(u, v);
	return max(letItJump(u, p), letItJump(v, p));
}

DisjointSet DS;
void buildTree()
{

	scanf("%d%d", &spotNum, &roadNum);
	for(int i = 0, x, y, w; i < roadNum; i ++)
	{
		scanf("%d%d%d", &x, &y, &w);
		x --, y --;
		road[i].u = x, road[i].v = y, road[i].weight = w;
	}
	sort(road, road + roadNum);
	DS.init(spotNum);
	for(int i = 0; i < roadNum; i ++)
	{
		int x = road[i].u, y = road[i].v;
		if(DS.find(x) != DS.find(y))
		{
			DS.merge(x, y);
			//fprintf(stderr, "%d\n", i);
			addEdge(road[i].u, road[i].v, road[i].weight);
			addEdge(road[i].v, road[i].u, road[i].weight);
		}
	}
	bfs();
	initReversely();
	chainSplit();
}

int main()
{
	freopen("t.in", "r", stdin);
	buildTree();
	int cmdNum;
	scanf("%d", &cmdNum);
	for(int i = 0, s = 1, p1, p2, q1, q2; i < cmdNum; i ++)
	{
		scanf("%d%d%d%d", &p1, &p2, &q1, &q2);
		int x = (ll)(s + p1) * p2 % spotNum,
			y = (ll)(s + q1) * q2 % spotNum;
		s = ask(x, y);
		if(s == -INF)
			s = 0;
		//fprintf(stderr, "%d %d\n", x, y);
		printf("%d\n", s);
	}
}
