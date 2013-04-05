#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int n, edge, st[100], ed[100], inq[10];
int ans, fa[10], vis[10];

bool check(int step)
{
    int v = ed[inq[step]];
    int x = fa[v];

    if(x != v) return false;
    return true;
}

void chose(int last, int step, int total)
{
    if(step > total)
    {
		for(int i = 1; i <= n; i++)
			if(!vis[i]) return;
		
        ans++; return;
    }

    for(int i = last + 1; i <= edge; i++)
    {
        inq[step] = i;
        if(check(step))
        {
            int u = st[i], v = ed[i];
			vis[u]++, vis[v]++, fa[v] = u;
            chose(i, step + 1, total);
            fa[v] = v, vis[u]--, vis[v]--;
        }
    }
}

int main()
{
    freopen("t.in", "r", stdin);

    while(1)
    {
        scanf("%d", &n), ans = 0, edge = 0;
        if(n == 0) break;

        for(int i = 1; i <= n; i++)
        {
            fa[i] = i;
            char tmp[10]; scanf("%s", tmp + 1);
            for(int j = 1; j <= n; j++)
                if(tmp[j] == '1' && i != j) edge++, st[edge] = i, ed[edge] = j;
        }

        //for(int i = 1; i <= edge; i++)
        //    printf("%d %d\n", st[i], ed[i]);

        chose(0, 1, n - 1);

        printf("%d\n", ans);
    }

    return 0;
}

