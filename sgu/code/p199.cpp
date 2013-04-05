#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N_MAX = 100010;
int f[N_MAX], g[N_MAX];

struct People
{
	int s, b, pos;
	bool operator< (const People &p) const
	{
		return b < p.b || (b == p.b && s < p.s);
	}
	bool operator== (const People &p) const
	{
		return s == p.s && b == p.b;
	}
} people[N_MAX];
int peopleNum;

struct Node
{
	Node *ch[2];
	int key, idx, fix;
	int maxIdx;
} nodePool[N_MAX], *null, *root;

inline int idxMax(int i, int j)
{
	if(i == null->idx)
		return j;
	else if(j == null->idx)
		return i;
	int res = i;
	if(f[j] > f[i])
		res = j;
	return res;
}

inline Node *alloc(int idx)
{
	static int nodeCnt = 0;
	Node *x = &nodePool[nodeCnt ++];
	x->ch[0] = x->ch[1] = null;
	x->key = people[idx].s;
	x->fix = rand() * rand();
	x->idx = x->maxIdx = idx;
	return x;
}

inline void update(Node *x)
{
	x->maxIdx = idxMax(x->idx, idxMax(x->ch[0]->maxIdx, x->ch[1]->maxIdx));
}

inline void rotate(Node *&x, int c)
{
	Node *y = x->ch[!c];
	x->ch[!c] = y->ch[c];
	y->ch[c] = x;
	update(x); update(y);
	x = y;
}

void insert(Node *&now, Node *x)
{
	if(now == null)
		now = x;
	else
	{
		int t = x->key > now->key;
		insert(now->ch[t], x);
		if(now->ch[t]->fix < now->fix)
			rotate(now, !t);
		else
			update(now);
	}
}

int find(Node *now, int upperlim)
{
	if(now == null)
		return null->idx;
	if(now->key < upperlim)
		return idxMax(now->ch[0]->maxIdx, idxMax(now->idx, find(now->ch[1], upperlim)));
	else
		return find(now->ch[0], upperlim);
}

int main()
{
	freopen("t.in", "r", stdin);
	null = alloc(0);
	null->idx = null->maxIdx = -1;
	root = null;

	scanf("%d", &peopleNum);
	for(int i = 0; i < peopleNum; i ++)
	{
		scanf("%d%d", &people[i].s, &people[i].b);
		people[i].pos = i;
	}
	sort(people, people + peopleNum);
	peopleNum = unique(people, people + peopleNum) - people;
	for(int i = 0; i < peopleNum; i ++)
	{
		int st = i, en = i;
		while(en + 1 < peopleNum && people[en].b == people[en + 1].b)
			en ++;
		for(int j = st; j <= en; j ++)
		{
			int k = find(root, people[j].s);
			if(k == null->idx)
			{
				g[j] = null->idx;
				f[j] = 1;
			}
			else
			{
				g[j] = k;
				f[j] = f[k] + 1;
			}
		}
		
		for(int j = st; j <= en; j ++)
			insert(root, alloc(j));

		i = en;
	}

	int best = -1;
	for(int i = 0; i < peopleNum; i ++)
		if(best == -1 || f[i] > f[best])
			best = i;
	printf("%d\n", f[best]);

	while(best != -1)
	{
		printf("%d ", 1 + people[best].pos);
		best = g[best];
	}
}
