#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int n, m, a, b, next[100001], queue[100000];
vector<int> adj[100001];
vector<int> ans;
int bfs(int i)
{
	next[0] = next[i];
	int qh = 0, qt = 0, res = 1;
	queue[qt ++] = i;
	while(qh < qt)
	{
		int u = queue[qh ++];
		sort(adj[u].begin(), adj[u].end());
		int p = 0;
		for(int w = 0, v = next[0]; v; v = next[v])
		{
			while(adj[u][p] < v) 
				p ++;
			if(adj[u][p] == v)
				w = v;
			else
			{
				next[w] = next[v];
				queue[qt ++] = v;
				res ++;
			}
		}
	}
	return res;
}
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	while(m --)
	{
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	next[0] = 1;
	for(int i = 1; i <= n; i ++)
		adj[i].push_back(n + 1), next[i] = i + 1;
	next[n] = 0;
	while(next[0])
		ans.push_back(bfs(next[0]));
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for(int i = 0; i < (int)ans.size(); i ++)
		printf("%d ", ans[i]);
}
