#include <cstdio>
#include <queue>

using namespace std;

typedef long long bignum_t;
#define BIGNUM_T_FMT "%lld"
typedef pair<int, int> state_t;

const int N_VTX_MAX = 400010;
const int N_EDGE_MAX = 13;
const bignum_t INFINITY = 1000000000000000LL;

int n_vtx, n_edge;
bignum_t dist[N_VTX_MAX];
int weight[N_EDGE_MAX];

struct cmp
{
	bool operator() (const state_t &a, const state_t &b)
	{
		return a.second > b.second;
	}
};

void dijkstra()
{
	priority_queue<state_t, vector<state_t>, cmp> PQ;
	for(int i = 0; i < n_vtx; i ++)
		dist[i] = INFINITY;
	dist[0] = 0;
	PQ.push(make_pair(0, 0));
	while(! PQ.empty())
	{
		state_t u = PQ.top(); PQ.pop();
		if(u.second > dist[u.first])
			continue;
		for(int i = 0; i < n_edge; i ++)
		{
			int v = (u.first + weight[i]) % weight[0];
			if(dist[u.first] + weight[i] < dist[v])
			{
				dist[v] = dist[u.first] + weight[i];
				PQ.push(make_pair(v, dist[v]));
			}
		}
	}
}

bignum_t calc(bignum_t upperlim)
{
	bignum_t ret = 0;
	for(int i = 0; i < n_vtx; i ++)
		if(dist[i] <= upperlim)
			ret += (upperlim - dist[i]) / weight[0] + 1;
	return ret;
}

int main()
{
	freopen("t.in", "r", stdin);
	//freopen("t.out", "w", stdout);
	bignum_t BMin, BMax;
	scanf("%d" BIGNUM_T_FMT BIGNUM_T_FMT, &n_edge, &BMin, &BMax);
	for(int i = 0; i < n_edge; i ++)
		scanf("%d", &weight[i]);
	for(int i = 0; i < n_edge; i ++)
		if(weight[0] == 0 && weight[i] != 0)
			swap(weight[0], weight[i]);
	if(weight[0] == 0)
	{
		printf("0\n");
		return 0;
	}
	n_vtx = weight[0];
	dijkstra();
	printf(BIGNUM_T_FMT "\n", calc(BMax) - calc(BMin - 1));
}
