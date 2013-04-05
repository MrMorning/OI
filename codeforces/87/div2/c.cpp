#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int V_MAX = 2010;
vector<int> son[V_MAX];
int f[V_MAX];
int pre[V_MAX];
int nv;

int dp(int u)
{
	static bool done[V_MAX];
	if(done[u])
		return f[u];
	done[u] = true;
	int &ret = f[u] = 0;
	for(int i = 0; i < (int)son[u].size(); i ++)
	{
		int v = son[u][i];
		ret = max(ret, dp(v));
	}
	ret ++;
	return ret;
}
int main()
{
//	freopen("t.in", "r", stdin);
	scanf("%d", &nv);
	for(int i = 0; i < nv; i ++)
	{
		scanf("%d", &pre[i]);
		if(pre[i] != -1)
		{
			pre[i] --;
			son[pre[i]].push_back(i);
		}
	}
	int ans = 0;
	for(int i = 0; i < nv; i ++)
		if(pre[i] == -1)
			ans = max(ans, dp(i));
	printf("%d\n", ans);
}
