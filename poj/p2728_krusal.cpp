#include <cstdio>
#include <cmath>
#include <cassert>
#include <algorithm>
using namespace std;

const int V_MAX = 1000;
const int E_MAX = V_MAX * V_MAX;
const double oo = 10E10;
const double EPS = 10E-4;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define SQR(x) ((x) * (x))

struct DisjointSet
{
	int parent[V_MAX], rank[V_MAX];
	int find(int x)
	{
		return parent[x] == x ? x : parent[x] = find(parent[x]);
	}
	void merge(int x, int y)
	{
		int p = find(x), q = find(y);
		if(rank[p] < rank[q])
			swap(p, q);
		parent[q] = p;
		rank[p] ++;
	}
	DisjointSet(){}
	DisjointSet(int n)
	{
		for(int i = 0; i < n; i ++)
			parent[i] = i, rank[i] = 0;
	}
};

struct Edge
{
	int u, v;
	double length, weight, cost;
	Edge(){}
	Edge(int _u, int _v, double _length, double _cost):
		u(_u), v(_v), length(_length), cost(_cost){}
	bool operator< (const Edge &t) const
	{
		return weight < t.weight;
	}
} edge[E_MAX];

struct Village
{
	int x, y, z;
	Village(){}
	Village(int _x, int _y, int _z):
		x(_x), y(_y), z(_z){}
} vil[V_MAX];

int vilNum, edgeCnt;

double calcG(double lamda)
{
	static DisjointSet DS;
	DS = DisjointSet(vilNum);
	for(int i = 0; i < edgeCnt; i ++)
		edge[i].weight = edge[i].cost - lamda * edge[i].length;
	sort(edge, edge + edgeCnt);
	double res = 0;
	for(int i = 0; i < edgeCnt; i ++)
	{
		int u = edge[i].u, v = edge[i].v;
		if(DS.find(u) != DS.find(v))
		{
			res += edge[i].weight;
			DS.merge(u, v);
		}
	}
	return res;
}

int main()
{
	freopen("t.in", "r", stdin);
	while(1)
	{
		scanf("%d", &vilNum);
		if(vilNum == 0)
			break;
		for(int i = 0; i < vilNum; i ++)
			scanf("%d%d%d", &vil[i].x, &vil[i].y, &vil[i].z);
		edgeCnt = 0;
		for(int i = 0; i < vilNum; i ++)
			for(int j = i + 1; j < vilNum; j ++)
				edge[edgeCnt ++] = Edge(i, j, sqrt(SQR(vil[i].x - vil[j].x) + SQR(vil[i].y - vil[j].y)), ABS(vil[i].z - vil[j].z));
		double lb = 0, rb = oo;
		for(double mid = (lb + rb) / 2; fabs(rb - lb) >= EPS; mid = (lb + rb) / 2)
		{
			if(calcG(mid) < 0)
				rb = mid;
			else
				lb = mid;
		}
		printf("%.3lf\n", lb);
	}
}
