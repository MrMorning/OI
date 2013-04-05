#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 10000;
const int MAXV = 10010;
const int MAXE = 100010;

struct se
{int v, d, next;};

se g[MAXE], r[MAXE];
int disg[MAXV], disr[MAXV];
int fg[MAXV], fr[MAXV];
int N, M, E=0;
int t[MAXV];
bool inq[MAXV];
deque<int> q;

void ae(int u, int v, int d)
{
    g[E].v = v; r[E].v = u;
    g[E].d = d; r[E].d = d;
    g[E].next = fg[u]; r[E].next = fr[v];
    fg[u] = E; fr[v] = E++;
}

bool spfa(int N, se e[], int f[], int dis[])
{
    int u, v, d, i;
    q.clear();
    for (u = 1; u <= N; ++u)
    {
        t[u] = 0;
        inq[u] = 1;
        q.push_back(u);
    }
    while (!q.empty())
    {
        u = q.front();
        q.pop_front();
        inq[u] = 0;
        for (i = f[u]; i != -1; i = e[i].next)
        {
            v = e[i].v; d = e[i].d;
            //printf("!%d %d %d %d %d %d\n", u, v, d, dis[u], dis[v], dis[v]<dis[u]+d);
            if (dis[v] > dis[u]+d)
            {
                dis[v] = dis[u]+d;
                if (!inq[v])
                {
                    inq[v] = 1;
                    q.push_back(v);
                    ++t[v];
                    if (t[v] > N) return 0;
                }
            }
        }
    }
    return 1;
}

int main()
{
	freopen("t.in", "r", stdin);
    int i, j, k, u, v, d;
    memset(fg, -1, sizeof(fg));
    memset(fr, -1, sizeof(fr));
    cin>>N>>M;
    while (M--)
    {
        scanf("%d%d%d", &u, &v, &d);
        ae(u, v, -d);
    }
    for (u = 1; u <= N; ++u)
        disg[u] = INF;
    if (!spfa(N, g, fg, disg))
    {
        puts("-1");
        return 0;
    }
    for (u = 1; u <= N; ++u)
        disr[u] = INF;
    if (!spfa(N, r, fr, disr))
    {
        puts("-1");
        return 0;
    }
    for (u = 1; u <= N; ++u)
        if (disg[u]<-disr[u])
        {
            puts("-1");
            return 0;
        }
    disg[N] = -disr[N];
    spfa(N, g, fg, disg);
//    for (u = 1; u <= N; ++u)
  //      printf("%d ", disg[u]);
	printf("%d\n", disg[N] - disg[1]);
    return 0;
}
