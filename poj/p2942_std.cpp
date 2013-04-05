#include <stdio.h>
#include <cstring>
#define min(a,b) ((a)<(b)?(a):(b))

char graph[1010][1010];
char bcc[1010][1010], color[1010];
int n, dfn[1010], low[1010], stack[1010], top, dfsidx, bccidx;

void tarjan (int x, int pere)
{
    int i, tar;
    dfn[x] = low[x] = dfsidx++;
    stack[top++] = x;
    for (i = 0; i < n; i++)
    {
        if (graph[x][i])
        {
            if (dfn[i] == -1)
            {
                tarjan(i, x);
                if (low[i] >= dfn[x])
                {
                    do
                    {
                        tar = stack[--top];
                        bcc[bccidx][tar] = 1;
                    } while (tar != i);
                    bcc[bccidx++][x] = 1;
                }
                low[x] = min(low[x], low[i]);
            }
            else if (i != pere) low[x] = min(low[x], dfn[i]);
        }
    }
}

int contradictory;
void brush (int x, int bcci)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (graph[x][i] && bcc[bcci][i])
        {
            if (color[i] == color[x])
            {
                contradictory = 1;
                return;
            }
            else if (color[i] == 0)
            {
                color[i] = 3 - color[x];
                brush(i, bcci);
            }
        }
    }
}

char bipartite[1010];
void judge (int bcci)
{
    int i;
    memset(color, 0, sizeof(color));
    contradictory = 0;
    for (i = 0; i < n; i++)
    {
        if (bcc[bcci][i])
        {
            color[i] = 1;
            brush(i, bcci);
            break;
        }
    }
    if (contradictory) bipartite[bcci] = 0;
    else bipartite[bcci] = 1;
}

int main ()
{
	freopen("t.in", "r", stdin);
    int m, a, b, i, j, ans;
    while (1)
    {
        scanf("%d %d", &n, &m);
        if (n == 0 && m == 0) break;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
                graph[i][j] = 1;
        }
        for (i = 0; i < n; i++)
            graph[i][i] = 0;
        for (i = 0; i < m; i++)
        {
            scanf("%d %d", &a, &b);
            a--, b--;
            graph[a][b] = graph[b][a] = 0;
        }
        top = dfsidx = bccidx = 0;
        memset(dfn, -1, sizeof(dfn));
        memset(bcc, 0, sizeof(bcc));
        for (i = 0; i < n; i++) if (dfn[i] == -1) tarjan(i, -1);
        for (i = 0; i < bccidx; i++) judge(i);
        for (i = 0, ans = 0; i < n; i++)
        {
            for (j = 0; j < bccidx; j++)
            {
                if (bcc[j][i] && bipartite[j] == 0)
                {
                    ans++;
                    break;
                }
            }
        }
        printf("%d\n", n - ans);
    }
    return 0;
} 
