/*
 * Date: Sat Jan 22 22:32:01 CST 2011
 * Author: csimstu
 * Problem: poj 2449
 * Algorithm: k-th path
 * Use "fake" A-star to optimize the naked dijkstra in memory(cause so much nodes to search):
 * Let h[u] be the shortest path's length from u to destination, then
 * it's easy to prove that the best solution won't lose, that is h[x] <= h*[x],
 * and g[k] = g*[k]
 */
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAXN 1010
#define MAXM 100010
#define INFINITY 0x3f3f3f3f
//#define DEBUG

using std::queue;
using std::vector;
using std::priority_queue;

struct Edge
{
	int s, t, next, weight;
} edge[2][MAXM * 2];
int edgeCnt[2];

struct State
{
	int idx, dist, f;
	State(){};
	State(int _idx, int _dist, int _f):idx(_idx), dist(_dist), f(_f){};
};

struct cmp
{
	bool operator() (State a, State b)
	{
		return a.f > b.f;
	}
};

int begin[2][MAXN], dist[MAXN];
bool isInQ[MAXN];
int n, m, st, en, h[MAXN], kth;

void addEdge(int a, int b, int x, int t)
{
	edgeCnt[t] ++;
	edge[t][edgeCnt[t]].next = begin[t][a];
	begin[t][a] = edgeCnt[t];
	edge[t][edgeCnt[t]].weight = x;
	edge[t][edgeCnt[t]].s = a, edge[t][edgeCnt[t]].t = b;
}

void spfa(int st, int t)
{
	queue<int> q;
	memset(isInQ, 0, sizeof(isInQ));
	isInQ[st] = true;
	q.push(st);
	for(int i = 1; i <= n; i ++)
		dist[i] = INFINITY;
	dist[st] = 0;
	while(! q.empty())
	{
		int u = q.front(); q.pop();
		isInQ[u] = false;
		for(int now = begin[t][u]; now; now = edge[t][now].next)
		{
			int v = edge[t][now].t;
			if(dist[v] > dist[u] + edge[t][now].weight)
			{
				dist[v] = dist[u] + edge[t][now].weight;
				if(! isInQ[v])
					q.push(v), isInQ[v] = true;
			}
		}
	}
}


void solve()
{
	priority_queue<State, vector<State>, cmp> q;
	q.push(State(st, 0, h[st]));
	int times= 0;
	while(! q.empty())
	{
		State u = q.top(); q.pop();
		if(u.idx == en)
		{
			times ++;
			if(times == kth)
			{
				printf("%d\n", u.dist);
				exit(0);
			}
		}
		for(int now = begin[0][u.idx]; now; now = edge[0][now].next)
		{
			int v = edge[0][now].t;
			q.push(State(v, u.dist + edge[0][now].weight, u.dist + edge[0][now].weight + h[v]));
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d\n", &n, &m);
	for(int i = 1, a, b, x; i <= m; i ++)
	{
		scanf("%d %d %d\n", &a, &b, &x);
		addEdge(a, b, x, 0);
		addEdge(b, a, x, 1);
	}
	scanf("%d %d %d\n", &st, &en, &kth);
	if(st == en)
		kth += 1;
	spfa(en, 1);
	memcpy(h, dist, sizeof(dist));
	solve();
	printf("-1\n");
#ifdef DEBUG
	priority_queue<State, vector<State>, cmp> q;
	q.push(State(0, 0, 0));
	q.push(State(1, 1, 1));
	printf("%d\n", q.top().f);
#endif
}
