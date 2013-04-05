#include <cstdio>
#include <cstring>
const int N_STATE_MAX = (1 << 21) + 1;
const int N_MAX = 22;

int go[N_MAX], queue[N_STATE_MAX];
int dist[N_STATE_MAX];
int pre[N_STATE_MAX], choice[N_STATE_MAX];
int n_ans, ans[N_MAX * 1000];

void solve(int n, int m)
{
	memset(dist, 0x3f, sizeof(int) * (1 << n));
	memset(go, 0, sizeof(int) * (n + 1));
	memset(pre, -1, sizeof(int) * (1 << n));
	memset(choice, -1, sizeof(int) * (1 << n));
	for(int i = 0; i < m; i ++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		go[u] |= 1 << v;
		go[v] |= 1 << u;
	}
	int head = 0, tail = 0;
	queue[tail ++] = (1 << n) - 1;
	dist[queue[0]] = 0;
	pre[0] = -1;
	while(head < tail) 
	{
		int u = queue[head ++];
		int v = 0;
		for(int i = 0; i < n; i ++)
			if((u >> i) & 1)
				v |= go[i];
		for(int i = 0; i < n; i ++)
		{
			int w = v & (~(1 << i));
			if(dist[w] > dist[u] + 1)
			{
				dist[w] = dist[u] + 1;
				pre[w] = u;
				choice[w] = i;
				queue[tail ++] = w;
			}
		}
	}

	int t = 0;
	if(choice[0] == -1)
		printf("Impossible\n");
	else
	{
		n_ans = 0;
		while(1)
		{
			ans[n_ans ++] = choice[t];
			t = pre[t];
			if(choice[t] == -1)
				break;
		}
		printf("%d:", n_ans);
		for(int i = n_ans - 1; i >= 0; i --)
			printf(" %d", ans[i]);
		printf("\n");
	}
}
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	while(1)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		if(n == 0)
			break;
		solve(n, m);
	}
}
