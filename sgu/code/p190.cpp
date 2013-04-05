#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int offset[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
#define CONV(x, y) ((x) * n + (y))

bool bad[40][40];
bool vis[1600];
int match[1600];
vector<pair<int, int> > out[2];
int n, m;

struct Edge
{
	int to;
	Edge *next;
} *begin[1600], edge[10000];
int edgeCnt;

void addEdge(int u, int v)
{
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u];
	begin[u] = e;
}

inline void getIdx(int i, int &x, int &y)
{
	x = i / n;
	y = i % n;
}

bool dfs(int u)
{
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->to;
		if(!vis[v])
		{
			vis[v] = true;
			if(match[v] == -1 || dfs(match[v]))
			{
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i ++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		a --, b --;
		bad[a][b] = true;
	}
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if((i + j) & 1)
				if(!bad[i][j])
				{
					for(int d = 0; d < 4; d ++)
					{
						int in = i + offset[d][0],
							jn = j + offset[d][1];
						if(0 <= in && in < n)
							if(0 <= jn && jn < n)
								if(!bad[in][jn])
									addEdge(CONV(i, j), CONV(in, jn));
					}
				}
	int matchCnt = 0;
	memset(match, -1, sizeof(match));
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if((i + j) & 1)
				if(!bad[i][j])
				{
					memset(vis, 0, sizeof(vis));
					if(dfs(CONV(i, j)))
						matchCnt ++;
				}
	if(matchCnt * 2 != n * n - m)
		printf("No\n");
	else
	{
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++)
				if(!((i + j) & 1))
					if(!bad[i][j])
					{
						int pi, pj;
						getIdx(match[CONV(i, j)], pi, pj);
						if(i == pi)
						{
							if(j < pj)
								out[0].push_back(make_pair(i, j));
							else
								out[0].push_back(make_pair(pi, pj));
						}
						else
						{
							if(i < pi)
								out[1].push_back(make_pair(i, j));
							else
								out[1].push_back(make_pair(pi, pj));
						}
					}
		printf("Yes\n");
		for(int t = 1; t >= 0; t --)
		{
			printf("%d\n", out[t].size());
			for(int i = 0; i < (int)out[t].size(); i ++)
				printf("%d %d\n", out[t][i].first + 1, out[t][i].second + 1);
		}
	}

}
