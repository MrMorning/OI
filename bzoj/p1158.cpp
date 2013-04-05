#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

const int INFINITY = 0x3f3f3f3f;

namespace solve
{
#define TOY(i) (i)
#define COMPARE(i) ((i) + toyNum)
	const int TOY_NUM_MAX = 400;
	const int COMPARE_TIMES_MAX = 100;
	const int EDGE_NUM_MAX = 2 * TOY_NUM_MAX + TOY_NUM_MAX * COMPARE_TIMES_MAX + 1;
	const int VTX_NUM_MAX = TOY_NUM_MAX + COMPARE_TIMES_MAX + 2;

	struct Edge
	{
		int from, to, capacity, lowerBound;
	};

	Edge edge[EDGE_NUM_MAX], *inEdge[VTX_NUM_MAX], *outEdge[VTX_NUM_MAX];
	int edgeCnt, vtxNum;
	int toyNum, compareTimes;
	int source, sink;
	int initLowerBound[TOY_NUM_MAX], initUpperBound[TOY_NUM_MAX];
	int possibleWeight[TOY_NUM_MAX];
	
	void addEdge(int u, int v, int b, int c)
	{
		Edge *e = &edge[edgeCnt ++];
		e->from = u, e->to = v, e->capacity = c, e->lowerBound = b;
		inEdge[v] = outEdge[u] = e;
	}

	void readData()
	{
		scanf("%d%d", &toyNum, &compareTimes);
		vtxNum = toyNum + compareTimes + 2;
		source = vtxNum - 2, sink = vtxNum - 1;

		for(int i = 0; i < toyNum; i ++)
		{
			scanf("%d%d", &initLowerBound[i], &initUpperBound[i]);
			initLowerBound[i] = max(initLowerBound[i], 0);
			initUpperBound[i] = min(initUpperBound[i], 20000);
		}
		for(int i = 0, l, r, d; i < compareTimes; i ++)
		{
			scanf("%d%d%d", &l, &r, &d);
			if(d > 0)
				addEdge(COMPARE(i), sink, d, d);
			else if(d < 0)
				addEdge(source, COMPARE(i), -d, -d);
			int toyIdx;
			while(l --)
			{
				scanf("%d", &toyIdx);
				toyIdx --;
				addEdge(TOY(toyIdx), COMPARE(i), 0, INFINITY);
			}
			while(r --)
			{
				scanf("%d", &toyIdx);
				toyIdx --;
				addEdge(COMPARE(i), TOY(toyIdx), 0, INFINITY);
			}
		}
	}

	void appendExtraEdge()
	{
		for(int i = 0; i < toyNum; i ++)
		{
			int u = TOY(i);
			if(inEdge[u] == NULL)
				addEdge(source, u, 0, INFINITY);
			if(outEdge[u] == NULL)
				addEdge(u, sink, 0, INFINITY);
			inEdge[u]->lowerBound = initLowerBound[i];
			inEdge[u]->capacity = initUpperBound[i];
		}

		addEdge(sink, source, 0, INFINITY);
	}

	bool checkWeight(int toyIdx, int weight);
	int calcLowerBound(int toyIdx);
	int calcUpperBound(int toyIdx);
	void main();
}

namespace maxFlow
{
	const int VTX_NUM_MAX = solve::VTX_NUM_MAX + 2;
	const int EDGE_NUM_MAX = solve::VTX_NUM_MAX + 2 * solve::EDGE_NUM_MAX;

	struct Edge
	{
		int capacity, to;
		Edge *next, *inv;
	};

	Edge edge[EDGE_NUM_MAX], *begin[VTX_NUM_MAX];
	int edgeCnt, vtxNum;
	int dist[VTX_NUM_MAX];
	int source, sink;
	int inBound[VTX_NUM_MAX], outBound[VTX_NUM_MAX];

	Edge *makeEdge(int u, int v, int w)
	{
		Edge *e = &edge[edgeCnt ++];
		e->to = v, e->next = begin[u], e->capacity = w;
		return begin[u] = e;
	}

	void addEdge(int u, int v, int w)
	{
		Edge *e1 = makeEdge(u, v, w),
			 *e2 = makeEdge(v, u, 0);
		e1->inv = e2, e2->inv = e1;
	}

	bool preLable()
	{
		static int queue[VTX_NUM_MAX];
		int head = 0, tail = 0;
		queue[tail ++] = source;
		memset(dist, -1, sizeof(int) * vtxNum);
		dist[source] = 0;
		while(head < tail)
		{
			int u = queue[head ++];
			for(Edge *e = begin[u]; e; e = e->next)
				if(e->capacity)
				{
					int v = e->to;
					if(dist[v] == -1)
					{
						dist[v] = dist[u] + 1;
						queue[tail ++] = v;
					}
				}
		}
		return dist[sink] != -1;
	}

	int findAug(int u, int flow)
	{
		if(u == sink)
			return flow;
		Edge *e;
		int result = 0;
		for(e = begin[u]; e; e = e->next)
			if(e->capacity)
			{
				int v = e->to;
				if(dist[v] == dist[u] + 1)
				{
					int tmp = findAug(v, min(e->capacity, flow));
					flow -= tmp;
					result += tmp;
					e->capacity -= tmp;
					e->inv->capacity += tmp;
					if(!flow)
						break;
				}
			}
		if(!e)
			dist[u] = -1;
		return result;
	}

	int dinic()
	{
		int result = 0;
		while(preLable())
			result += findAug(source, INFINITY);
		return result;
	}

	//upperbound && lowerbound network flow without src and sink
	//return true if there's a valid flow
	bool main(solve::Edge *edgeWithBound, int _edgeCnt, int _vtxNum)
	{
		vtxNum = _vtxNum + 2;
		source = vtxNum - 2, sink = vtxNum - 1;
		edgeCnt = 0;
		memset(begin, 0, sizeof(Edge*) * vtxNum);
		memset(inBound, 0, sizeof(int) * _vtxNum);
		memset(outBound, 0, sizeof(int) * _vtxNum);

		for(int i = 0; i < _edgeCnt; i ++)
		{
			solve::Edge *e = edgeWithBound + i;
			if(e->lowerBound > e->capacity)
				return false;
			inBound[e->to] += e->lowerBound;
			outBound[e->from] += e->lowerBound;
			addEdge(e->from, e->to, e->capacity - e->lowerBound);
		}

		for(int i = 0; i < _vtxNum; i ++)
		{
			int w = outBound[i] - inBound[i];
			if(w > 0)
				addEdge(i, sink, w);
			else if(w < 0)
				addEdge(source, i, -w);
		}

		dinic();
		for(Edge *e = begin[source]; e; e = e->next)
			if(e->capacity != 0)
				return false;
		return true;
	}
}

bool solve::checkWeight(int toyIdx, int weight)
{
	Edge *e = inEdge[TOY(toyIdx)];
	e->lowerBound = e->capacity = weight;
	bool result = maxFlow::main(edge, edgeCnt, vtxNum);
	e->lowerBound = initLowerBound[toyIdx];
	e->capacity = initUpperBound[toyIdx];
	return result;
}

int solve::calcLowerBound(int toyIdx)
{
	int lb = initLowerBound[toyIdx] - 1,
		rb = possibleWeight[toyIdx],
		mid = (lb + rb) / 2;
	while(lb < rb - 1)
	{
		if(checkWeight(toyIdx, mid))
			rb = mid;
		else
			lb = mid;
		mid = (lb + rb) / 2;
	}
	return rb;
}

int solve::calcUpperBound(int toyIdx)
{
	int lb = possibleWeight[toyIdx],
		rb = initUpperBound[toyIdx] + 1,
		mid = (lb + rb) / 2;
	while(lb < rb - 1)
	{
		if(checkWeight(toyIdx, mid))
			lb = mid;
		else
			rb = mid;
		mid = (lb + rb) / 2;
	}
	return lb;
}

void solve::main()
{
	readData();
	appendExtraEdge();
	if(!maxFlow::main(edge, edgeCnt, vtxNum))
	{
		printf("-1\n");
		return;
	}

	//generate one specific solution
	for(int i = 0; i < toyNum; i ++)
	{
		maxFlow::Edge *e = NULL;
		for(int j = 0; j < maxFlow::edgeCnt; j ++)
		{
			e = &maxFlow::edge[j];
			if(e->to == inEdge[TOY(i)]->to && e->inv->to == inEdge[TOY(i)]->from)
				break;
		}
		assert(e != NULL);
		int flow = e->inv->capacity;
		possibleWeight[i] = flow + initLowerBound[i];
	}

	for(int i = 0; i < toyNum; i ++)
		printf("%d %d ", calcLowerBound(i), calcUpperBound(i));
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	solve::main();
}
