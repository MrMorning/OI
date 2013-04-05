#include <cstdio>
#include <cstring>
#include <string>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MAXN 100001
using std::string;
using std::pair;
typedef double Val_t;
typedef pair<Val_t, Val_t> data_t;
const Val_t INFINITY = 10E100;
Val_t f[MAXN], A[MAXN], B[MAXN], rate[MAXN];
int n;

struct node_t
{
	Val_t k[2];
	data_t data;
	node_t *ch[2], *pre;
};

node_t node[MAXN], *null, *root;
int nodeIdx, top;
node_t *nodeAlloc(Val_t key, Val_t val);
void rotate(node_t *u, bool c);
void splay(node_t *u, node_t *p);
void insert(node_t *u);

Val_t readReal()
{
	double res = 0, t = 1;
	char ch;
	for (ch = getchar(); '0' <= ch && ch <= '9'; ch = getchar())
		res = res * 10 + int(ch) - 48;
	for (ch = getchar(); '0' <= ch && ch <= '9'; ch = getchar())
		t /= 10, res += t * (int(ch) - 48);
	return res;
}

void init()
{
	top = nodeIdx = 0;
	root = null = nodeAlloc(0, 0);
}

node_t *nodeAlloc(Val_t key, Val_t val)
{
	node_t *u = &node[nodeIdx ++];
	u->data = std::make_pair(key, val);
	u->pre = u->ch[0] = u->ch[1] = null;
	return u;
}

void rotate(node_t *u, bool c)
{
	node_t *p = u->pre;
	u->pre = p->pre; 
	if(p->pre != null)
		p->pre->ch[p == p->pre->ch[1]] = u;
	p->ch[! c] = u->ch[c];
	if(u->ch[c] != null)
		u->ch[c]->pre = p;
	p->pre = u, u->ch[c] = p;
	if(p == root) root = u;
}

void splay(node_t *u, node_t *p)
{
	while(u->pre != p)
	{
		if(u->pre->pre == p)
			rotate(u, u == u->pre->ch[0]);
		else
		{
			node_t *v = u->pre, *w = v->pre;
			if(v == w->ch[0])
			{
				if(u == v->ch[0])
					rotate(v, 1), rotate(u, 1);
				else
					rotate(u, 0), rotate(u, 1);
			}
			else
			{
				if(u == v->ch[1])
					rotate(v, 0), rotate(u, 0);
				else
					rotate(u, 1), rotate(u, 0);
			}
		}
	}

}

Val_t calcK(data_t p1, data_t p2)
{return p1.first == p2.first ? -INFINITY : (p1.second - p2.second) / (p1.first - p2.first);}

node_t *getNeighbor(node_t *u, int c)
{
	if(u->ch[c] == null) return null;
	for(u = u->ch[c]; u->ch[! c] != null; u = u->ch[! c]);
	return u;
}

node_t *getMax(Val_t k)
{
	for(node_t *u = root; ; u = u->ch[k < u->k[1]])
		if(u->k[0] >= k && k >= u->k[1]) return u;
}

void check(node_t *u, int c)
{
	for(node_t *v = getNeighbor(u, c); ; v = getNeighbor(u, c))
	{
		if(v == null) break;
		splay(v, u);
		if((v->k[c] <= calcK(v->data, u->data)) ^ c)
		{
			u->ch[c] = v->ch[c];
			if(v->ch[c] != null) v->ch[c]->pre = u;
		}
		else
			break;
	}
}

void fix(node_t *u)
{
	node_t *pred, *succ;
	splay(u, null), pred = getNeighbor(u, 0), succ = getNeighbor(u, 1);
	u->k[0] = (pred == null) ? 0 : calcK(u->data, pred->data);
	u->k[1] = (succ == null) ? -INFINITY : calcK(u->data, succ->data);
	if(u->k[0] <= u->k[1])
	{
		if(pred == null)
			splay(succ, u), root = succ, succ->pre = null;
		else
		{
			splay(pred, u), root = pred, pred->pre = null, pred->ch[1] = u->ch[1];
			if(u->ch[1] != null) u->ch[1]->pre = pred;
		}
	}
	else
	{
		check(u, 0), check(u, 1);
		pred = getNeighbor(u, 0), succ = getNeighbor(u, 1);
		u->k[0] = (pred == null) ? 0 : pred->k[1] = calcK(pred->data, u->data);
		u->k[1] = (succ == null) ? -INFINITY : succ->k[0] = calcK(succ->data, u->data);
	}
}

void insert(node_t *newNode)
{
	node_t *u = root, *p = null;
	for(; u != null; u = u->ch[newNode->data > u->data])
		if(u->data == newNode->data) return;
		else p = u;
	if(p == null)
		root = newNode;
	else
		p->ch[newNode->data > p->data] = newNode, newNode->pre = p;
	fix(newNode);
}

int main()
{
	Val_t tmp;
	int n;

	freopen("t.in", "r", stdin);
	init();
	scanf("%d%lf", &n, &tmp);
	for(int i = 1; i <= n; i ++)
		scanf("%lf%lf%lf", &A[i], &B[i], &rate[i]);
	f[1] = tmp;
	tmp = f[1] / (rate[1] * A[1] + B[1]);
	insert(nodeAlloc(tmp * rate[1], tmp));
	for(int i = 2; i <= n; i ++)
	{
		f[i] = f[i - 1];
		node_t *u = getMax(- A[i] / B[i]);
		tmp = A[i] * u->data.first + B[i] * u->data.second;
		f[i] = MAX(f[i], tmp);
		tmp = f[i] / (rate[i] * A[i] + B[i]);
		insert(nodeAlloc(tmp * rate[i], tmp));
	}
	printf("%.3lf\n", f[n]);
}
